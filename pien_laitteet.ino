void pien_laitteet()
{
 select_btn_jannite = analogRead(VALINTA_PAINIKE) * (5.0 / 1023.0);
 back_btn_jannite = analogRead(PALUU_PAINIKE) * (5.0 / 1023.0);
 if(!sleep_mode){kirk_jannite = analogRead(VALO_ANTURI) * (5.0 / 1023.0);}
 akun_jannite = analogRead(AKUN_MITTAUS) * (5.0 / 1023.0);
 left_hall_jannite = analogRead(VASEN_HALL) * (5.0 / 1023.0);
 right_hall_jannite = analogRead(OIKEA_HALL) * (5.0 / 1023.0);

  if(select_btn_jannite<0.5) // onko valinta nappia painettu
  {
    select_nappi = true;
  }
    else
  {
    select_nappi = false;
  }

  if(back_btn_jannite<0.5)  // onko paluu nappia painettu
  {
    back_nappi = true;
  }
    else
  {
    back_nappi = false;
  }

  if(right_hall_jannite<0.5)  // jos oikea hall anturi tunnistaa
  {
    right_hall = true;
  }
    else
  {
    right_hall = false;
  }
  
  if(left_hall_jannite<0.5)  // jos vasen hall anturi tunnistaa
  {
    left_hall = true;
  }
    else
  {
    left_hall = false;
  }
  
  if(akun_jannite>akun_maksimi_jannite)
  {
    ladataan=true;
  }
    else
  {
    ladataan=false;
  }
  
   if(!sleep_mode){valon_maara = (kirk_jannite/akun_jannite) * 100;} // Lasketaan valon määrä prosentteina
  akun_taso = (akun_jannite - pienin_toiminta_jannite) / (akun_maksimi_jannite - pienin_toiminta_jannite) *100; // Lasketaan akun taso prosentteina 
} 