#include "U8glib.h"
#include <Arduino.h>
#include <DrinkingSensor.h>

DrinkingSensor sensor;
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 

void draw(void)
{ 
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(0, 20); 
  u8g.print("Hello World!");
}

void setup()
{
  Serial.begin(9600);
  while(!Serial);

  sensor.init(2); // init(sensotInterruptPin);
  delay(100);
}

void loop()
{
  Serial.print("velocity: ");
  Serial.print(sensor.getVelocity());
  Serial.print(" velocity max: ");
  Serial.print(sensor.getMaxVelocity());
  Serial.print(" velocity av: ");
  Serial.print(sensor.getAverageVelocity());
  Serial.print(" volume: ");
  Serial.print(sensor.getVolume());
  Serial.print(" cycle: ");
  Serial.println(sensor.getCycle());
  delay(100);

  u8g.firstPage();  
  do
  {
    draw();
  } 
  while( u8g.nextPage() );
}