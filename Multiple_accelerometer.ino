#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>
#include <TCA9548A.h>
float sensitivity = 2 * 9.81 / 256;  // 2 is the range of the ADXL345 accelerometer in g, 9.81 is the acceleration due to gravity in m/s^2, and 256 is the number of least significant bits (LSBs) per g
Adafruit_ADXL345_Unified accel1 = Adafruit_ADXL345_Unified(0); // Initialize accelerometer 1
Adafruit_ADXL345_Unified accel2 = Adafruit_ADXL345_Unified(1); // Initialize accelerometer 2

// Define the potentiometer pin
const int potPin = A0; // analog input pin for /2
int val = 0; // variable to store the potentiometer value
float angle = 0; // variable to store the angle in degrees


void TCA9548A(uint8_t bus) //function of TCA9548A
{
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

void setup() {
  Serial.begin(250000);
  Wire.begin();
  accel1.begin();
  accel2.begin();
  delay(10);
}

void loop() {
  sensors_event_t event1, event2;
  
  // Read accelerometer data from accelerometer 1
  TCA9548A(0);
  accel1.getEvent(&event1);
  Serial.print("  X: "); Serial.print(" , "); Serial.print(event1.acceleration.x * sensitivity); Serial.print(" , ");
  Serial.print("  Y: "); Serial.print(" , "); Serial.print(event1.acceleration.y * sensitivity); Serial.print(" , ");
  Serial.print("  Z: "); Serial.print(" , "); Serial.print(event1.acceleration.z * sensitivity);  Serial.print(" , ");

  // Read accelerometer data from accelerometer 2
  TCA9548A(1);
  accel2.getEvent(&event2);
  Serial.print("  X: "); Serial.print(" , "); Serial.print(event2.acceleration.x * sensitivity); Serial.print(" , ");
  Serial.print("  Y: "); Serial.print(" , "); Serial.print(event2.acceleration.y * sensitivity); Serial.print(" , ");
  Serial.print("  Z: "); Serial.print(" , "); Serial.print(event2.acceleration.z * sensitivity); Serial.print(" , "); Serial.print(" m/s^2"); Serial.print(" , ");

  // Read potentiometer
  val = analogRead(potPin); // read the potentiometer value
  angle = map(val, 0, 1023, 0, 280); // map the potentiometer value to angle (0-135)
  Serial.print(angle);
  Serial.print(" , "); Serial.println(" degrees");
  delay(10); // Add a delay between readings
}
