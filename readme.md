WOW Museum Body Exhibit
==============

The body exhibit allows children to press one of twelve buttons and see that part of the skeletal or organ system light up. An audio track saying the organ/bone name in English and Spanish is heard. An information audio track is heard if the button is pressed a second time. 

![The body exhibit lit up](https://raw.githubusercontent.com/nseidle/Body_Exhibit/master/Body-Exhibit-Front.jpg)

The system monitors the state of 12 buttons. When a button is pressed a string of 10 LEDs is lit and plays the corresponding MP3 track. I designed a custom shield to allow for JST connections to each channel (LED+button). 

The Sandwich
===============

The front face was clear plexiglass, a mylar graphic, then 1" compressed fiber board that was routed out to created the light boxes. I don't have the artwork for the body; I believe it was a educational poster that was printed on mylar or other semi-transparent material. The backer board was 3/8" thin and had the LED strips attached with hot glue. The arcade buttons were then drilled through the stack-up. The entire sandwich was pretty heavy but reasonably easy to handle. The control electronics were mounted to the back of the backer board with velcro for easy disconnect. The sandwich was spaced off the wall (because the buttons stick out the back) using 2x2s. The 2x2s were in turn attached to studs on the wall for a secure attachment.

Materials used:

* [SparkFun Mega2560](https://www.sparkfun.com/products/11007)
* A whole bunch of [Arcade Buttons](https://www.sparkfun.com/products/9336)
* [SparkFun MP3 Shield](https://www.sparkfun.com/products/12660)
* [MicroSD Card](https://www.sparkfun.com/products/11609) (Any size up to 64GB behemoths should do)
* [SparkFun Audio Amplifier](https://www.sparkfun.com/products/11044)
* [10k Trimpot for volume](https://www.sparkfun.com/products/9806)
* [Couple 10k resistors](https://www.sparkfun.com/products/11508)
* [SparkFun MegaShield Kit](https://www.sparkfun.com/products/9346) (used just the headers to connect to custom shield)
* [5V Wall Adapter](https://www.sparkfun.com/products/12889)
* [DC Barrel Jack](https://www.sparkfun.com/products/119)
* [Waterproof Speakers](http://www.amazon.com/gp/product/B001ES8X9M) because you need speakers that can mount flat on a wall and not be damaged by small, poking fingers

The custom shield uses a bunch of passives:
* 12 x [2N3904 NPN Transistors](https://www.sparkfun.com/products/521)
* 12 x [4-pin jumper connectors](https://www.sparkfun.com/products/9916)
* 12 x [10k Ohm resistors](https://www.sparkfun.com/products/11508) are optional. I used the internal pullups instead.
* 12 x [330 Ohm resistors](https://www.sparkfun.com/products/11507)
* 12 x [47 Ohm resistors](https://www.sparkfun.com/products/10969) from resistor kit
* [String of white LEDs](http://www.amazon.com/gp/product/B00P7OMKD4) cut into lengths of 10 LEDs
* Lots of [ribbon wire](https://www.sparkfun.com/products/10647)

I experimented with some of the cheap amplifiers found on Amazon. The SparkFun class-D amplifier was louder and a lot more clean than the TDA42934 based stereo amplifiers. The original shield design had a space for the TDA42934 amplifier but I'm going to change that on the next version.

The string of LEDs is the type that has three thin wires and a blob of epoxy over a 1206 sized SMD LED. The wire is enamelized so you have to burn the enamel off before you can solder to it. I use a blob of solder on the end of my iron and hold it there for 5-10 seconds to burn the enamel off. You should probably do so in a well ventilated because it smells pretty rough.

![The internal wiring of the body exhibit](https://raw.githubusercontent.com/nseidle/Body_Exhibit/master/Body-Exhibit-Rear.jpg)

To prep the audio amp for external control: cut the small jumper, solder in two 10k PTH resistors, and then the 10k trim pot. This will allow user controllable volume. It is *very* loud and *very* clean with a good speaker and a wall power supply. Powering the MP3 player and audio amp via USB will introduce buzzing; I used an external 5V wall supply to power the amp directly.

The SparkFun Mega connects to the MP3 Shield via SPI pins and a handful of control pins. This was a bit of a hassle because the Mega has SPI pins in a weird place. In the future I will probably wire the ISP header from the Mega to the 2x6 pin SPI/ISP connector on the shield.

The MP3 shield "-" and "R" pins are wired to the "-" and "+" pins of the "In" port of the audio amp. The out pins of the audio amp are connected to the speaker. The audio amp's S or shutdown pin is connected to A1 so that we can shut it down when not playing an MP3.

The Mega2560 has a bug in its bootloader that doesn't allow normal usage of the watchdog. Because this is an exhibit that can be left on for weeks at a time I needed a method to prevent system hangs. I found a good solution [here](http://forum.arduino.cc/index.php?topic=62813.25) - thanks draythomp!

Another lesson: Label all the wires, sometimes in multiple places. When the wiring gets rough the labels are what will keep you sane. 

License Information
-------------------
The **code** is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!

Please use, reuse, and modify these files as you see fit. Please maintain attribution to SparkFun Electronics and release anything derivative under the same license.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.
