/*

    JykeWatch OS for Arduino Nano 33 ble
    Muuttujat määritetään tämän sivun alhaalla.

    [sivun nimike] lisätieto 

    [TÄMÄ SIVU] kirjastojen, pinnejen ja muuttujien määritykset
    [update_history] päivitys/kehitys historia/tiedot
    [setup] ohjelman luonnollinen setup
    [loop] ohjelman luonnollinen kierto
    [naytto] näytön ohjaus
    [muistikortti] muistikortin luku
    [pien_laitteet] nappejen, hall antureiden , valoanturin ja akun toiminta
    [debug] vianetsintä jatkuvasti muuttujille muuttujille jne
    [aika] kellon toiminta
    [kolmannen_osapuolen_ohjelmat] suorittaa ohjelmiston
    [gyroscope] gyroscope arvojen päivitys ja toiminta
*/

//tarvittavat kirjastot
#include "SPI.h"              //Väyläkirjasto näytölle ja sd kortille
#include "Adafruit_GFX.h"     //Yleinen näytön piirtokirjasto
#include "Adafruit_GC9A01A.h" //Mallikohtainen näytön piirtokirjasto
#include <SD.h>               //sd kortin kirjasto
#include <ArduinoBLE.h>       //bt,rgb ja muut arduino 33 ble toiminnot 
#include <Arduino_LSM9DS1.h>  //gyroscope kirjasto
#include <Wire.h>             
#include "MAX30100_PulseOximeter.h" //pulssianturin kirjasto

//  Näytön määritykset
//              RST  8             
      #define TFT_CS 10
      #define TFT_DC 7
//              SDA  11
//              SCL  13

//SD kortin pinnimääritykset
//            MOSI 11
//            MISO 12
//            CLK  13
      #define SD_CS 4 

//pikkuosia
#define VALINTA_PAINIKE A0  //ylempi sivu painike
#define PALUU_PAINIKE A1    //alempi sivu painike
#define VALO_ANTURI   A2    //valoanturi
#define AKUN_MITTAUS  A3    //akun jännitemittaus 
#define VASEN_HALL A6       //oikea hall anturi   
#define OIKEA_HALL A7       //vasen hall anturi    

// Alustetaan muuttujat, kaikki jossa on (+/-) voi muuttaa, muita ohjaa jonkin sortin logiikka 

//vianetsintä
bool force_all_debug = false;   //pakota näyttämään kaikki kehitysviestit konsoliin (+/-)
bool enable_debug_rgb = true;   //käytetäänkö arduinon päällä olevaa rgb lediä virheilmoituksiin (+/-)
bool config_load_debug = false; //tulostetaanko kehitysviesteja aloitusmääritystiedostoon liittyen

int debug_msg_delay = 1000;       //kuinka usein tulostaa (vaikuttaa alla oleviin asetuksiin) (ms)(+/-) 
bool time_debug = false;          //tulostaa aikaan liittyviä kehitysviestejä konsoliin (+/-)
bool pienlaitteet_debug = false;  //napit, hall, valoanturi jne [pien_laitteet.ino]
bool akku_debug = false;          //tulostaa akkuun liittyviä kehitysviestejä konsoliin (+/-)

//Järjestelmä
float os_versio = 1.0;      //järjestelmän versio (TÄRKEÄ! mitä .jp kieltä tukee) (+/-)
long last_debug_msg = 0;    //ms koska viimeisin kehitysviesti on tulostettu 
long last_time = 0;         //ms koska viimeisin sekuntti on lisätty  
bool os_debug = true;      //tulostetaanko järjestelmän toimintaan liittyviä kehitysviestejä
int inapp = -1;

//Oletusasetuksia
String kellon_nimi = "JykeWatch" + String(os_versio); //kellon oletus nimi jos kortilla ei ole tallennusta (+/-)
bool sleep_mode = false;                  //tällä voidaan säästää virtaa koska kaikkia scriptejä ei tarvita jos kelloa ei "käytetä"
int home_app = -1;                        //kellon oletus kotisovellus jos kortilla ei ole tallennusta (+/-)
int menu_app = -1;                        //kellon oletus päävalikkosovellus jos kortilla ei ole tallennusta (+/-)
int error_app = -1;                       //kellon oletus virheviesti sovellus jos kortilla ei ole tallennusta (+/-)
int app_error_code = -1;                  //minkä virheviestin virhesovellus näyttää
String maaritys_tiedosto = "patonki.jpm"; //kellon määritys tiedosto (+/-)
String app_file_type = ".jp";             //millä tiedostopäätteellä sovelluksia etsitään

//Päiväys ja aika muuttujat
int vuosi = 2023;     //vuosi jos kortilla ei ole tallennusta(+/-)
int kuukausi = 12;    //kuukausi jos kortilla ei ole tallennusta(+/-)
int paiva = 31;       //päivä jos kortilla ei ole tallennusta(+/-)
int sekunnit = 0;     //sekunnit jos kortilla ei ole tallennusta(+/-)
int minuutit = 59;    //minuutit jos kortilla ei ole tallennusta(+/-)
int tunnit = 23;      //tunnit jos kortilla ei ole tallennusta(+/-)

