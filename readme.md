WOW Story Time Tree
==============

The story time tree exhibit allows children to view a diorama through a small window. Pressing a button plays sounds of nature, a story teller, or other tracks related to the scene. When a button is pressed the scene is illuminated. The handset is a modified telephone and phone hook to increase reliability and reduce cost. The knob controls volume. Each button plays a series of tracks, looping if the user continues to press the button.

![The story time scenes lit up](https://raw.githubusercontent.com/nseidle/WOW_Diorama_Audio_Controller/main/Story_Time_Tree_Exhibit.png)

The system monitors the state of 5 buttons. When a button is pressed a string of LEDs is lit and plays the corresponding MP3 track. I designed a custom shield to allow for JST connections to each channel (LED+button). 

Materials used:

* [SparkFun RedBoard Plus](https://www.sparkfun.com/sparkfun-redboard-plus.html)
* A whole bunch of [Arcade Buttons](https://www.sparkfun.com/products/9336)
* [SparkFun MP3 Shield](https://www.sparkfun.com/products/12660)
* [MicroSD Card](https://www.sparkfun.com/products/11609) (Any size up to 64GB behemoths should do)
* [10k Trimpot for volume](https://www.sparkfun.com/products/9806)
* [Metal volume knob](https://www.sparkfun.com/silver-metal-knob-14x24mm.html)
* Custom Arduino R3 shield (this repo, see hardware folder) to interface to five buttons and one LED strip
* [5x 3-pin JST cable](https://www.sparkfun.com/jst-to-breadboard-jumper-3-pin.html) connections to the illuminated buttons
* [2-pin JST cable](https://www.sparkfun.com/jst-jumper-2-wire-assembly.html) connection to the LED illumination of the scene

3D Printed Parts
-------------------
The phone handset is cut and modified with a 3D printed part:

<script src="https://embed.github.com/view/3d/nseidle/WOW_Diorama_Audio_Controller/main/Models/WOWPhoneAttachment.stl"></script>

License Information
-------------------
The **code** is drinkware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!

Please use, reuse, and modify these files as you see fit. Please maintain attribution to SparkFun Electronics and release anything derivative under the same license.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.
