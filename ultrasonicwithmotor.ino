/*
  Ping))) Sensor

  This sketch reads a PING))) ultrasonic
  rangefinder and returns the distance to the
  closest object in range. To do this, it sends a
  pulse to the sensor to initiate a reading, then
  listens for a pulse to return.  The length of
  the returning pulse is proportional to the
  distance of the object from the sensor.

  The circuit:
   * +V connection of the PING))) attached to +5V
   * GND connection attached to ground
   * SIG connection attached to digital pin 7

  http://www.arduino.cc/en/Tutorial/Ping

  This example code is in the public domain.
*/
#include <AFMotor.h>
AF_DCMotor motor(3, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
int inches = 0;

int cm = 0;

long readUltrasonicDistance(int pin)
{
  pinMode(pin, OUTPUT);  // Clear the trigger
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  // Sets the pin on HIGH state for 10 micro seconds
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(A1, INPUT);
  // Reads the pin, and returns the sound wave travel time in microseconds
  return pulseIn(A1, HIGH);
}

void setup()
{
  pinMode(A1, INPUT);
  pinMode(A0, OUTPUT);
  Serial.begin(9600);
motor.setSpeed(200); // set the speed to 200/255
}

void loop()
{
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(A0);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  Serial.print(inches);
  if(inches > 20){
      motor.run(FORWARD);
    }else{
      motor.run(RELEASE); // stopped
      }
  Serial.print("in, ");
  Serial.print(cm);
  Serial.println("cm");
  delay(100); // Wait for 100 millisecond(s)
}
