#include <AccelStepper.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ezButton.h>
#include <LiquidCrystal_I2C.h>
// Define stepper motor connections
#define STEP_PIN 3
#define DIR_PIN 4
#define ENABLE_PIN 5
#define ONE_WIRE_BUS 6
//lenth ditect
const int sensorPin2 = 8;
//const int buzzerPin2 = 12;
//break
const int sensorPin = 2;
const int buzzerPin = 13;
ezButton toggleSwitch(7);
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);
// Create a new ins2tance of the AccelStepper class
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
//I2C address 0x27, 16 column and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);
// create ezButton object that attach to pin 8;




void setup() {
  // Set the maximum speed and acceleration of the stepper motor
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);
  //Sensor PinSetup
  pinMode(sensorPin, INPUT);
  pinMode(sensorPin2, INPUT);
  // Set the enable pin as an output
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW);  // Enable the motor driver
  //Buzzer PinSetup
  pinMode(buzzerPin, OUTPUT);
  // temp Start serial communication for debugging purposes
  Serial.begin(9600);
  //temp Start up the library
  sensors.begin();
  // set debounce time to 50 milliseconds
  toggleSwitch.setDebounceTime(50);
  // initialize the lcd
  lcd.init();
  lcd.backlight();
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  //toggleSwitch.loop();  // MUST call the loop() function first
  // if (toggleSwitch.isPressed()) {
  //      display();
         
       if (irSensor()) {
          Serial.println("object Detected");
          buzzerOff();
          motor();

        }
       else if(!irSensor()) {
         Serial.println("No object Detected");
         buzzerOn();
        
        }
       if (irSensor2()) {
          Serial.println("object Detected");
          motor();

        }
       else if (!irSensor2()) {
         Serial.println("No object Detected");
         buzzerOn();
          }          

        temperature();

  // }
 // if (toggleSwitch.isReleased()){
       
   //    display();
    //  }
}

void motor() {
  digitalWrite(DIR_PIN, LOW);

  // Move the motor a certain number of steps
  int numSteps = 200;  // Adjust the number of steps as desired
  stepper.move(numSteps);
  stepper.runToPosition();

  // Delay before running in the other direction
}

int irSensor() {
  int sensorValue = digitalRead(sensorPin);

  if (sensorValue == LOW) {
    return true;
  } else {
    // No object detected
    return false;
  }

  
}

int irSensor2() {
  int sensorValue = digitalRead(sensorPin2);

  if (sensorValue == LOW) {
    return true;
  } else {
    // No object detected
    return false;
  }

  delay(500);
}
void buzzerOn() {

  digitalWrite(buzzerPin, HIGH);
  //delay(1000);  
}
void buzzerOff() {

  digitalWrite(buzzerPin, LOW);
  //delay(1000);  
}


void temperature() {

  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures();

  Serial.print("Celsius temperature: ");
  float temp = sensors.getTempCByIndex(0);
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.println(temp);
  if (temp > 32.19) {
    Serial.println(temp);
    Serial.println("High Temp");
  } else {
    Serial.println(temp);
    Serial.println("Low Temp");
  }

  delay(2000);
}


void display() {

  //lcd.clear();          // clear display
  //lcd.setCursor(4, 0);  // move cursor to   (4, 0)
  int state = toggleSwitch.getState();
  if (state == HIGH) {
    lcd.setCursor(4, 0);
    lcd.print("Power OFF");
    delay(500);
  } else {
    lcd.setCursor(4, 0);
    lcd.print("Power ON ");
    delay(500);
  }
}
