# Automatic Drink Mixer
Ever wanted a Shirley temple but too lazy to pour it? Have a machine do it!


## Project Description
This automatic drink maker uses an Arduino Mega as the central controller. The Mega interfaces with an LCD screen via I2C, a membrane keypad, and a large red start button. The setup includes four DC motors, each driving a 3D-printed peristaltic pump with food-grade tubing for dispensing, and flowmeters positioned above the cup to measure liquid flow. Mason jars serve as liquid reservoirs, while the housing is crafted from wood and clear plastic. The housing has a plug for a wall outlet so the machine can be used wherever an outlet is accessible. 

The user places a cup in the machine, and then selects drink combinations and custom ratios from four options via the membrane keypad. After finalizing selections, the user presses the red button to start dispensing, with the LCD displaying a "Pouring" status. The system automatically controls each pump based on flowmeter feedback to achieve the desired ratios, ensuring a well-mixed drink. The code for this project was developed in the Arduino IDE. 

## Some Photos
![IMG_3263](https://github.com/user-attachments/assets/935f5c0e-4af8-4cb6-96b9-109a591cbdf5)!
![IMG_3262](https://github.com/user-attachments/assets/95cac1dc-1288-4bbd-9d9b-fc620b447e36)


## Youtube Video of Drink Maker 
[Automatic Drink Maker](https://youtu.be/md6ckqX8Wa8)

## Component and Supplies
Most of the materials used for this project weere scrap parts from other previous projects. Feel free to change this design to however you want it to look.
### Parts List 
* LCD Screen with I2C 
* Membrane Keyboard
* large button
* Arduino Mega 
* Flow Meters
* Jumpers
* Heat Shrink
* ABS
* Ball Bearings 
* Zip ties
* Wood
* 12-volt power supply with outlet cable
* Food grade tubing

## Software 
Software used for this project was the Arduino IDE, Cura, and Fusion360.

## The Pumps
Any 3D printer that can handle ABS will work, but the design was based on [GreatScottLab](https://www.instructables.com/member/GreatScottLab). The pumps were slightly modified to fit our tubing by giving the design more clearance and using a Dremel. Using a 3D-printed pump worked surprisingly well, but if you can afford it, you should buy a pump instead unless you have all the parts lying around.

## Comments 
This project is not fully finished right now. The code which is in this repository can be used as a reference but DOES NOT function right now. Using pointers could fix many of the issues in the code but not too sure as the group is too busy with school right now to revisit this. This project was completed in about a week and was fun to develop. Our design also makes it pretty easy to add more or fewer drinks depending on the desired amount of drinks you would like access to.



