#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   //Hardware lcd tft library
#include <SoftwareSerial.h>
MCUFRIEND_kbv tft; // start library tft
//deklarasi warna
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define DEBUG true

/**** WiFi Host Name, Password, and Host ****/
String Host_name = "SMART ROOM";
String password = "smartroom";
String host = "192.168.43.239";
SoftwareSerial ESP8266 (10,11); //rxPin = pinTX ESP, txPin = pinRX ESP
String PROYEKTOR, ubah;
int readKey,THSUHU,THCAHAYA,SUHU,CAHAYA;
int menuPage = 0;
int cursorPosition = 0;

void Cursor(){
  switch (cursorPosition) {
    case 0:
      Serial.println("Menu Suhu");      
      tft.setTextColor(BLACK); tft.setTextSize(2);
      tft.setCursor(60,15); 
      tft.println(">");          
      tft.setTextColor(YELLOW);
      tft.setCursor(60,55);
      tft.println(">");
      tft.setCursor(60,95);
      tft.println(">");
      tft.setCursor(60,135);
      tft.println(">");
      tft.setCursor(60,175);
      tft.println(">");
      break;
    case 1:
      Serial.println("Menu Cahaya");
      tft.setTextColor(BLACK); tft.setTextSize(2);
      tft.setCursor(60,55); 
      tft.println(">");          
      tft.setTextColor(YELLOW);
      tft.setCursor(60,15);
      tft.println(">");
      tft.setCursor(60,95);
      tft.println(">");
      tft.setCursor(60,135);
      tft.println(">");
      tft.setCursor(60,175);
      tft.println(">");
      break;
    case 2:
      Serial.println("Proyektor");
      tft.setTextColor(BLACK); tft.setTextSize(2);
      tft.setCursor(60,95); 
      tft.println(">");          
      tft.setTextColor(YELLOW);
      tft.setCursor(60,15);
      tft.println(">");
      tft.setCursor(60,55);
      tft.println(">");
      tft.setCursor(60,135);
      tft.println(">");
      tft.setCursor(60,175);
      tft.println(">");
      break;
    case 3:
      Serial.println("Batas Suhu");
      tft.setTextColor(BLACK); tft.setTextSize(2);
      tft.setCursor(60,135); 
      tft.println(">");          
      tft.setTextColor(YELLOW);
      tft.setCursor(60,15);
      tft.println(">");
      tft.setCursor(60,55);
      tft.println(">");
      tft.setCursor(60,95);
      tft.println(">");
      tft.setCursor(60,175);
      tft.println(">");
      break;
    case 4:
      Serial.println("Batas Cahaya");
      tft.setTextColor(BLACK); tft.setTextSize(2);
      tft.setCursor(60,175); 
      tft.println(">");          
      tft.setTextColor(YELLOW);
      tft.setCursor(60,15);
      tft.println(">");
      tft.setCursor(60,55);
      tft.println(">");
      tft.setCursor(60,95);
      tft.println(">");
      tft.setCursor(60,135);
      tft.println(">");
      break;
  }
}
void operateMainMenu() {
  int activeButton = 0;
  if ((activeButton == 0) && (menuPage == 0)) {
    int button;
    readKey = analogRead(5);
    if (readKey < 900) {
      delay(100);
      readKey = analogRead(5);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 0: 
        break;
      case 1:  
        button = 0;
        if (cursorPosition > 0){
          cursorPosition = cursorPosition - 1;
        }
        Cursor();
        activeButton = 1;
        break;
      case 2:
        button = 0;
        if (cursorPosition < 4){
          cursorPosition = cursorPosition + 1;
        }
        Cursor();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        switch (cursorPosition) {
          case 0:
            menuItem2();
            break;
          case 1:
            menuItem3();
            break;
          case 2:            
            menuItem4();
            break;
          case 3:            
            menuItem5();
            break;
          case 4:            
            menuItem6();
            break;
        }
        activeButton = 1;
        break;
      case 4:
        button = 0;
        activeButton = 1;
        break;
    }
  }
  
  if ((activeButton == 0) && (menuPage == 1)) {
    int button;
    readKey = analogRead(5);
    if (readKey < 900) {
      delay(100);
      readKey = analogRead(5);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:
        button = 0;
        menuItem1();
        activeButton = 1;
        break;
    }
  }

  if ((activeButton == 0) && (menuPage == 2)) {
    int button;
    readKey = analogRead(5);
    if (readKey < 900) {
      delay(100);
      readKey = analogRead(5);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4: 
        button = 0;
        menuItem1();
        activeButton = 1;
        break;
    }
  }

  if ((activeButton == 0) && (menuPage == 3)) {
    int button;
    readKey = analogRead(5);
    if (readKey < 900) {
      delay(100);
      readKey = analogRead(5);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 3:
        button = 0;
        Serial.println("Change");
        ubahproyektor();
        Serial.println("Success");
        menuItem1();
        activeButton = 1;
        break;
      case 4: 
        button = 0;
        menuItem1();
        activeButton = 1;
        break;
    }
  }

  if ((activeButton == 0) && (menuPage == 4)) {
    int button;
    readKey = analogRead(5);
    if (readKey < 900) {
      delay(100);
      readKey = analogRead(5);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 0:
        break;
      case 1:
        button = 0;
        if (THSUHU < 50) {
          THSUHU++;
        }
        else if (THSUHU = 50) {
          THSUHU = 0;
        }
        Serial.print("Value : ");
        Serial.println(THSUHU);
        tft.fillRect(120,145,100,50,WHITE);
        tft.setTextColor(BLACK);
        tft.setCursor(120,145); tft.setTextSize(5);
        tft.print(THSUHU);
        activeButton = 1;
        break;
      case 2:
        button = 0;
        if (THSUHU < 51) {
          THSUHU--;
        }
        while (THSUHU < 0) {
          THSUHU = 50;
        }
        Serial.print("Value : ");
        Serial.println(THSUHU);
        tft.fillRect(120,145,100,50,WHITE);
        tft.setTextColor(BLACK);
        tft.setCursor(120,145); tft.setTextSize(5);
        tft.print(THSUHU);
        activeButton = 1;
        break;
      case 3:
        button = 0;
        Serial.println("Save");
        ubahthsuhu();
        Serial.println("Success");
        menuItem1();
        activeButton = 1;
        break;
      case 4:
        button = 0;
        menuItem1();
        activeButton = 1;
        break;
    }
  }

  if ((activeButton == 0) && (menuPage == 5)) {
    int button;
    readKey = analogRead(5);
    if (readKey < 900) {
      delay(100);
      readKey = analogRead(5);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 0:
        break;
      case 1:
        button = 0;
        if (THCAHAYA < 1000) {
          THCAHAYA ++;
        }
        else if (THCAHAYA = 1000) {
          THCAHAYA = 0;
        }
        Serial.print("Value : ");
        Serial.println(THCAHAYA);
        tft.fillRect(120,145,100,50,WHITE);
        tft.setTextColor(BLACK);
        tft.setCursor(120,145); tft.setTextSize(5);
        tft.print(THCAHAYA);
        activeButton = 1;
        break;
      case 2:
        button = 0;
        if (THCAHAYA  < 1001) {
          THCAHAYA --;
        }
        while (THCAHAYA < 0) {
          THCAHAYA = 1000;
        }
        Serial.print("Value : ");
        Serial.println(THCAHAYA );
        tft.fillRect(120,145,100,50,WHITE);
        tft.setTextColor(BLACK);
        tft.setCursor(120,145); tft.setTextSize(5);
        tft.print(THCAHAYA);
        activeButton = 1;
        break;
      case 3:
        button = 0;
        Serial.println("Save");
        ubahthcahaya();
        Serial.println("Success");
        menuItem1();
        activeButton = 1;
        break;
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        menuItem1();
        activeButton = 1;
        break;
    }
  }
}
int evaluateButton(int x) {
  int result = 0;
  if (x < 150 ) {
    result = 1; // Atas
  } if (x > 151 && x < 300) {
    result = 2; // Bawah
  } if (x > 320 && x < 650) {
    result = 3; // Masuk
  } if (x > 660 && x < 750) {
    result = 4; // Keluar
  }
  return result;
}

