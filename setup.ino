void setup() 
{
  if(force_all_debug)           //jos pakotus päällä asetetaan kaikki trueksi
  {
    time_debug=true;            //pakotetaan kellon ja päiväyksen kehitysviestit
    akku_debug=true;            //pakotetaan akun kehitysviestit
    sd_debug=true;              //pakotetaan muistikortin kehitysviestit
    pienlaitteet_debug=true;    //pakotetaan irto-osien kehitysviestit
    config_load_debug=true;     //pakotetaan os käynistyksen kehitysviestit
    gyroscope_debug=true;       //pakotetaan gyroscopen kehitysviestit
    bt_debug=true;              //pakotetaan bt kehitysviestit
    heartrate_debug=true;       //pakotetaan sykeanturi
  } 

  heartrate_maaritys();         //herätetään sykeanturi
  bt_maaritys();                //herätetään bt-moduuli
  aloita_gyroscope();           //päivitetään gyroscope arvot
  aloitus_naytto();             //Piirretään aloitus grafiikka kelloon [naytto.ino]
  aloita_muistikortin_lukija(); //hehkutetaan lukijaa [muistikortti.ino]
  os_init();                    //ladataan järjestelmän konfigit [os_init.ino]
}