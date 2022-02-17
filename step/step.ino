
// defines pins numbers
const int stepPin = 9; 
const int dirPin = 8; 
#include <ros.h>

#include <SoftwareSerial.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

void servoC(const std_msgs::Int32& cmd_msg){

    digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < int(cmd_msg.data); x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  // One second delay
  
 delay(1000); 
 
 }

ros::Subscriber<std_msgs::Int32> sub("motor",servoC);

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}
void loop() {

  nh.spinOnce();
delay(1);
}
