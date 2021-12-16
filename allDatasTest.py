# -*- coding: utf-8 -*-
"""
Created on Mon Dec 13 01:03:23 2021
@author: LENOPC
"""

import random
import pandas as pd
import xlsxwriter
import matplotlib.pyplot as plt
import rospy 
from std_msgs.msg import String



# convert and append to dict

def callback(sensor_datas):
    data_list =sensor_datas.split(",") # we will write data.data instead of sensor_datas
    k = 0
    for i in dictionary:
        dictionary[i].append(float(data_list[k]))
        k+=1
    
    plt.subplot(5,1,1)
    plt.plot(dictionary["temperature"],color = "blue")
    plt.ylabel("Celcius")
    
    plt.subplot(5,1,2)
    plt.plot(dictionary["altitude"],color = "red")
    plt.ylabel("meter")
    
    plt.subplot(5,1,3)
    plt.plot(dictionary["pressure"],color = "yellow")
    plt.ylabel("Pa")
    
    plt.subplot(5,1,4)
    plt.plot(dictionary["nem"],color = "green")
    plt.ylabel("pmm")
    
    plt.subplot(5,1,5)
    plt.plot(dictionary["karbon"],color = "black")
    plt.ylabel("C")
    
    plt.draw()
    plt.pause(0.0001)

def create_excel_file(dictionary):
    # read sensor datas
    
    df = pd.DataFrame(dictionary) # be sure that it is on the current directory
    # create new excel file's path
    file_path = "./bunee2.xlsx" # this should be the path is  current directory
    
    #add extra index col
    df["index"]  = [i for i in range(len(df))] # to plot easily
    
    # create new excel file
    workbook = xlsxwriter.Workbook(file_path)
    
    #create sheet1
    worksheet_  = workbook.add_worksheet()
    
    # fill sheet1 with sensor values
    for index,name in enumerate(df.columns):
        worksheet_.write(0,index,name)# 
        worksheet_.write_column(1,index,df[name])


    # create a blank chart
    chart = workbook.add_chart({"type":"scatter","subtype":"straight"})
    #fill chart categories x-axis  values y-axis
    chart.add_series({"categories":"=Sheet1!$F$2:$F${}".format(len(df)+1),
                      "values":"=Sheet1!$A$2:$A${}".format(len(df)+1),
                      "name":"temperature"})
    # name axs
    chart.set_x_axis({'name': 'Index'})
    chart.set_y_axis({'name': 'Temperature(C)'})
    # add chart to sheet1 at certain position it generally takes 15x8 (lenxwidth) places
    worksheet_.insert_chart("I1",chart)
    
    
    chart1 = workbook.add_chart({"type":"scatter","subtype":"straight"})
    chart1.add_series({"categories":"=Sheet1!$F$2:$F${}".format(len(df)+1),
                      "values":"=Sheet1!$B$2:$B${}".format(len(df)+1),
                      "name":"pressure"})
    chart1.set_x_axis({'name': 'Index'})
    chart1.set_y_axis({'name': 'Pressure(Pa)'})
    worksheet_.insert_chart("I16",chart1)
    
    chart2 = workbook.add_chart({"type":"scatter","subtype":"straight"})
    chart2.add_series({"categories":"=Sheet1!$F$2:$F${}".format(len(df)+1),
                      "values":"=Sheet1!$C$2:$C${}".format(len(df)+1),
                      "name":"altitude"})
    chart2.set_x_axis({'name': 'Index'})
    chart2.set_y_axis({'name': 'Altitude(meter)'})
    worksheet_.insert_chart("Q1",chart2)
    
    chart3 = workbook.add_chart({"type":"scatter","subtype":"straight"})
    chart3.add_series({"categories":"=Sheet1!$F$2:$F${}".format(len(df)+1),
                      "values":"=Sheet1!$D$2:$D${}".format(len(df)+1),
                      "name":"nem"})
    chart3.set_x_axis({'name': 'Index'})
    chart3.set_y_axis({'name': 'nem(?)'})
    worksheet_.insert_chart("Q16",chart3)
    
    chart4 = workbook.add_chart({"type":"scatter","subtype":"straight"})
    chart4.add_series({"categories":"=Sheet1!$F$2:$F${}".format(len(df)+1),
                      "values":"=Sheet1!$E$2:$E${}".format(len(df)+1),
                      "name":"karbon"})
    chart4.set_x_axis({'name': 'Index'})
    chart4.set_y_axis({'name': 'karbon(?)'})
    worksheet_.insert_chart("Y1",chart4)
    
    workbook.close()



dictionary =  {"temperature":[],"pressure":[],"altitude":[],"nem":[],"karbon":[]}

if __name__=="__main__": 
    rospy.init_node("excel_writer")
    rospy.Subscriber("SENSORS",String,callback) # we will call callback here
    plt.show()
    create_excel_file(dictionary)
    rospy.spin()
     
    

    
    