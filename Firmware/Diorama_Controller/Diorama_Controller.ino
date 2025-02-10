/*
  Controller to light up a diorama and play a variety of sounds
  By: Nathan Seidle
  SparkFun Electronics
  Date: November 4th, 2024
  License: This code is public domain but you buy me a beverage if you use this and we meet someday (Beverageware license).

  We read five buttons.
  Four buttons play one of four MP3s
  One button turns on the light for 120 seconds.

  Runs on SparkFun RedBoard Plus: https://www.sparkfun.com/products/18158
  and the MP3 Shield: https://www.sparkfun.com/products/12660

  Does the audio sound like a monster? Covert the WAV or MP3 to 64kHz.

  Good online editor: https://twistedwave.com/online/ (cut, amplify, VBR save)
  Audio Cutter: http://mp3cut.net/
  MP3 Volume Increase: http://www.mp3louder.com/
  Down sample MP3s to 64kHz: http://online-audio-converter.com/
*/

#define pin_MP3_CS 6
#define pin_SD_CS 9
#define pin_light 10
#define pin_Volume A5

#define BUTTON_SIZE 5 //This is the number of buttons to read

//Hardware pin definitions
//The buttons array contains the hardware arduino pin numbers to buttons
//The first pin number is button0, 2nd is button1, etc.
//                              BTN 0,  1,  2,  3,  4,
const byte buttons[BUTTON_SIZE] = {A0, A1, A2, A3, A4};

#include <avr/wdt.h> //We need watch dog for this program

#include <vs1053_SdFat.h> //Mp3 Shield Library - http://librarymanager/All#VS1053_sdFat by Michael Flaga
vs1053 MP3player; //Create MP3 library object
SdFat sd; //Create object to handle SD functions

//Global variables
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
long buttonPressedTime[BUTTON_SIZE]; //This array stores the number of millis seconds since a button has been pressed
#define MINTIMEOUT 1500 //This is the minimum amount of time required between button plays, in ms, 250ms works ok

boolean playerStopped = false; //These are booleans used to control the main loop

long lastButton_ms = 0; //Keeps track of how long since last button press

unsigned long resetTime = 0;

char globalTrackName[20] = {0};

int redTrackNumber = 0;
int greenTrackNumber = 0;
int blueTrackNumber = 0;
int whiteTrackNumber = 0;

// We play a series of tracks for any given button, ie green003.mp3, then green004.mp3
// We need to loop them so we need to know the max number of tracks
// If there is white000 to white004 that's 5 max tracks
int maxRedTracks = 8;
int maxGreenTracks = 6;
int maxBlueTracks = 7;
int maxWhiteTracks = 5;

// You can make this time as long as you want,
// it's not limited to 8 seconds like the normal watchdog
#define TIMEOUTPERIOD 2000

#define petDog() resetTime = millis();  // This macro will reset the timer

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void setup()
{
  petDog(); //Pet the dog
  wdt_disable(); //We don't want the watchdog during init

  Serial.begin(115200);
  Serial.println("SparkFun Diorama Controller Booting...");

  //Setup buttons as inputs
  for (byte x = 0 ; x < BUTTON_SIZE ; x++)
  {
    pinMode(buttons[x], INPUT_PULLUP); //Define buttons as inputs with internal pull ups
    buttonPressedTime[x] = 0; //Reset all the button times
  }

  pinMode(pin_light, OUTPUT); //Define LED as output
  pinMode(pin_Volume, INPUT); //Read analog volume knob

  lightOff(); //Turn off the light

  initSD(); //Initialize the SD card
  initMP3Player(); // Initialize the MP3 Shield

  playTrackNumber(0); //Generic start up sound - green000.mp3

  Serial.println("Light sound controller online");

  watchdogSetup(); //Unleash the beast
}

void loop()
{
  petDog(); //Reset the watchdog timer

  int button = checkButtons(); //Returns the number of the first button pressed
  if (button > -1)
  {
    Serial.print("Button pressed: ");
    Serial.println(button);

    //Check to see if enough time has passed to accept this button press
    if (millis() - buttonPressedTime[button] > MINTIMEOUT)
    {
      Serial.println("Timeout passed so doing action");
      buttonPressedTime[button] = millis(); //Reset the amount of time to zero

      //lightOff();
      lightOn();

      //playTrackNumber(button); //Play this track

      //Instead of play track 0 to 4 we want to play a series of tracks
      //for each button (ie, green button will have track 000green, 001green, etc).
      playButton(button);
    }
  }

  //Turn off MP3 chip when not playing
  if (MP3player.isPlaying() == false && playerStopped == false)
  {
    Serial.println("Shutting down MP3");
    //MP3player.end(); //MP3 player is buzzing. This disables it.
    playerStopped = true;

    Serial.println("Deactivating light");
    lightOff();
  }

  updateVolumeKnob();
}

