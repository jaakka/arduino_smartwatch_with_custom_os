void aloita_gyroscope()
{
  if(!skip_gyroscope)
  {
    if (!IMU.begin()) //Tarkistetaan vastaako gyroscope moduuli
    {
      skip_gyroscope = true;
      if(gyroscope_debug) //onko viankorjaus päällä
      {
        Serial.println("Gyroscopen määrittäminen ei onnistunut!");
      }
    }
  }
}

void gyroscopen_toiminta()
{
  if(!skip_gyroscope)
  {
    if(last_gyroscope_time < millis())
    {
      last_gyroscope_time=millis() + gyroscopen_luku_viive;

      if(Acc) //tarvitaanko tätä arvoa?
      {
        if (IMU.accelerationAvailable()) //tarkistetaan onko arvoja saatavissa
        {
          IMU.readAcceleration(xAcc, yAcc, zAcc);
        }
      }

      if(Gyro) //tarvitaanko tätä arvoa?
      {
        if (IMU.gyroscopeAvailable()) //tarkistetaan onko arvoja saatavissa
        {
          IMU.readGyroscope(xGyro, yGyro, zGyro);
        }
      }

      if(Mag) //tarvitaanko tätä arvoa?
      {
        if (IMU.magneticFieldAvailable()) //tarkistetaan onko arvoja saatavissa
        {
          IMU.readMagneticField(xMag, yMag, zMag);
        }
      }
    }
  }
}