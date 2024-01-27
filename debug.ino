void vianetsinta()
{
  if ((millis() > last_debug_msg) && (time_debug || akku_debug || sd_debug || pienlaitteet_debug || gyroscope_debug || heartrate_debug)) //katsotaan että edes joku debug mode on päällä muuten menee turhaa tehoa
  {
    last_debug_msg = millis() + debug_msg_delay; //odotetaan niin kauan kun on määritetty
    
    if(time_debug)
    {
      Serial.println(String(lisaa_nolla(tunnit))+":"+String(lisaa_nolla(minuutit))+":"+String(lisaa_nolla(sekunnit))+" "+String(vuosi)+"/"+String(kuukausi)+"/"+String(paiva));
    }

    if(akku_debug)
    {
      Serial.println("| BAT:"+String(akun_taso)+"% PTJ:"+String(pienin_toiminta_jannite)+"v / MXJ"+String(akun_maksimi_jannite)+"v J"+String(akun_jannite)+"v LAD:"+String(truefalse(ladataan))+"|");
    }
  
    if(pienlaitteet_debug)
    {
      Serial.println("| BRG"+String(valon_maara)+"% / "+String(kirk_jannite)+"v |"+"valinta "+String(truefalse(select_nappi))+" / "+String(select_btn_jannite)+"v | "+"paluu "+String(truefalse(back_nappi))+" / "+String(back_btn_jannite)+"v | "+"ohall "+String(truefalse(right_hall))+" / "+String(right_hall_jannite)+"v |" +"vhall "+String(truefalse(left_hall))+" / "+String(left_hall_jannite)+"v |");
    }

    if(gyroscope_debug)
    {
      if(Acc)
      {
        Serial.print(" Ax:" + String(xAcc) + ",Ay:" + String(yAcc) + ",Az" + String(zAcc));
      }

      if(Gyro)
      {
        Serial.print(" Gx:" + String(xGyro) + ",Gy:" + String(yGyro) + ",Gz" + String(zGyro));
      }

      if(Mag)
      {
        Serial.print(" Mx:" + String(xMag) + ",My:" + String(yMag) + ",Mz" + String(zMag));
      }

      Serial.println("");
    }

    if(heartrate_debug)
    {
      Serial.println("Syke:" + String(bpm) + "bpm / Sp2:" + String(sptwo) + "%");
    }
  }
}