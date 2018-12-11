# Build Instructions

# Introduction
My project I am working with deals with reading temperature data from a temperature sensor. My sensor 
is called a TMP006 IR Temperature Sensor that can measure the temperature of any object without making direct contact with it.
It detects and absorbs the infrared energy from an object regardless of how hot or cold it is. I plan on storing 
my temperature data from my sensor to the Firebase database where all my data is stored. The reason why I chose this
project is because I was interested in the idea of reading an object's temperature data from the sensor just by pointing my finger
directly close to it. Here is a system UML diagram below to show you how my hardware will send data from my Raspberry Pi 3 to my database.
![Image description](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/UMLSystemDiagram.PNG)

# Bill of Materials/Budget
The total cost of my budget is $131.55 which is below the maximum limit of $150. I did not order any of my hardware materials online instead I went to local electronic stores such as Canada Computers and Creatron Inc. They had everything I needed in my budget including Raspberry Pi 3 kit, TMP006 IR Temperature Sensor, SD Card, USB to Ethernet Adapter, etc. I also included where I got my parts from the links in my budget. Here is a image below to show you my budget and all the materials I used for my project.
https://raw.githubusercontent.com/n01103934/Thermometer/master/images/Budget.PNG

# Time Commitment
The project did not take me long to complete because I got my parts ahead of time and started working on it as soon as possible.
However, their was still alot of time and commitment put in setting up my Raspberry Pi 3 and changing the default address to my
address as well as reading data from sensor. I started off researching my parts for project early then I went to get them and lucky
the electronic stores like Creatron Inc and Canada Computers have what I needed. Once I acquired the parts I started setting up my 
Raspberry Pi 3 which took almost a week at the lastest for setup. After that I soldering the header pins with my sensor to make a 
connection to it and the Raspberry Pi 3. Then, I tested the sensor and see if it can read data by running the python program for 
my sensor's library and I was able to display the temperature readings on the output just by pointing finger close to the sensor.
Overall, it took alot of time and commitment inorder to finish my project and put it all together for the next term. Finally, it 
took about 3 to 5 weeks to complete and I achieve the end result of reading data from my final hardware for the project.

# Mechanical Assembly
Before, you connect your sensor to Raspberry Pi 3 you need to get header pins in order for your Raspberry Pi 3 to detect it. I provided 
a link to show you where you could get them for your sensor incase you don't already have one.  
https://www.digikey.ca/product-detail/en/omron-electronics-inc-emc-div/XG8T-0231/XG8T-0231-ND/1829453?utm_adgroup=&mkwid=s3xcZrPTl&pcrid=312348616043&pkw=&pmt=&pdv=c&productid=1829453&slid=&gclid=EAIaIQobChMIp6fskvWQ3wIVFHdeCh2qPAeFEAYYASABEgKKKvD_BwE

This open-sourced adafruit website will help you connect the TMP006 IR Temperature Sensor with the Raspberry Pi 3 or BeagleBone Black.
https://learn.adafruit.com/tmp006-temperature-sensor-python-library/hardware

Firstly, you need to connect a jumper wire from the 3.3V pin of the Raspberry Pi 3 to first pin(VCC) on my sensor. Secondly, the GND pin on Raspberry Pi 
3 connects another jumper wire to the second pin(GND) of my sensor. After, connect a third jumper wire from SDA pin of Raspberry Pi 3 to the third pin(SDA) 
of my sensor. Then, the SCL pin of Raspberry Pi 3 connects with the fourth pin(SCL) of my sensor. The next link will give you information on how to change
your sensor's default address which is 0x40 to another one ranging from 0x41 to 0x47. 
https://learn.adafruit.com/infrared-thermopile-sensor-breakout/assembly-and-wiring


# PCB / Soldering
I made a fritzing file in my repository to create my own custom PCB just by following my breadboard and schematic
connections to do the same for the PCB. The file is called Thermometer Circuit Diagram.fzz in my github repository. 
https://github.com/n01103934/Thermometer

