void heartrate_maaritys()
{
  if(!skip_heartrate)
  {
    if (!pox.begin()) 
    {
        skip_heartrate = true;
        if(heartrate_debug)
        {
          Serial.println("Sykeanturin määrittäminen epäonnistui");
        }
    }
      else
    {
      pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
      pox.setOnBeatDetectedCallback(lyonti_tunnistettu);
    }
  }
}

void lyonti_tunnistettu()
{
  pulse = true;
}

void heartrate_toiminta()
{
  if(!skip_heartrate)
  {
    pox.update();
    if(last_pulse < millis())
    {
      last_pulse = millis() + rate_delay;
      bpm = pox.getHeartRate();
      sptwo = pox.getSpO2();
    }
  }
}