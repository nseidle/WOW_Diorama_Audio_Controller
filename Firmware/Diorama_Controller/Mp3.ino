//Initialize the SD card
void initSD()
{
  if (sd.begin(pin_SD_CS, SPI_HALF_SPEED) == false)
  {
    Serial.println("No SD card found.");
  }
}

//Begin MP3 shield, set the volume and mono mode.
void initMP3Player()
{
  MP3player.begin(); // Init the mp3 player shield

  //Volume level
  //30 is probably max loudness
  //100 is pretty soft
  MP3player.setVolume(100, 100); // MP3 Player volume 0=max, 255=lowest (off)

  MP3player.setMonoMode(1); // Mono setting: 0=off, 1 = on, 3=max
}