void menuItem1() { // Function executes when you select the 2nd item from main menu
  int activeButton = 0;
  menuPage = 0;
  Serial.println("Menu Utama");
  tft.fillRect(0, 0, 320, 215, WHITE);
  tft.fillRect(57, 7, 206, 31, BLACK);
  tft.fillRect(60, 10, 200, 25, YELLOW);
  tft.fillRect(57, 47, 206, 31, BLACK);
  tft.fillRect(60, 50, 200, 25, YELLOW);
  tft.fillRect(57, 87, 206, 31, BLACK);
  tft.fillRect(60, 90, 200, 25, YELLOW);
  tft.fillRect(57, 127, 206, 31, BLACK);
  tft.fillRect(60, 130, 200, 25, YELLOW);
  tft.fillRect(57, 167, 206, 31, BLACK);
  tft.fillRect(60, 170, 200, 25, YELLOW);  
  tft.setTextColor(BLACK); tft.setTextSize(2);
  tft.setCursor(75, 15); 
  tft.println("Suhu Ruangan");
  tft.setCursor(75, 55); 
  tft.println("Cahaya Ruangan");
  tft.setCursor(75, 95); 
  tft.println("Proyektor");
  tft.setCursor(75, 135);
  tft.println("Batas Suhu");
  tft.setCursor(75, 175);
  tft.println("Batas Cahaya");
  tft.setCursor(54,220); tft.setTextSize(1);
  tft.println("Oleh: Deni Sugiarto NIM 120534400684");
  tft.setCursor(54,230);
  tft.println("S1 Pendidikan Teknik Elektro 2012 UM");
}

