void aloita_muistikortin_lukija()
{
  if (!SD.begin(SD_CS)) 
  {
    if(sd_debug){Serial.println("Muistikortinlukijan määrittäminen epäonnistui!, mahdolliset syyt: lukian kytkentä tai viallinen kortti.");} //vian määritys
    tft.setTextSize(2); //asetetaan tekstin koko
    tft.setTextColor(luo_rgb(255,0,0)); //asetetaan punainen väri
    tft.setCursor(43, 190); //valitaan mihin piirretään
    tft.println("MuistiOngelma!"); //ilmoitetaan näytöllä virheestä
    while (1); // ei anneta ohjelman edetä.
  }
}

bool onko_olemassa(String etsittava_tiedosto)
{
  File root = SD.open("/");//avataan juurikansio
  bool oliko_tiedostoa = false;
  while (true) 
  {
    File tiedosto = root.openNextFile(); //avataan seuraava filu
    
    if (!tiedosto) 
    { 
      // ei enää tiedostoja katkaistaan loop
      break;
    }
    if(etsittava_tiedosto == String(tiedosto.name()))
    {
      oliko_tiedostoa = true;
      break;
    }
    tiedosto.close(); //suljetaan selattu tiedosto
  }
  root.close(); //suljetaan kansio
  return oliko_tiedostoa; //palautetaan oliko vai ei
}

String lista_tiedostoista()
{
  File root = SD.open("/");//avataan juurikansio
  String lista_niista="";

  while (true) {
    File tiedosto = root.openNextFile(); //avataan seuraava filu
    if (!tiedosto) { 
      // ei enää tiedostoja
      break;
    }
    lista_niista=lista_niista+","+String(tiedosto.name()); //lisätään listalle
    tiedosto.close(); //suljetaan selattu tiedosto
  }

  root.close(); //suljetaan kansio
  return lista_niista; // palautetaan tiedostojen lista
}

void tallenna(){ //aika kohassa tällähetkellä minutin välein tallennus
    SD.remove(maaritys_tiedosto);
   File tiedosto = SD.open(maaritys_tiedosto, FILE_WRITE); // Avaa tiedosto kirjoitusta varten
  if (tiedosto) {
    tiedosto.println("name='"+String(kellon_nimi)+"'");
    tiedosto.println("home='"+String(home_app)+"'");
    tiedosto.println("menu='"+String(menu_app)+"'");
    tiedosto.println("y='"+String(vuosi)+"'");
    tiedosto.println("m='"+String(kuukausi)+"'");
    tiedosto.println("d='"+String(paiva)+"'");
    tiedosto.println("h='"+String(tunnit)+"'");
    tiedosto.println("m='"+String(minuutit)+"'");
    tiedosto.println("s='"+String(sekunnit)+"'");
    tiedosto.close(); // Sulje tiedosto
    Serial.println("Uudet arvot tallennettu tiedostoon.");
  } else {
    Serial.println("Virhe tiedoston avaamisessa");
  }
}

String lue_tiedosto(String tiedosto)
{
  if(sd_debug)
  {
    Serial.println("Aloitetaan tiedoston " + String(tiedosto)+" lukeminen");
  }
  String keratty_data="";
  File kasiteltava_tiedosto = SD.open(tiedosto);
  if (kasiteltava_tiedosto) 
  {
    while (kasiteltava_tiedosto.available()) 
    {
      char merkki = kasiteltava_tiedosto.read();
      if(sd_debug_read){Serial.write(merkki);}
      //kasataan data kirjaimista
      keratty_data = keratty_data + String(merkki);
    }
    kasiteltava_tiedosto.close();
    if(sd_debug){Serial.println("Tiedosto "+String(tiedosto)+" on nyt luettu!");}
    return keratty_data;
  } 
    else 
  {
    if(sd_debug){Serial.println("Virhe avatessa tiedostoa "+String(tiedosto));}
  }
}