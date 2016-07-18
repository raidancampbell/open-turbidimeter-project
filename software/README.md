# Software

This directory contains the _firmware_ for the turbidimeter. These are the files that are compiled and uploaded to the microcontroller and provide the user interface, measurement, and calibration functions.

##Notes
-----
 - All temperature correction has been removed: the hardware was not documented properly.
 - All GSM code has been compiled out: several issues prevented proper compilation


###Contents
-----

The folder called ```turbidimeter``` is the [Arduino](http://arduino.cc/en/main/software) project folder for the turbidimeter firmware. This can go anywhere and you can rename it, but the ```.ino``` file must have the save name as the parent folder when working in the Arduino IDE. This is the file that you most likely be working with if you want to change how the turbidimeter operates.

The ```libraries``` folder contains the extra libraries needed to compile the Arduino sketches, providing the ability to send/receive text messages, store calibration data, etc. These need to be made available to the Arduino compiler by putting them in a place it knows about. One sure way to do this is to import them using the "Sketch>Import Library" utility in the Arduino IDE. Depending on how you have installed Arduino, this should have the effect of copying the files into the ```C:/Users/You/Documents/Arduino/libraries``` folder (Windows) or ```~/sketchbook/libraries``` folder (Mac/Linux). Note that some of the libraries have the same name as those prepackaged with the Arduino software. They are different (usually slightly modified for interoperability reasons); if you run into errors, make sure you are using the right ones.