void menuItem2() {
  int activeButton = 0;
  menuPage = 1;
  Serial.println("Read Temp");
  suhu();
  tft.fillRect(0, 0, 320, 75, BLUE);
  tft.fillRect(0, 75, 320, 3, RED);
  tft.fillRect(0, 80, 320, 135, WHITE);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.setCursor(0, 10);
  tft.println("   Suhu Ruangan");
  tft.setCursor(0, 40);
  tft.println("  Sensor: DHT 11");
  tft.fillRect(185,125,75,30,WHITE);  
  tft.setTextColor(BLACK); 
  tft.setCursor(155, 120);
  tft.println("  o");
  tft.setTextSize(5);
  tft.setCursor(120, 125);
  tft.println(SUHU);
  tft.setCursor(160, 125);
  tft.println("  C");
}

void menuItem3() {
  int activeButton = 0;
  menuPage = 2;
  Serial.println("Read Light");
  cahaya();
  tft.fillRect(0, 0, 320, 75, BLUE);
  tft.fillRect(0, 75, 320, 3, RED);
  tft.fillRect(0, 80, 320, 135, WHITE);
  tft.setTextColor(WHITE); tft.setTextSize(3);
  tft.setCursor(0, 10);
  tft.println("  Cahaya Ruangan");
  tft.setCursor(0, 40);
  tft.println("   Sensor: LDR");
  tft.setTextColor(BLACK); tft.setTextSize(2);
  tft.setCursor(190, 120);
  tft.fillRect(50,120,125,50,WHITE);
  tft.setCursor(100, 125); tft.setTextSize(5);
  tft.print(CAHAYA);
  tft.println(" lux");
}

void menuItem4() { // Function executes when you select the 7th item from main menu
  int activeButton = 0;
  menuPage = 3;
  Serial.println("Read Proyektor");
  proyektor();
  tft.fillRect(0, 0, 320, 75, BLUE);
  tft.fillRect(0, 75, 320, 3, RED);
  tft.fillRect(0, 80, 320, 135, WHITE);
  tft.fillRect(55, 181, 84, 28, BLACK);
  tft.fillRect(57, 183, 80, 24, RED);  
  tft.fillRect(181, 181, 84, 28, BLACK);
  tft.fillRect(183, 183, 80, 24, RED);  
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.setCursor(0, 10);
  tft.println("    Pengaturan");
  tft.setCursor(0, 40);
  tft.println("  Kendali Ruangan");
  tft.setTextColor(BLACK);  tft.setTextSize(2);
  tft.setCursor(40, 90);
  tft.println(" Status Proyektor :");
  tft.setCursor(62, 188);
  tft.println("SIMPAN");
  tft.setCursor(195, 188);
  tft.println("BATAL");
  tft.setCursor(125,125); tft.setTextSize(5);
  tft.print(PROYEKTOR);
}

void menuItem5() {
  int activeButton = 0;
  menuPage = 4;
  Serial.println("Read Batas Suhu");
  thsuhu();
  tft.fillRect(0, 0, 320, 75, BLUE);
  tft.fillRect(0, 75, 320, 3, RED);
  tft.fillRect(0, 80, 320, 135, WHITE);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.setCursor(0, 10);
  tft.println("    Pengaturan");
  tft.setCursor(0, 40);
  tft.println("  Kendali Ruangan");
  tft.setTextColor(BLACK);  tft.setTextSize(2);
  tft.setCursor(40, 90);
  tft.println(" Ambang Batas Suhu :");
  tft.setCursor(120,145); tft.setTextSize(5);
  tft.print(THSUHU);
}

