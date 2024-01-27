void ajan_lasku() 
{
  if (millis() > last_time) //jos nykyinen aika on isompi kuin tavoitteeksi asetettu aika
  {
    last_time = millis() + 1000; // asetetaan tavoitteeksi nykyinen aika + 1000ms eli 1s
    sekunnit++;
    if(sekunnit >= 60) //jos sekuntteja enemmän kun 60 lisätään minuutti
    {
      sekunnit = 0; //nollataan
      minuutit++;   //lisätään 1
      tallenna();
      if(minuutit >= 60) //jos minuutteja enemmän kun 60 niin lisätään tunti
      {
        minuutit = 0; //nollataan
        tunnit++; //lisätään 1
        if(tunnit >= 24) //jos tunteja enemmän ku vuorokausi lisätään päiviä
        {
          tunnit = 0; //nollataan
          seuraava_paiva(); //lisätään pv, alempana functio
        }
      }
    }
  }
}

void seuraava_paiva()
{
  // Tarkista karkausvuosi
  bool onKarkausvuosi = ((vuosi % 4 == 0) && (vuosi % 100 != 0)) || (vuosi % 400 == 0);

  // Määritä päivien lukumäärä kuukausittain, ottaen huomioon karkausvuoden
  int kuukausienPituudet[] = {31, (onKarkausvuosi ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // Lisää päivä yhdellä
  paiva++;

  // Tarkista, onko kyseinen kuukausi ohi
  if (paiva > kuukausienPituudet[kuukausi - 1]) 
  {
    paiva = 1;
    kuukausi++;
  }

  // Tarkista, onko vuosi vaihtunut
  if (kuukausi > 12) 
  {
    kuukausi = 1;
    vuosi++;
  }
}