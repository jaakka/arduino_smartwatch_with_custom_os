void os_init()
{
 // Serial.println("Muistikortilla on tiedostoja "+String(lista_tiedostoista())); //[muistikortti.ino]
  String maaritys_tiedoston_data = lue_tiedosto(maaritys_tiedosto); //luetaan määritystiedosto config joka on tiedostomuotoa patonki
  bool jotain_puuttui = false;

  String uus_nimi = poimi_arvo(maaritys_tiedoston_data,"name");
  if(uus_nimi == "")
  {
    if(config_load_debug)
    {
      Serial.println("Kellon nimen määritystä ei löytynyt, käytetään oletus nimeä.");
    }
    jotain_puuttui=true; //tallentaa lopuksi jos kortilla ei ollut jotain, mutta ei tarvitse tallentaa jos kaikki oli kortilla
  }
  else
  {
    kellon_nimi=uus_nimi;
    if(config_load_debug)
    {
      Serial.println("Kellon nimeksi muutettiin " + kellon_nimi); //kellon nimi on string joten ei pitäisi tulla ongelmia
    } 
  }

 
  String uus_home_app = poimi_arvo(maaritys_tiedoston_data,"home");
  if(uus_home_app == "")
  {
    if(config_load_debug)
    {
      Serial.println("Oletus koti sovellusta ei ollut määritetty, käytetään oletus");
    }
    jotain_puuttui=true; //tallentaa lopuksi jos kortilla ei ollut jotain, mutta ei tarvitse tallentaa jos kaikki oli kortilla
  }
    else
  {
    if(config_load_debug)
    {
      Serial.println("Oletus kotisovellus muuttui "+ uus_home_app); //tässä ei pitäisi tulla ongelmaa koska uus_ on string
    } 
    home_app = uus_home_app.toFloat(); //muunnetaan string intiks
  }

  String uus_menu_app = poimi_arvo(maaritys_tiedoston_data,"menu");
    
  if(uus_menu_app == "")
  {
    if(config_load_debug)
    {
      Serial.println("Oletus päävalikko sovellusta ei ollut määritetty, käytetään oletus");
    }
    jotain_puuttui=true; //tallentaa lopuksi jos kortilla ei ollut jotain, mutta ei tarvitse tallentaa jos kaikki oli kortilla
  }
    else
  {
    if(config_load_debug){Serial.println("Oletus päävalikko sovellus muuttui " + String(uus_menu_app));}
    menu_app = uus_menu_app.toFloat(); //muunnetaan string intiks
  }

  String uus_vuosi = poimi_arvo(maaritys_tiedoston_data,"y");
  String uus_kuukausi = poimi_arvo(maaritys_tiedoston_data,"m");
  String uus_paiva = poimi_arvo(maaritys_tiedoston_data,"d");

  if(uus_vuosi == "" || uus_kuukausi == "" || uus_paiva == "")
  {
    if(config_load_debug)
    {
      Serial.println("Päivämäärän kaikkia tarvittavia määrityksiä ei löytynyt joten käytetään vakio asetuksia.");
    }
    jotain_puuttui=true; //tallentaa lopuksi jos kortilla ei ollut jotain, mutta ei tarvitse tallentaa jos kaikki oli kortilla
  }
    else
  {
    if(config_load_debug)
    {
      Serial.println("Paivamaara muutettiin " + uus_paiva + "/" + uus_kuukausi + "/" + uus_vuosi); //uus_ muuttujat ovat string joten ei pitäisi tulla virhettä
    } 
    vuosi=uus_vuosi.toFloat();
    kuukausi=uus_kuukausi.toFloat(); //muutetaan stringit inteiks
    paiva=uus_paiva.toFloat();
  }

  String uus_tunnit = poimi_arvo(maaritys_tiedoston_data,"h");
  String uus_minuutit = poimi_arvo(maaritys_tiedoston_data,"m");
  String uus_sekunnit = poimi_arvo(maaritys_tiedoston_data,"s");

  if(uus_tunnit == "" | uus_minuutit == "" | uus_sekunnit == "")
  {
    if(config_load_debug)
    {
      Serial.println("Ajan kaikkia tarvittavia määrityksiä ei löytynyt joten käytetään vakio asetuksia.");
    }
    jotain_puuttui=true; //tallentaa lopuksi jos kortilla ei ollut jotain, mutta ei tarvitse tallentaa jos kaikki oli kortilla 
  }
    else
  {
    if(config_load_debug)
    {
      Serial.println("Aika muutettiin " + uus_tunnit + ":" + uus_minuutit + ":" + uus_sekunnit);
    }
    sekunnit=uus_sekunnit.toFloat();
    minuutit=uus_minuutit.toFloat(); //muutetaan stringit inteiks
    tunnit=uus_tunnit.toFloat();
  }

  if(jotain_puuttui)
  {
    if(config_load_debug)
    {
      Serial.println("Koska kello teki jollekkin arvoilla määrityksiä, ne tallennettiin.");
    }
    tallenna(); //Tallennetaan uudet määritykset kortille
  }
    else
  {
    if(config_load_debug)
    {
      Serial.println("Kaikki  määritykset ladattiin tiedostosta onnistuneesti!");
    }
  }
  aloita_sovellus(home_app); //aloitetaan sovelluksen lataus
}