void menuItem6() { // Function executes when you select the 6th item from main menu
  int activeButton = 0;
  menuPage = 5;
  Serial.println("Read Batas Cahaya");
  thcahaya();
  tft.fillRect(0, 0, 320, 75, BLUE);
  tft.fillRect(0, 75, 320, 3, RED);
  tft.fillRect(0, 80, 320, 135, WHITE);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.setCursor(0, 10);
  tft.println("    Pengaturan");
  tft.setCursor(0, 40);
  tft.println("  Kendali Ruangan");
  tft.setTextColor(BLACK);  tft.setTextSize(2);
  tft.setCursor(30, 90);
  tft.println(" Ambang Batas Cahaya :");
  tft.setCursor(120,145); tft.setTextSize(5);
  tft.print(THCAHAYA);
}

//Fungsi Ubah Batas Suhu
void ubahthsuhu(){
  Serial.print("Change to ");
  Serial.println(THSUHU);
  String add = "AT+CIPSTART=\"TCP\",\"";
  add += host;
  add += "\",80";
  add += "\r\n";
  sendData(add, 3000, 1);
  String rest = "AT+CIPSEND=60";
  rest += "\r\n";
  sendData(rest, 1000, 1);
  String hostt = "GET /smartroom/api/kendali/thsuhu.php?batas=";
  hostt += THSUHU;
  hostt += "\r\n";
  hostt += "Host:";
  hostt += host;
  hostt += "\r\n\r\n";
  sendData(hostt, 1500, 1);
  Serial.print("Success");
}

// Fungsi Ubah Batas Cahaya
void ubahthcahaya(){
  Serial.print("Change to ");
  Serial.println(THCAHAYA);
  String add = "AT+CIPSTART=\"TCP\",\"";
  add += host;
  add += "\",80";
  add += "\r\n";
  sendData(add, 3000, 1);
  String rest = "AT+CIPSEND=60";
  rest += "\r\n";
  sendData(rest, 1000, 1);
  String hostt = "GET /smartroom/api/kendali/thcahaya.php?batas=";
  hostt += THCAHAYA;
  hostt += "\r\n";
  hostt += "Host:";
  hostt += host;
  hostt += "\r\n\r\n";
  sendData(hostt, 1500, 1);
  Serial.print("Success");
}

//Fungsi Ubah Proyektor
void ubahproyektor(){
  if (PROYEKTOR == "ON"){ubah="OFF";}
  if (PROYEKTOR == "OFF"){ubah="ON";}
  Serial.print("Change to ");
  Serial.println(ubah);
  String add = "AT+CIPSTART=\"TCP\",\"";
  add += host;
  add += "\",80";
  add += "\r\n";
  sendData(add, 3000, 1);
  String rest = "AT+CIPSEND=60";
  rest += "\r\n";
  sendData(rest, 1000, 1);
  String hostt = "GET /smartroom/api/aktuator/update3.php?status=";
  hostt += ubah;
  hostt += "\r\n";
  hostt += "Host:";
  hostt += host;
  hostt += "\r\n\r\n";
  sendData(hostt, 1500, 1);
  Serial.print("Success");
}

String suhu()
{
  String add = "AT+CIPSTART=\"TCP\",\"";
  add += host;
  add += "\",80";
  add += "\r\n";
  sendData(add, 3000, 1);
  String rest = "AT+CIPSEND=50";
  rest += "\r\n";
  sendData(rest, 1000, 1);  
  String hostt = "GET /smartroom/api/sensor/readsuhu.php";
  hostt += "\r\n";
  hostt += "Host:";
  hostt += host;
  hostt += "\r\n\r\n";
  String suhu = sendData(hostt, 1500, 1);  
  int i = 0;
  while (suhu.charAt(i) != ':')
    i++;
  i++;
  suhu = suhu.substring(i);
  int j = 0;
  while (suhu.charAt(j) != 'C')
  j++;
  suhu = suhu.substring(0, j);
  if (DEBUG)
  Serial.println("");
  Serial.print("Value : ");
  Serial.println(suhu);
  SUHU = suhu.toInt();
  return (suhu);
}

String cahaya(){
  String add = "AT+CIPSTART=\"TCP\",\"";
  add += host;
  add += "\",80";
  add += "\r\n";
  sendData(add, 3000, 1);
  String rest = "AT+CIPSEND=50";
  rest += "\r\n";
  sendData(rest, 1000, 1);
  String hostt = "GET /smartroom/api/sensor/readcahaya.php";
  hostt += "\r\n";
  hostt += "Host:";
  hostt += host;
  hostt += "\r\n\r\n";
  String cahaya = sendData(hostt, 1500, 1);
  int i = 0;
  while (cahaya.charAt(i) != ':')
    i++;
  i++;
  cahaya = cahaya.substring(i);
  int j = 0;
  while (cahaya.charAt(j) != 'C')
  j++;
  cahaya = cahaya.substring(0, j);
  if (DEBUG)
  Serial.println("");
  Serial.print("Value : ");
  Serial.println(cahaya);
  CAHAYA = cahaya.toInt();
  return (cahaya);
}

