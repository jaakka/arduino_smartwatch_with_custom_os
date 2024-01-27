void aloita_sovellus(int sovellus_tunnus)
{
  nykyinen_sivu = 1; //asetetaan sovellukset aukeamaan ekalta sivulta 
  String ohjelman_tiedosto = String(sovellus_tunnus) + app_file_type; //lisätään tiedosto pääte
/*
  if(sovellus_tunnus == -1 || !onko_olemassa(ohjelman_tiedosto)) //katotaan että sovellus on määritetty ja tiedosto löytyy
  {
    if(sovellus_tunnus == -1)
    {
      if(os_debug)
      {
        Serial.println("Sovellusta ei ollut määritetty!");
      }
    }
      else
    {
      if(os_debug)
      {
        Serial.println("Sovelluksen tiedostoa "+String(sovellus_tunnus)+" ei löytynyt.");
      }
    }
    //sovellusta ei ollut määritetty
    if(!error_app == -1)
    {
      if(sovellus_tunnus == -1)
      {
        app_error_code = 1001; //asetetaan virhekoodi , sovellusta ei määritetty
      }
        else
      {
        app_error_code = 1002; //asetetaan virhekoodi , sovelluksen tiedostoa ei löytynyt
      }
      aloita_sovellus(error_app);
    }
      else  //jossei oo virheilmoitus sovellusta avaa päänäytön
    {
      aloitus_naytto(); //piirretään aloitus näyttö
      unsigned int punanen = luo_rgb(255,0,0);
      if(sovellus_tunnus == -1)
      {
        piirra_teksti("Sovellusta", 50, 100, 3, punanen);
        piirra_teksti("ei asetettu!", 40, 130, 3, punanen);
      }
        else
      {
        piirra_teksti("Sovellusta", 50, 100, 3, punanen);
        piirra_teksti("ei löydy!", 40, 130, 3, punanen);
      }
    }

    
  }*/

  String ohjelma = lue_tiedosto(ohjelman_tiedosto);
  
  bool errors = false;

   //poimitaan versio
  float ohjelman_os_versio = poimi_arvo(ohjelma,"os_ver").toFloat();

  if(!os_versio == ohjelman_os_versio)
  {
    if(ohjelman_os_versio<os_versio)
    {
        if(os_debug)
        {
          Serial.println("Ohjelmisto on vanhentunut! " + String(ohjelman_os_versio) + " / OS " + String(os_versio));
        }
    }
      else
    {
      if(ohjelman_os_versio>os_versio)
      {
        if(os_debug)
        {
          Serial.println("Ohjelmisto on uudenmalle järjestelmälle! " + String(ohjelman_os_versio) + " / OS " + String(os_versio));
        }
      }
        else
      {
        if(os_debug)
        {
          Serial.println("Ohjelmiston version mainintaa ei löytynyt!");
        }
      }
    }
  }
    else
  {
    if(os_debug)
    {
      Serial.println("Ohjelmisto ja järjestelmä ovat yhteensopivat " + String(ohjelman_os_versio));

      //Ruvetaan lataan muuta ohjelmaa
      int sivut = poimi_arvo(ohjelma,"pages").toFloat();
      int muuttujat = poimi_arvo(ohjelma,"vars").toFloat();
      int objektit = poimi_arvo(ohjelma,"objs").toFloat();

      int i = 0;
      while(i < sivut)
      {
        
        String sivu = etsi_alue(ohjelma,"p" + String(i+1));
        int punainen = poimi_arvo(sivu, "r").toFloat();
        int vihrea = poimi_arvo(sivu, "g").toFloat();
        int sininen = poimi_arvo(sivu, "b").toFloat();
        String rullaus_oikealle = poimi_arvo(sivu, "sr_rt");
        String rullaus_vasemmalle = poimi_arvo(sivu, "sr_lt");
        String valinta_painike = poimi_arvo(sivu, "bt_up");
        String paluu_painike = poimi_arvo(sivu, "bt_dn");
        unsigned int sivu_vari = luo_rgb(punainen,vihrea,sininen);

        sivun_paluu[i] = paluu_painike;
        sivun_valinta[i] = valinta_painike;
        sivun_rul_vas[i] = rullaus_vasemmalle;
        sivun_rul_oik[i] = rullaus_oikealle;
        sivun_vari[i] = sivu_vari;

        if(i == 0) // eka sivu piirretään
        {
          tft.fillScreen(sivu_vari);
          inapp = sovellus_tunnus; //ilmoitetaan nykyinen sovellus
        }

        if(os_debug)
        {
          Serial.println("Ladataan sovelluksen sivuja " + String(i+1) + " / " + String(sivut));
        }
        i++;
      }

      i = 0;
      while(i < muuttujat)
      {
        String arvo = poimi_muuttujan_arvo(ohjelma,i + 1);
        if(onko_string(arvo))
        {
          //arvo oli tekstiä
          muuttuja_is_int[i] = false;
          muuttuja_arvo_str[i] = arvo;
        }
          else
        {
          //arvo oli numero
          muuttuja_is_int[i] = true;
          muuttuja_arvo_float[i] = arvo.toFloat();
        }

        muuttuja_nimi[i - 1] = poimi_muuttujan_nimi(ohjelma,i+1); //tallennetaan muuttujan nimi*/
        if(os_debug)
        {
          Serial.println("Ladataan sovelluksen muuttujia " + String(i+1) + " / " + String(muuttujat));
        }
        i++;
      }

      i = 0;
      while(i < objektit)
      {
        
        String sivu = etsi_alue(ohjelma,"o" + String(i + 1));

        String type = poimi_arvo(sivu, "type");

        if(type == "box" || type == "text")
        {
          String text = "";
          int scale = 1;
          int h = 0;
          int w = 0;
          if(type == "text")
          {  //teksti
            text = poimi_arvo(sivu, "v");
            scale = poimi_arvo(sivu, "s").toFloat();
            obj_s[i] = scale;
            obj_v[i] = text;
          }
          
          if(type == "box")
          {   //laatikko
            h = poimi_arvo(sivu, "h").toFloat();
            w = poimi_arvo(sivu, "w").toFloat();
            obj_h[i] = h;
            obj_w[i] = w;
          }

          //jompikumpi / yhteiset arvot
          int x = poimi_arvo(sivu, "x").toFloat();
          int y = poimi_arvo(sivu, "y").toFloat();
          int p = poimi_arvo(sivu, "p").toFloat();
          int punainen = poimi_arvo(sivu, "r").toFloat();
          int vihrea = poimi_arvo(sivu, "g").toFloat();
          int sininen = poimi_arvo(sivu, "b").toFloat();
          String ehto = poimi_arvo(sivu, "if");
          String ehto_muuttuja = poimi_arvo(sivu, "var");
          

          unsigned int vari = luo_rgb(punainen,vihrea,sininen);
          obj_x[i] = x;
          obj_y[i] = y;
          obj_page[i] = p;
          obj_type[i] = type;
          obj_vari[i] = vari;
          //piirretään ekasivu avatusta sovelluksesta
          
          if(p == 1 || p == 0) // && tarkista_objektin_ehto(ehto_muuttuja,ehto))
          {
            unsigned int objektin_vari = luo_rgb(punainen,vihrea,sininen);
            if(type == "box")
            {
              piirra_laatikko(x, y, w, h, objektin_vari); //piirtää laatikon x , y , pituus , korkeus , näytön tukema värikoodi
            }

            if(type == "text")
            {
              piirra_teksti(text, x - 5, y + 12, 2,  objektin_vari);
            }
          }

        }
          else
        {
          if(os_debug)
          {
            Serial.println("Tuntematon objekti! id:o"+String(i+1));
          }
        }
        
        if(os_debug)
        {
          Serial.println("Ladataan sovelluksen objekteja " + String(i+1) + " / " + String(objektit));
        }
    
        i++;
      }
    }
  }
}