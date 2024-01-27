void piirra_laatikko(int x, int y, int w, int h, uint16_t color) //piirtää laatikon x , y , pituus , korkeus , näytön tukema värikoodi
{
  int i=0;
  while(i<h)
  {
    tft.drawLine(x, y+i, x+w, y+i, color);  //piirretään viiva x ja x+pituus välille ja toistetaan se korkeuden verran
    i++;
  }
}

void piirra_teksti(String txt,int x, int y, int scale,  uint16_t color)
{
  tft.setTextColor(color);  //asetetaan tekstin väri
  tft.setTextSize(scale);   //asetetaan tekstin kooksi 
  tft.setCursor(x, y);      //valitaan mihin piirretään
  tft.println(txt);         //kirjoitetaan tekstiä
}

void aloitus_naytto()
{  
  tft.begin();                            //aloitetaan näyttö kirjasto
  tft.fillScreen(luo_rgb(255,255,255));   //maalataan koko näyttö valkoisella
  uint16_t musta = luo_rgb(0,0,0);        //luodaan musta väri koska sitä tarvitaan useassa kohtaa
  piirra_teksti("Jyke",55, 85,5,musta);
  piirra_teksti("WatchOs",40, 130,4,musta);
}