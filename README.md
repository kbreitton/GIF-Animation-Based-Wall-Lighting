#Introduction
"Dynamic Image-based Immersive Lighting" describes a system of modular LED light panels that can be easily put together in any rectangular organization and play a GIF. To goal is to introduce a scalable, designer-friendly platform for creating immersive lighting in entertainment environments. One does not need any background in programming to have the light panels play a GIF you want it to. Additionally, as an embedded system, this platform allows the incorporation of sensing to modify GIFs in real time depending on sensor data. This is possible due to this project's heavy dependence on OpenCV to transform images. The current implementation uses a gesture sensor that can, for example, perspective transform images to the left when one swipes left over the sensor. Finally, this project has a basic webapp where one can navigate to a website, upload a GIF, and play it on the LED panels in order to demonstate cloud functionality.

This is the github repository for all the software written to get it working on a Raspberry Pi B+. With the exception of a basic webapp, everything in written in C++. This document will explain how to get all the software up and running to play GIFs, and will briefly cover the necessary hardware setup to have GIFs displayed *correctly*.

#Dependencies
This project is fully tested on a Raspberry Pi B+. In order to run this software to work, it requires these libraries: [OpenCV](http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html) , [wiringPi](http://wiringpi.com/download-and-install/) , and [ImageMagick](http://www.imagemagick.org/script/install-source.php). In order get the webapp working for remote control, you also need to install [Meteor](http://meteor-universal.tumblr.com/).

Hardware-wise, these this software is specifically setup to run with [LPD8806 LED strips](https://www.adafruit.com/products/306) 

#Installation and Usage
Clone this repository with `git clone git@github.com:ese-519/xlab.git`
From the command line, navigate to the directory `xlab/xlab-node/lights` and then run `make`.
If all the requires libraries were installed correctly, everything should compile just fine. Afterwards, the output executable you care about running will be called `playGIF` and it is located in `bin/`. From the command line, running `playGIF` will need two arguments: the path to the GIF you want to play, then the duration in milliseconds you want to play it. 

Additionally, `playGIF` needs to be run in `sudo`. It is recommended (as well as for the webapp to work) to change permissions on `playGIF` so you it will automatically run with `sudo`. From this project's root directory, run:
```
chmod +s bin/playGIF
chown root bin/playGIF
```

Finally, before you can actually light up some LPD8806 strips, you need to make sure SPI is enabled on the Raspberry Pi. Run `sudo raspi-config` and enable SPI from its menu.

If everything is working correctly, and you also correctly wired the LPD8806 strips according to the [wiringPi pinout](http://wiringpi.com/pins/), from this project's root directory you should be able to run e.g.:
`bin/playGIF bin/images/rainbow.gif 5000`

where a GIF called "rainbow.gif" will be played for 5 seconds (5000 millliseconds)

#Basic Hardware Setup
As it is currently setup, the software needs the LPD8806 strips tos be cut in sections of six LEDs, and every strips' Data and Clock pins are connected in series. Each "panel" currently is defined to have 36 LEDs -- six LPD8806 strips where each strip contains six LEDs. You then connect one "panel" to the next by connecting the last strip's pins to the first strip's pins of the next panel. This daisy chain of panels can be done "ad infinitum". How long a "row" of panels is, is completely defined in software. 
Power is supplied in both series and parallel: using a PC power supply, a maximum of about about 144 LEDs are able to be powered in series without noticable brightness drop. After that mark, the next 144 LEDs need to be powered in parallel from the first set (though these next 144 LEDs will be powered in series together).

#Configuration
In order to change how many "rows" or "columns" of panels there are and have GIFs play correctly (or even change the number of LEDs within a panel), currently you must edit the `Controller.hpp` file, found in `include/`.

All you have to do is edit these lines:
```
const uint8_t leds_per_panel = 36;
const uint8_t cols_leds_per_panel = 6;
const uint8_t rows_leds_per_panel = 6;
const uint8_t cols_panels = 3;
const uint8_t rows_panels = 3;
```
which should be self-explanatory.

Then after editing, run `make` again from the project root directory and you are good to go.

#Webapp control
The Raspberry Pi running this software can additionally run a web server where you can navigate to a webpage, upload a GIF of your choice, and play it on the LED panels. Code for this is found in `web-app-meteor/`. Assuming you have installed Meteor on the Pi correctly, simply nagivate to `web-app-meteor/` and run `meteor`. This command will result in the Pi starting a webserver that you can then connect to if you are on the same network. Before you run it though, you must edit the `server/server.js` file and modify the `projPath` variable so that it points to the proper location where you installed things on the Pi. `projPath` should point to the `bin/` directory of the compiled executables.

#Handling sensor data
The project's use of OpenCV allows one to transform images in real-time such that one can manipulate images according to sensor data. Currently, this project can incorporate sensor data from a [gesture sensor](https://www.sparkfun.com/products/12787) from Sparkfun and, for example, perspective transform GIFs to the left when one swipes left over the sensor.

How to transform images as one likes using OpenCV is beyond the scope of this document. The first resource to go to about how to transform images in OpenCV is to check out its [documentation](http://docs.opencv.org/2.4/modules/imgproc/doc/geometric_transformations.html). In this project, handling sensor data is done through two classes: `ImageProcessor` which in this case does all the image pre-processing to transform them in real time,  and `SensorHandler`, which uses the low-level gesture sensor driver to get gesture states. The relevant variables/functions in ImageProcessor in this implemenation are:
```
cv::Mat _lambda_left_gest;
cv::Mat _lambda_right_gest;
cv::Mat _lambda_up_gest;
cv::Mat _lambda_down_gest;
```

and 
```
void determinePerspTransforms(const cv::Mat& input);
cv::Mat perspTransIm(const GESTURE_STATE& gesture_state);
```

I adapted this [perspective transformation example](http://opencvexamples.blogspot.com/2014/01/perspective-transform.html) to get things working as it does now.

