#include <ros.h>

#include <LiquidCrystal.h>

#include <std_msgs/UInt8.h>

int sensorValue;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

ros::NodeHandle nh;
std_msgs::UInt8 hava_msg;

ros::Publisher Sensors("SENSORS",&hava_msg);

void setup(){  lcd.begin(16, 2);

  nh.initNode();
  nh.advertise(Sensors);
 }
void loop(){sensorValue = analogRead(0);       // read analog input pin 0
  String data = String(sensorValue);
  hava_msg.data = data.c_str();
  Sensors.publish( &hava_msg );
  nh.spinOnce();
  
delay(100);                                   // wait 100ms for next reading

}
