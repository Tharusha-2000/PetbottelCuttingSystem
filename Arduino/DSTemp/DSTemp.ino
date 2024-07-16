#include <OneWire.h>
#include <DallasTemperature.h>
// Data wire is conntec to the Arduino digital pin 6
#define ONE_WIRE_BUS 6
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
}

void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  float temp =sensors.getTempCByIndex(0);
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.println(temp);
  if(temp>32.19){
  Serial.println(temp);
  Serial.println("High Temp");
  }
  else{
  Serial.println(temp);
  Serial.println("Low Temp");
  }

  delay(2000);

}
