#!/usr/bin/enc python

import rospy
import matplotlib.pyplot as plt
from std_msgs.msg import UInt8

liste=[]
def callback(data):
	x  = data.data
	liste.append(x)
	plt.plot(liste)
	plt.draw()
	plt.pause(0.00000001)


if __name__ == '__main__' :

	rospy.init_node('listener' , anonymous=True)
	rospy.Subscriber('SENSORS', UInt8 , callback)
	plt.show()
	rospy.spin()