//valinta painike
float select_btn_jannite = 0; //reaaliaikainen jännitemittaus
bool select_nappi = false;    //onko nappi päällä

//paluu painike
float back_btn_jannite = 0; //reaaliaikainen jännitemittaus
bool back_nappi = false;    //onko nappi päällä

//oikea hall anturi
float right_hall_jannite = 0; //reaaliaikainen jännitemittaus
bool right_hall = false;      //onko nappi päällä

//vasen hall anturi
float left_hall_jannite = 0; //reaaliaikainen jännitemittaus
bool left_hall = false;      //onko nappi päällä

//kirkkaus anturi
float kirk_jannite = 0;    //reaaliaikainen jännitemittaus
int valon_maara = 0;       //valon määrä prosentteina

//gyroscope
bool gyroscope_debug = false;             //tulostetaanko gyroscopen kehitysviestit (+/-)
int gyroscopen_luku_viive = 1000;         //kuinka usein gyroscope arvot päivitetään (+/-)
long last_gyroscope_time = 0;             //ms koska viimeisin kehitysviesti ilmoitettu 
float xAcc = 0, yAcc = 0, zAcc = 0;       //asento arvot
float xGyro = 0, yGyro = 0, zGyro = 0;    //kiihtyvyys arvot
float xMag = 0, yMag = 0, zMag = 0;       //magneettikentän arvot
bool Acc = true, Gyro = true, Mag = true; //estää turhat päivitykset
bool skip_gyroscope = false;              //ohitetaanko anturi (AUTOM jos määritys failee) (+/-)

//bluethoot
bool bt_debug = false;    //tulostaako bt kehitysviestejä (+/-)
bool skip_bt = false;    //ohitetaanko anturi (AUTOM jos määritys failee) (+/-)

//sykeanturi
bool heartrate_debug = false; //tulostetaanko sykkeeseen liittyviä kehitysviestejä (+/-)
bool pulse = false;          //pulssi signaali
int rate_delay = 1000;       //mittaus viive (+/-)
bool skip_heartrate = false; //ohitetaanko anturi (AUTOM jos määritys failee)
long last_pulse = 0;         //koska viimeisin syke raportoitu
float bpm = 0;               //syke
int sptwo = 0;               //veren happipitoisuus
PulseOximeter pox;           //sykekirjaston muuttuja

//akun muuttujat
float akun_jannite = 0;             //reaaliaikainen jännitemittaus
int akun_taso = 0;                  //akun taso 0-100 pääteltynä minimistä ja maksimista
float pienin_toiminta_jannite = 2;  //pienin mahdollinen virta jolla järjestelmä toimii (+/-)
float akun_maksimi_jannite = 4.6;   //paljonko kello voi maksimissaan saada omalta akulta (+/-)
bool ladataan = false;              //jos akun jännite on isompi kuin maksimi oletetaan että ladataan

//muistikortin muuttujat
bool sd_debug = true;        //tulostaa muistikortin lukiaan liittyviä kehitysviestejä konsoliin (+/-)
bool sd_debug_read = false;   //tulosta kaikki konsoliin mitä kortinlukia lukee

int nykyinen_sivu = 0;

//ohjelman sivu muisti  //eli max sivut ovat 10kpl 
String sivun_paluu[10] = {"","","","","","","","","",""};   //paluu näppäimen komento milläkin sivulla
String sivun_valinta[10] = {"","","","","","","","","",""}; //valinta näppäimen komento milläkin sivulla
String sivun_rul_vas[10] = {"","","","","","","","","",""}; //rullaus vasempaan komento milläkin sivulla
String sivun_rul_oik[10] = {"","","","","","","","","",""}; //rullaus oikeaan komento milläkin sivulla
unsigned int sivun_vari[10] = {0,0,0,0,0,0,0,0,0,0};        //sivujen värin

//ohjelman objektit //max objektit ovat 100kpl
int obj_x[100] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int obj_y[100] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int obj_h[100] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int obj_w[100] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int obj_s[100] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
String obj_v[100] = {"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""};
String obj_type[100] = {"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""};
unsigned int obj_vari[100] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int obj_page[100] =  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//ohjelman muuttujat HUOM jos kokoa muutetaan pitää se muuttaa funktiot sivulla ehtojen tarkastus funtiossa
String muuttuja_nimi[20] = {"","","","","","","","","","","","","","","","","","","",""};
bool muuttuja_is_int[20] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
String muuttuja_arvo_str[20] = {"","","","","","","","","","","","","","","","","","","",""};
float muuttuja_arvo_float[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

Adafruit_GC9A01A tft(TFT_CS, TFT_DC); //ilmoitetaan pinnit näytön kirjastolle