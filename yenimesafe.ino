#include <ros.h>
#include <std_msgs/UInt8.h>


/*
 * created by Rui Santos, https://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
 
int trigPin = 9;    // Trigger
int echoPin = 10;    // Echo
long duration, cm;

ros::NodeHandle nh;
std_msgs::UInt8 distance_msg;

ros::Publisher Sensors("SENSORS",&distance_msg);



void setup() {
  //Serial Port begin
  Serial.begin (57600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  nh.initNode();
  nh.advertise(Sensors);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
   // Divide by 74 or multiply by 0.0135
  
  
  Serial.print(cm);
  //Serial.print("cm");
  Serial.println();
  distance_msg.data = cm;
  Sensors.publish( &distance_msg );
  nh.spinOnce();
  delay(250);
}
