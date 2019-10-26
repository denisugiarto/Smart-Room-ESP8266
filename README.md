# Smartroom
Smart room using ESP8266 with datalogger
Sensor : 
- DHT 11 = Temperature
- LDR = Light Intensity (Custom)

Actuator :
- Fan
- LED light
- Miniature Projector 

The purpose:
- For control temperature and room light level wirelessly using esp8266. 
- Using sensor DHT11 to collect temperature data and  LDR to collect room light levels
- All data from the sensor is sent to the webserver using esp8266 and shows the condition of the room about temperature, light level, fan status, and lamp status. 
- After all, the microcontroller in ESP8266-12E will calculate to turn on or turn off the lamp and the fan between the current condition in the room and the threshold was set. 
- In webserver we can adjust the threshold of temperature and light level.
