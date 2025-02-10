

void(* resetFunc) (void) = 0; // Declare reset function @ address 0

void watchdogSetup()
{
  cli();  // Disable all interrupts
  petDog(); // Reset the WDT timer
  MCUSR &= ~(1 << WDRF);

  /*
    WDTCSR configuration:
    WDIE = 1 :Interrupt Enable
    WDE = 1  :Reset Enable - I won't be using this on the 2560
    WDP3 = 0 :For 1000ms Time-out
    WDP2 = 1 :bit pattern is
    WDP1 = 1 :0110  change this for a different
    WDP0 = 0 :timeout period.
  */

  // Enter Watchdog Configuration mode:
  WDTCSR = (1 << WDCE) | (1 << WDE);
  // Set Watchdog settings: interrupte enable, 0110 for timer
  WDTCSR = (1 << WDIE) | (0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (0 << WDP0);

  sei(); // Enable interrupts

  Serial.println("Watchdog configured");
}

// Watchdog timer interrupt
ISR(WDT_vect)
{
  if (millis() - resetTime > TIMEOUTPERIOD)
    resetFunc();
}
