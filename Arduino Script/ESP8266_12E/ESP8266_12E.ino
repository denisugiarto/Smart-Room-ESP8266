#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT11.h>
#include <ArduinoJson.h>
//DEKLARASI SENSOR DHT11
#define DHTPIN 13
DHT11 dht11(DHTPIN);
//DEKLARASI SENSOR LDR
#define LDR_PIN A0
#define MAX_ADC_READING 1023
#define ADC_REF_VOLTAGE 1.0
#define REF_RESISTANCE 3150 
#define LUX_CALC_SCALAR 12518931
#define LUX_CALC_EXPONENT -1.405
//DEKLARASI PIN OUTPUT
#define proyektor 4
#define lampu 5
#define kipas 12
//DEKLARASI HOST NAME, PASSWORD WIFI dan IP SERVER
const char* host_name = "SMART ROOM";
const char* password = "smartroom";
const char* host = "192.168.43.239";
//DEKLARASI VARIABEl
String url, Kipas, Lampu, Proyektor;
int ldrRawData,count,adc,cahaya,err;
float resistorVoltage, ldrVoltage, ldrResistance, suhu, humi;
void setup() {
  Serial.begin(115200);
  //Deklarasi Pin Aktuator
  pinMode(4, OUTPUT);   //Pin Proyektor
  pinMode(5, OUTPUT);   //Pin Lampu
  pinMode(12, OUTPUT);  //Pin kipas
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(12, 0);
  Serial.println();
  Serial.println();
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(host_name);
  WiFi.begin(host_name, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");}
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  }
void loop() {
  Bacadata();
  }
void bacasuhu(){//BACA SENSOR SUHU
  if((err=dht11.read(humi, suhu))==0)
  {
    Serial.print("SUHU : ");
    Serial.print(suhu);
    Serial.println(" C");}}
  
void bacacahaya(){//BACA SENSOR CAHAYA
  for (count = 0; count <= 200; count++){  
  adc = analogRead(LDR_PIN);
  if (adc > ldrRawData)ldrRawData = adc;
  delay(10);
  }
  resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;
  ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
  ldrResistance = ldrVoltage / resistorVoltage * REF_RESISTANCE;
  cahaya = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);
  Serial.print("CAHAYA : ");
  Serial.print(cahaya);
  Serial.println(" lux");
  ldrRawData = 0;}  
  
void SendDatasensor(){//KIRIM DATA KE SERVER
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;}
  String url="/smartroom/api/sensor/insert.php?suhu="+String(suhu)+"&cahaya="+String(cahaya);
  Serial.print("Requesting URL:");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(10);
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);}}
    
void Bacadata(){//MEMBACA Data pada database
  Serial.print("connecting to ");
  Serial.println(host);  
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;}
    url = "/smartroom/api/api.php";    
  Serial.print("Requesting URL: ");
  Serial.println(url);  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +  "Connection: keep-alive\r\n\r\n");
  delay(50);
  String section="header";
  while(client.connected()){
    String line = client.readStringUntil('\r');
    if (section=="header") { // headers..      
      if (line=="\n") { // skips the empty space at the beginning 
        section="json";
    }}
    else if (section=="json") {  // print the good stuff
      section="ignore";
      String result = line.substring(1);      
      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<500> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      String thsuhu = json_parsed["TRESHOLD"][0]["suhu"];
      String thcahaya = json_parsed["TRESHOLD"][0]["cahaya"];
      String Kipas = json_parsed["AKTUATOR"][0]["status"];
      String Lampu = json_parsed["AKTUATOR"][1]["status"];
      String Proyektor = json_parsed["AKTUATOR"][2]["status"];
      //BACA SENSOR SUHU
      bacasuhu();
      //BACA SENSOR CAHAYA
      bacacahaya();
      delay(100);
      Serial.println("KIRIM DATA ke SERVER");
      SendDatasensor();
      Serial.println("BACA AMBANG BATAS");
      Serial.print("Batas Suhu : ");
      Serial.println(thsuhu);
      Serial.print("Batas Cahaya : ");
      Serial.println(thcahaya);
      //FUNGSI PERBANDINGAN SUHU DAN BATAS SUHU
      if (suhu > thsuhu.toInt()){
        digitalWrite(kipas, 1);
        Serial.println("KIPAS ON");
        //update database KIPAS menjadi ON
        WiFiClient client;
        const int httpPort = 80;
        if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;}
        String url = "/smartroom/api/aktuator/update1.php?status=ON";
        Serial.print("Requesting URL: ");
        Serial.println(url);
        client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
        delay(500);
        while(client.available()){
        String line = client.readStringUntil('\r');
        Serial.print(line);}
        Serial.println("UPDATE KIPAS ON");}
      //FUNGSI PERBANDINGAN SUHU DAN BATAS SUHU
      if (suhu < thsuhu.toInt()){
        digitalWrite(kipas, 0);
        Serial.println("KIPAS OFF");
        //update database KIPAS menjadi OFF
        WiFiClient client;
        const int httpPort = 80;
        if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;}
        String url = "/smartroom/api/aktuator/update1.php?status=OFF";
        Serial.print("Requesting URL: ");
        Serial.println(url);
        client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
        delay(500);
        while(client.available()){
        String line = client.readStringUntil('\r');
        Serial.print(line);}
        Serial.println("UPDATE KIPAS OFF");}
      //FUNGSI PERBANDINGAN CAHAYA DAN BATAS CAHAYA
      if ((cahaya<thcahaya.toInt())&&(Proyektor=="OFF")){
        digitalWrite(lampu, 1);
        Serial.println("LAMPU ON");
        //update database LAMPU menjadi ON
        WiFiClient client;
        const int httpPort = 80;
        if (!client.connect(host, httpPort)) {
          Serial.println("connection failed");
          return;}
        String url = "/smartroom/api/aktuator/update2.php?status=ON";
        Serial.print("Requesting URL: ");
        Serial.println(url);
        client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
        delay(500);
        while(client.available()){
        String line = client.readStringUntil('\r');
        Serial.print(line);}
        Serial.println("UPDATE LAMPU ON");}
      //FUNGSI PERBANDINGAN CAHAYA DAN BATAS CAHAYA
      if (((cahaya>thcahaya.toInt()+200)||(cahaya>600))|| (Proyektor=="ON")){
        digitalWrite(lampu, 0);
        Serial.println("LAMPU OFF");
        //update database LAMPU menjadi OFF
        WiFiClient client;
        const int httpPort = 80;
        if (!client.connect(host, httpPort)) {
          Serial.println("connection failed");
          return;}
        String url = "/smartroom/api/aktuator/update2.php?status=OFF";
        Serial.print("Requesting URL: ");
        Serial.println(url);
        client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
        delay(500);
        while(client.available()){
          String line = client.readStringUntil('\r');
          Serial.print(line);}
          Serial.println("UPDATE LAMPU OFF");}
      Serial.println("BACA STATUS PROYEKTOR");
      if (Proyektor == "ON"){
        digitalWrite(proyektor, 1);
        digitalWrite(lampu, 0);
        Serial.println("PROYEKTOR ON");}
      if (Proyektor == "OFF"){
        digitalWrite(proyektor, 0);
        Serial.println("PROYEKTOR OFF");}
        Serial.println("closing connection");
        delay(10);}
    }}
