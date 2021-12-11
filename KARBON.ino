#include <ros.h>
#include <std_msgs/UInt8.h>
ros::NodeHandle nh;
std_msgs::UInt8 karbon_msg;

ros::Publisher Sensors("SENSORS",&karbon_msg);

    /*
  modified on Sep 28, 2020
  Modified by MohammedDamirchi from Arduino Examples
  Home
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  nh.initNode();
  nh.advertise(Sensors);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  karbon_msg.data = sensorValue;
  Sensors.publish( &karbon_msg );
  nh.spinOnce();
  delay(20);
}
