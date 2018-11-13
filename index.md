# Nov 13 2018
This week I demonstrated my functional hardware can read data from my sensor and display the results on the screen. Firstly, I was able to figure out how to connect to my Raspberry Pi using Remote Desktop Connection and issue the i2c detect command to see my address was working on my PCB board successfully. My project is going well the PCB is powered on right and I can read temperature data from my sensor just by moving my finger close to it. My financial status is good my hardware was not damaged during production and testing which will not delay time creating my project. I am still using the same materials for building my capstone project as stated in my proposal. Furthermore, I am still on track based from my project schedule because I have completed by this week powering up my Raspberry Pi with PCB to show that I can read data from my sensor. There are links at the bottom of this weeks discussion to show proof of powering on my developmental platform with PCB attached to it and reading data from my sensor.

[PCB Powered Up](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/PCB_PowerUp.png)

[I2C on PCB](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/I2C_PCB.PNG)

[My Sensor's Data](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/TempDataCapture.PNG)




# Nov 6 2018
This week I soldered my PCB for my TMP006 IR Temperature Sensor, Raspberry Pi 3 with the help of Vlad and Kelly in the prototype lab. Before my sensor was not picking up my address on the Raspberry Pi 3. However, I told Vlad the problem and we both troubleshooted the issue and found out the Ground and SDA pins were not picking up on multimeter. I had to strip both ends of a wire and connect it from the Ground pin on Raspberry Pi to my via trace connecting to GND pin for my Temperature Sensor from the top of the PCB. Then I had to connect another wire from Add1 to the via trace connecting to my SDA pin on the bottom of my PCB. Afterwards, my address is shown when I issue the I2C detect command the same way as I did using the breadboard and jumper wires for my connections. But this time I using the PCB for connecting my sensor to Raspberry Pi and I am getting the same results so I should now be able to get data from my Temperature Sensor. I am currently testing out if my sensor can detect temperature data and readings from any object close to it in order to display it on the terminal. My project has not changed I am still using both my Temperature Sensor and Raspberry Pi as stated in my Proposal. I am still on track based from my project schedule because I have completed the PCB Soldering this week and now I am working on the milestone for next week. I still need to figure out how to get my data from sensor by next week but other than that the project is going well. My financial status is good I am using the same materials in my budget but it could change if my materials are damaged from testing it. There are links below this weeks discussion to my soldered PCB from the top to bottom and on the Raspberry Pi below to show what I did for this week.

[PCB Top Soldered](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/PCBTop.jpg)

[PCB Bottom Soldered](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/PCBBottom.jpg)

[PCB on Raspberry Pi](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/PCBPi.jpg)

# Oct 30 2018
This week I will have designed a PCB for my TMP006 IR Temperature Sensor and Raspberry Pi 3. I should get it soon from the prototype lab to be able soldering it for next week. Based on my project schedule I am still on track as long as I get my PCB designed and soldered by next week. My project has not changed based from my proposal I am still using the same materials from before to build it. My financial update is good I am still under budget and most of the stuff I need I already have so their is no need to buy more materials for my project. I have included the fritzing file for my project in my respository to look at how I designed the pcb. Here are links at the bottom of this weeks discussion on my design files for breadboard, schematic, and pcb diagrams.

[My breadboard diagram](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/Thermometer%20Circuit%20Diagram_bb.png)

[My schematic diagram](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/Thermometer%20Circuit%20Diagram_schem.png)

[My pcb diagram](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/Thermometer%20Circuit%20Diagram_pcb.png)

# Oct 23 2018
This week I soldered my TMP006 IR Temperature sensor, connected wires from my sensor to broadcom development platform and have completed getting my sensor to detect my I2C address on Raspberry Pi 3. I researched my sensor's pin layout to determine how to change my default I2C address from (0x40) to (0x46) for my temperature sensor. I found out to get my I2C address you have to connect wires from Add0 to SDA and Add1 to VCC from my sensor connected to breadboard. I have provided links at the bottom of this weeks discussion for observing my breadboard circuit and I2C address from my sensor below.  Based on the project schedule I am on track because it shows that week eight I have to complete the breadboard milestone. Next week I have to design a PCB Board, I already emailed the prototype lab my gerber files of my circuit diagram in order to design one. The project has not changed I am still using the same materials like my TMP006 IR Temperature Sensor and Raspberry Pi 3 based from my Proposal.

[My breadboard circuit](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/breadboard_circuit_diagram.png)

[My fritzing circuit](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/Thermometer%20Circuit%20Diagram_bb.png)

[My sensor's I2C address](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/I2CAddress.PNG)

# Oct 16 2018 
This week I will solder my header pins for my temperature sensor on the breadboard and connect them with my developmental platform.

# Oct 9 2018
I have my parts with me and working on fritzing my connections on breadboard.

# Oct 2 2018
Proof of purchase is due and here are pictures of my parts that I ordered at store.
[pictures of my parts](https://raw.githubusercontent.com/n01103934/Thermometer/master/images/parts.png)

# Sept 25 2018
Worked on budget for project and I have completed it. I have provided a excel document of the budget in my Github respository.

# Sept 18 2018
Worked on project schedule and submitted it. I provided a microsoft project document of the schedule in my Github respository.

# Sept 11 2018
Worked on proposal and submitted it. I also provided a word document and pdf of proposal in my Github respository.

# Sept 4 2018
Worked on and completed lighting up an LED on the Raspberry Pi 3. 
