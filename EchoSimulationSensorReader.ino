// Include libraries for 9DOF sensor:
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// Global variables for FSR:
int zone1AnalogPin = 1;   // Zone 1 FSR is connected to analog 0
int zone2AnalogPin = 2;   // Zone 2 FSR is connected to analog 1
int zone3AnalogPin = 3;   // Zone 3 FSR is connected to analog 2
int zone4AnalogPin = 4;   // Zone 4 FSR is connected to analog 3
int probeAnalogPin = 5;   // Probe FSR is connected to analog 4
int zone1Reading;         // the analog reading from the zone 1 FSR resistor divider
int zone2Reading;         // the analog reading from the zone 2 FSR resistor divider
int zone3Reading;         // the analog reading from the zone 3 FSR resistor divider
int zone4Reading;         // the analog reading from the zone 4 FSR resistor divider
int probeReading;         // the analog reading from the probe FSR resistor divider
int zone1Zero = 0;
int zone2Zero = 0;
int zone3Zero = 0;
int zone4Zero = 0;
int probeZero = 0;

// Global variable for 9DOF sensor:
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  Serial.begin(9600); // Set baud rate
  Serial.println("Zone & Orientation Sensor Test"); 
  Serial.println("");

  // Initialize the 9DOF sensor:
  if(!bno.begin()){
    // There was a problem detecting the BNO055 ... check your connections:
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;

  bno.setExtCrystalUse(true);
  
  for (int i=0; i<100; i++) {
    zone1Zero += analogRead(zone1AnalogPin);
    zone2Zero += analogRead(zone2AnalogPin);
    zone3Zero += analogRead(zone3AnalogPin);
    zone4Zero += analogRead(zone4AnalogPin);
    probeZero += analogRead(probeAnalogPin);
    delay(10);
  }
  
  zone1Zero = zone1Zero/100;
  zone2Zero = zone2Zero/100;
  zone3Zero = zone3Zero/100;
  zone4Zero = zone4Zero/100;
}

void loop() {
  zone1Reading = analogRead(zone1AnalogPin) - zone1Zero;
  zone2Reading = analogRead(zone2AnalogPin) - zone2Zero;
  zone3Reading = analogRead(zone3AnalogPin) - zone3Zero;
  zone4Reading = analogRead(zone4AnalogPin) - zone4Zero;
  probeReading = analogRead(probeAnalogPin) - probeZero;
  
  if(probeReading > 50) {    
    if(zone1Reading > 50){
      while(zone1Reading > 50){  
        Serial.print("1,");
        zone1Reading = analogRead(zone1AnalogPin);
        sensors_event_t event; 
        bno.getEvent(&event);
        
        // Display the floating point data:
        Serial.print(String(event.orientation.x) + ",");
        Serial.print(String(event.orientation.y) + ",");
        Serial.println(String(event.orientation.z) + ",");
        
      }
    } else if(zone2Reading > 50){
      while(zone2Reading > 50){  
        zone2Reading = analogRead(zone2AnalogPin);
        sensors_event_t event; 
        bno.getEvent(&event);
        Serial.print("2,");
        // Display the floating point data:
        Serial.print(String(event.orientation.x) + ",");
        Serial.print(String(event.orientation.y) + ",");
        Serial.print(String(event.orientation.z) + ",");
        Serial.println("");
  
        delay(50);
      }
    } else if(zone3Reading > 50){
      while(zone3Reading > 50){ 
        Serial.print("3,"); 
        zone3Reading = analogRead(zone3AnalogPin);
        sensors_event_t event; 
        bno.getEvent(&event);
        
        // Display the floating point data:
        Serial.print(String(event.orientation.x) + ",");
        Serial.print(String(event.orientation.y) + ",");
        Serial.println(String(event.orientation.z) + ",");
  
        delay(50);
      }
    } else if(zone4Reading > 50){
      while(zone4Reading > 50){  
        zone4Reading = analogRead(zone4AnalogPin);
        sensors_event_t event; 
        bno.getEvent(&event);
        Serial.print("4,");
        
        // Display the floating point data:
        Serial.print(String(event.orientation.x) + ",");
        Serial.print(String(event.orientation.y) + ",");
        Serial.println(String(event.orientation.z) + ",");
        
        delay(50);
      }
    } else {
      Serial.println("Tissue");
      delay(50);
    }
  } else {    
    Serial.println("No Contact");
    delay(50);
  }
}
