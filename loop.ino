void loop() 
{
  ajan_lasku();             //Pitää ajan laskun käynnissä [aika.ino]
  pien_laitteet();          //Pidetään nappeihin reagointi käynnissä [pien_laitteet.ino]
  vianetsinta();            //mahdollistetaan vikojen tulostamisen [debug.ino]
  gyroscopen_toiminta();    //mahdollistetaan gyroscopen päivittäminen[gyroscope.ino]
  heartrate_toiminta();     //sykeanturin toiminta [heartrate.ino]
}