String proyektor(){
  String add = "AT+CIPSTART=\"TCP\",\"";
  add += host;
  add += "\",80";
  add += "\r\n";
  sendData(add, 3000, 1);
  String rest = "AT+CIPSEND=50";
  rest += "\r\n";
  sendData(rest, 1000, 1);
  String hostt = "GET /smartroom/api/aktuator/read3.php";
  hostt += "\r\n";
  hostt += "Host:";
  hostt += host;
  hostt += "\r\n\r\n";
  String proyektor = sendData(hostt, 1500, 1);
  int i = 0;
  while (proyektor.charAt(i) != ':')
    i++;
  i++;
  proyektor = proyektor.substring(i);
  int j = 0;
  while (proyektor.charAt(j) != 'C')
  j++;
  proyektor = proyektor.substring(0, j);
  if (DEBUG)
  Serial.println("");
  Serial.print("Value : ");
  Serial.println(proyektor);
  PROYEKTOR = proyektor;
  return (proyektor);  
}

String thsuhu(){
  String add = "AT+CIPSTART=\"TCP\",\"";
  add += host;
  add += "\",80";
  add += "\r\n";
  sendData(add, 3000, 1);
  String rest = "AT+CIPSEND=50";
  rest += "\r\n";
  sendData(rest, 1000, 1);
  String hostt = "GET /smartroom/api/kendali/readthsuhu.php";
  hostt += "\r\n";
  hostt += "Host:";
  hostt += host;
  hostt += "\r\n\r\n";
  String thsuhu = sendData(hostt, 1500, 1);
  int i = 0;
  while (thsuhu.charAt(i) != ':')
    i++;
  i++;
  thsuhu = thsuhu.substring(i);
  int j = 0;
  while (thsuhu.charAt(j) != 'C')
  j++;
  thsuhu = thsuhu.substring(0, j);
  if (DEBUG)
  Serial.println("");
  Serial.print("Value : ");
  Serial.println(thsuhu);
  THSUHU = thsuhu.toInt();
  return (thsuhu);
}

String thcahaya(){
  String add = "AT+CIPSTART=\"TCP\",\"";
  add += host;
  add += "\",80";
  add += "\r\n";
  sendData(add, 3000, 1);
  String rest = "AT+CIPSEND=50";
  rest += "\r\n";
  sendData(rest, 1000, 1);
  String hostt = "GET /smartroom/api/kendali/readthcahaya.php";
  hostt += "\r\n";
  hostt += "Host:";
  hostt += host;
  hostt += "\r\n\r\n";
  String thcahaya = sendData(hostt, 1500, 1);
  int i = 0;
  while (thcahaya.charAt(i) != ':')
    i++;
  i++;
  thcahaya = thcahaya.substring(i);
  int j = 0;
  while (thcahaya.charAt(j) != 'C')
  j++;
  thcahaya = thcahaya.substring(0, j);
  if (DEBUG)
  Serial.println("");
  Serial.print("Value : ");
  Serial.println(thcahaya);
  THCAHAYA = thcahaya.toInt();
  return (thcahaya);
}

String sendData(String command, const int times, boolean debug) {
  String response = "";
  ESP8266.print(command); // send the read character to the Serial1
  long int Time = millis();
  while ( (Time + times) > millis()) {
    while (ESP8266.available()) {
      // The esp has data so display its output to the serial window
      char c = ESP8266.read(); // read the next character.
      response += c;
    }
  }
  if (debug) {
    Serial.print(response);
  }
  return response;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESP8266.begin(9600);
  tft.reset();
  uint16_t identifier = tft.readID();
  if (identifier == 0xEFEF) identifier = 0x9486;
  tft.begin(identifier);
  tft.setRotation(1);
  tft.fillScreen(WHITE);
  tft.setTextSize(3); 
  tft.setTextColor(BLACK);
  tft.setCursor(80,100);
  tft.println("SMART ROOM");
  Serial.println("CONNECTING");
  String conn = "AT+CWJAP=\"";
  conn += Host_name;  // Host name
  conn += "\",\"";
  conn += password; // Password
  conn += "\"";
  conn += "\r\n";
  sendData(conn,3000, 1); // Join the connection.( AT+CWJAP = "Host_name","password" )
  String cif = "AT+CIFSR\r\n"; // SHOW IP address
  sendData(cif,3000,1);
  tft.fillRect(50,80,240,60,WHITE);
  menuItem1();
}

void loop() {
  // put your main code here, to run repeatedly:
  operateMainMenu();
}