//Checks all the buttons
//Returns the first button that is pressed
int checkButtons(void)
{
  for (byte x = 0 ; x < BUTTON_SIZE ; x++)
  {
    petDog(); //Pet the dog

    if (digitalRead(buttons[x]) == LOW)
    {
      delay(10); //Debounce
      return (x);
    }
  }

  return (-1); //No button is pressed
}

//Plays a given track number
//Then turns off audio to reduce hissing
void playTrackNumber(byte trackNumber)
{
  playTrackName(getTrackName(trackNumber, "green"));
}

//Given a button (0 to 3), play through the tracks for that button
//ie, green000.mp3, green001.mp3, etc
void playButton(int buttonNumber)
{
  if (buttonNumber == 3) //Red
  {
    playTrackName(getTrackName(redTrackNumber, "red"));
    redTrackNumber++;
    redTrackNumber %= maxRedTracks;
  }
  else if (buttonNumber == 2) //Green
  {
    playTrackName(getTrackName(greenTrackNumber, "green"));
    greenTrackNumber++;
    greenTrackNumber %= maxGreenTracks;
  }
  else if (buttonNumber == 0) //Blue
  {
    Serial.println("Blue");
    Serial.print("track: ");
    Serial.println(getTrackName(blueTrackNumber, "blue"));
    playTrackName(getTrackName(blueTrackNumber, "blue"));
    blueTrackNumber++;
    blueTrackNumber %= maxBlueTracks;
  }
  else if (buttonNumber == 1) //White
  {
    playTrackName(getTrackName(whiteTrackNumber, "white"));
    whiteTrackNumber++;
    whiteTrackNumber %= maxWhiteTracks;
  }

}

//Based on a button number look up the correct track name
//Return a string that is the mp3 file name
//ie green001.mp3
char *getTrackName(byte trackNumber, char* buttonColor)
{
  sprintf(globalTrackName, "%s%03d.mp3", buttonColor, trackNumber);
  return globalTrackName;
}

//Plays a given track name
//Once track completes playing, audio is turned off to reduce hissing
void playTrackName(char * trackName)
{
  if (MP3player.isPlaying())
  {
    Serial.println("Interrupting track");
    MP3player.stopTrack(); //Stop any previous track
  }

  //MP3player.begin(); //Causes crackling and resets MP3 volume

  Serial.print("Playing: ");
  Serial.println(trackName);

  petDog(); //Pet the dog
  MP3player.playMP3(trackName);
  petDog(); //Pet the dog

  playerStopped = false; //Boolean for main loop to turn off MP3 IC
}

void lightOn()
{
  digitalWrite(pin_light, HIGH);
}

void lightOff()
{
  digitalWrite(pin_light, LOW);
}

//Read the analog pin
//As it changes, change the MP3 volume level
void updateVolumeKnob()
{
  const int averageSize = 16;
  static bool firstEntry = true;
  static int knobSpot = 0;
  static uint16_t knobReadings[averageSize];
  static int lastVolume = 0;

  int knobLevel = analogRead(pin_Volume);

  //Pre-fill array upon first entry
  if (firstEntry == true)
  {
    firstEntry = false;
    for (int x = 0 ; x < averageSize ; x++)
      knobReadings[x] = knobLevel;
  }

  knobReadings[knobSpot++] = knobLevel;
  if (knobSpot == averageSize)
    knobSpot = 0; //Wrap

  long knobTotal = 0;
  for (int x = 0 ; x < averageSize ; x++)
    knobTotal += knobReadings[x];

  int knobAverage = knobTotal / averageSize;

  //100 is pretty soft
  //30 is pretty loud
  int maxLoundness = 0;
  int minLoundness = 100;
  int volumeLevel = map(knobAverage, 0, 1023, minLoundness, maxLoundness);

  //Update the MP3 volume if it has changed
  if (lastVolume != volumeLevel)
  {
    lastVolume = volumeLevel;
    MP3player.setVolume(volumeLevel, volumeLevel);
  }

  //  Serial.print("knobLevel: ");
  //  Serial.print(knobLevel);
  //  Serial.print(" knobTotal: ");
  //  Serial.print(knobTotal);
  //  Serial.print(" knobAverage: ");
  //  Serial.print(knobAverage);
  //  Serial.print(" volumeLevel: ");
  //  Serial.print(volumeLevel);
  //  Serial.println();
}