Here are links to view my breadboard, schematic, and pcb diagrams for my project below.
https://raw.githubusercontent.com/n01103934/Thermometer/master/images/Thermometer%20Circuit%20Diagram_bb.png
https://raw.githubusercontent.com/n01103934/Thermometer/master/images/Thermometer%20Circuit%20Diagram_schem.png
https://raw.githubusercontent.com/n01103934/Thermometer/master/images/Thermometer%20Circuit%20Diagram_pcb.png

Additionally, I emailed the prototype lab my gerber files by exporting them from my fritzing project and got my board 
the next day. Then, I started soldering my via traces on my custom PCB and connected my header pins to the board. 
After, I soldered my header pins on sensor to my PCB board from the top to bottom and I connected the header socket to 
my board as well. Finally, I connected the PCB to my Raspberry Pi 3, powered it on, ran the sudo i2cdetect -y 1 on cmd
terminal and I got my I2C address (0x46) displayed on the output for my sensor. 

# Power Up
First you need to download the operating system of Pi and format the micro SD card using the SD card reader included with 
the card to upload the Pi image to the Raspberry Pi 3. Here is a very useful blog that I followed step by step to upload my 
image to Raspberry Pi 3 as well as basic setup. https://github.com/six0four/StudentSenseHat/blob/master/cribpisdcard.md

Once you installed the operating system and got the image uploaded to Raspberry Pi 3, insert the SD card into the slot at the 
bottom of Pi, and boot it up with the power supply. If you are booting the Raspberry Pi 3 for the first time then you will have 
the option to change the default username and password to what ever suits you or you can leave it the same. The default username 
and password for every Raspberry Pi is always pi and raspberry unless a user changes it. Everything you need to know about the basic
setup of the Raspberry Pi is from the first link provided above just follow the instructions and your Pi should be ready. Some commands
to consider using for updating your Raspberry Pi 3 are sudo apt-get update and sudo apt-get dist-upgrade for installing packages to their
latest versions for Pi. You need to make sure that I2C is enabled on the Raspberry Pi in order to use cmds like i2c detect for displaying the 
address of your sensor. In order to do that go to the Raspberry Pi configuration from start menu or type in terminal sudo raspi-config, 
then go to Interfaces and click on the I2C option to enable it if it hasn't already been enabled yet. 
 

# Unit Testing
In order to test whether or not the sensor is connected to the Raspberry Pi 3 properly you need to
open up a terminal on Pi and issue the command sudo i2cdetect -y 1 to list all the I2C addresses connected to the
Raspberry Pi 3. Additionally, once you see your address listed on the output now we can test the sensor by running
the python program from adafruit website. Follow the instructions on the adafruit website to install the python library
into Raspberry Pi 3 to run the simpletest.py that came with adafruit library for reading data from the sensor. The program
can be found in my github repository called simpletest.py and to compile/run it type in python simpletest.py. This command 
will not only compile it but run the python program if there are no errors in the file and after entering it the program will
execute to display the temperature readings every second. I have provided a link below to the open-sourced adafruit website 
which will show you step by step how to make the sensor read data by running the python program in terminal.
https://learn.adafruit.com/tmp006-temperature-sensor-python-library/software 

# Production Testing
When the python program ran successfully, it displayed the temperature from the sensor itself 
and object temperature just by pointing my finger towards it. The temperature readings prints
out every second and change based on me putting my hand close to it and far from it. 
The program is running on an infinite loop so you don't need to keep running it again and again
to see if the temperature values are changing. 

# Reproducible
I believe that my project is reproducible because I have provided detailed step by step instructions above
for anyone who wants to build my project on their own. If you follow my instructions and references carefully you should 
be able to recreate the same project that I made as well very easily with no problems or difficulties. I have provided files in my github repository such as my project's fitzing design file, proposal, schedule, budget, and all the necessary parts are listed in budget to build this final hardware project.
