unsigned int luo_rgb(uint8_t r, uint8_t g, uint8_t b) //luo näytön tukema värikoodi r,g ja b arvoilla 
{
    return (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

String lisaa_nolla(int i) 
{ // lisää nollia jos alle 10 esim jos 5 niin voi tulostaa 05 jne
    if(i < 10) 
    {
        return "0" + String(i);  
    } 
      else 
    {
        return String(i);
    }
}

bool onko_string(String tutkittava) 
{
  float luku = tutkittava.toFloat(); 

  if(String(luku) == tutkittava) 
  {
    return false; // On liukuluku
  } 
    else 
  {
    return true; // On merkkijono
  }
}

String truefalse(bool i) //tämä mahdollistaa tulostaa true tai false konsoliin tai näytölle
{
  if(i==true)
  {
    return "True";
  }
    else
  {
    return "False";
  }
}

bool tarkista_objektin_ehto(String ehto_muuttuja, String arvo)
{
  int i = 0;
  while(i < 20)
  {
    if(muuttuja_nimi[i] == ehto_muuttuja) 
    {
      if(muuttuja_is_int[i] == !onko_string(arvo))
      {
        if(muuttuja_is_int[i] == true)
        {
          if(muuttuja_arvo_float[i] == arvo.toFloat())
          {
            return true;
          } 
            else
          {
            break;
          }
        }
          else
        {
          if(muuttuja_arvo_str[i] == arvo)
          {
            return true;
          }
            else
          {
            break;
          }
        }
      }
        else
      {
        break; // ei ollut samaa tyyppiä
      }
    }
    i++;
  }
  return false;
}

String poimi_muuttujan_nimi(String sisalto, int id)
{
  //etsitään muuttujan nimi
  int aloitus_kohta = sisalto.indexOf("m" + String(id) + " §") + (3 + String(id).length()); 
  int lopetus_kohta = sisalto.indexOf("§", aloitus_kohta); 
  return sisalto.substring(aloitus_kohta, lopetus_kohta); //lisätään palautus taulukkoon
}

String poimi_muuttujan_arvo(String sisalto, int id)
{
  //etsitään muuttujan nimi
  int aloitus_kohta = sisalto.indexOf("m" + String(id) + " §") + (3 + String(id).length()); 
  int lopetus_kohta = sisalto.indexOf("§", aloitus_kohta); 
  //etsitään muuttujan arvo
  aloitus_kohta = sisalto.indexOf("'" , lopetus_kohta); //etsitään seuraava lainausmerkki
  lopetus_kohta = sisalto.indexOf("'" , aloitus_kohta);
  return sisalto.substring(aloitus_kohta, lopetus_kohta); //lisätään palautus taulukkoon
}

String poimi_arvo(String sisalto, String etsittava)
{ 
  int aloitus_kohta = sisalto.indexOf(String(etsittava)+"='") + (2 + etsittava.length());
  //hankitaan aloituskohta haettavan sanan pituudella ja lisätään 2 eli merkit = ja ' 

  if(aloitus_kohta == -1) //aloituskohtaa ei löytynyt
  {
    return ""; //keskeytetään functio
  }

  int lopetus_kohta = sisalto.indexOf("'", aloitus_kohta); 
  //aloitetaan aloituskohdasta joka on jo ohittanut ensimmäisen ' ja päättyy seuraavaan '

  if(lopetus_kohta == -1) //lopetuskohtaa ei löytynyt
  {
    return ""; //keskeytetään functio
  }

  return sisalto.substring(aloitus_kohta, lopetus_kohta); 
  //palautetaan string 
}

String etsi_alue(String sisalto, String alue)
{
  int aloitus_kohta = sisalto.indexOf(String(alue)+"{") + (1 + alue.length());
  //etsitään alueen määrityksen aloitus kohta

  if(aloitus_kohta == -1) //aloituskohtaa ei löytynyt
  {
    return ""; //keskeytetään functio
  }

  int lopetus_kohta = sisalto.indexOf("}", aloitus_kohta);
  //etsitään alueen lopetuskohta

  if(lopetus_kohta == -1) //lopetuskohtaa ei löytynyt
  {
    return ""; //keskeytetään functio
  }
  
  return sisalto.substring(aloitus_kohta, lopetus_kohta);
}