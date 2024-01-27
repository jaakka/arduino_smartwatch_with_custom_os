void bt_maaritys()
{
  if(!skip_bt)
  {
    if (!BLE.begin()) 
    {
      skip_bt = true;
      if(bt_debug)
      {
        Serial.println("BT-moduulin määritys epäonnistui!");
      }
    }
  }
}