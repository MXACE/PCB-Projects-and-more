#include <SD.h>
#include <FAB_LED.h>

//-----------------------------------------------
// Just unnecessary, but cool leds for the gokarts.
// Made for KITT
// 
// Autor: Marco Stauber, 13.11.2019
//-----------------------------------------------


//Max Pixel using
//Speed of the Pixel
/////////////////////////////
const uint8_t numPixels = 17;
/////////////////////////////
#define SPEED 20
/////////////////////////////

ws2812b<D,6>  LEDstrip;
hbgr  pixels[numPixels] = {};

void setup()
{  
  Serial.begin(9600); //Feedback console
  
  for (uint8_t pos = 0; pos < numPixels; pos++) //Clear all LED
  {
    pixels[pos].h = 0xFF; // hgrb has h field
    pixels[pos].g = 0;
    pixels[pos].b = 0;
    pixels[pos].r = 0;
  }

  LEDstrip.sendPixels(numPixels,pixels);
  LEDstrip.refresh();
}

void loop()
{

//---------------------------------------------------------------------

  while(1)
  {
    Lauflicht(0);   //Red
    
    LEDstrip.sendPixels(numPixels, pixels); 
    LEDstrip.refresh();                         //don't know what this does, but looks nice
    
    delay(SPEED);
  }
}

//---------------------------------------------------------------------


void fillPixel(uint8_t r, uint8_t g, uint8_t b) //Just to fill the LEDS
{
  uint8_t i = 0;

  for(i=0; i != numPixels; i++)
  {
    pixels[i].r = r;
    pixels[i].g = g;
    pixels[i].b = b;
  }
}

void Lauflicht(uint8_t color) // 0 = red; 1 = orange
{
  static uint8_t PosNow = 1;      //LED Position
  uint8_t SecPos = numPixels;      //Second Position for mirror
  static uint8_t dir = 1;         //0 = Backwards; 1 = Forwards
  uint8_t midExist = 0;           //For odd numbers of LEDs
  
  uint8_t lastPixel = numPixels;
  
  
  if(dir == 1)                      //forward?
  {
    if(PosNow == (lastPixel - 1))   //At last LED?
    {
      PosNow--;                     //Go back
      dir = 0;                      //and change dir
    }
    else
    { 
      PosNow++;                     //else go further
    }
  }
  else if(dir == 0)                 //backwards?
  {
    if(PosNow == 0)                 //At first LED?
    {
      PosNow++;                     //Go back
      dir = 1;                      //and change dir
    }
    else
    {
      PosNow--;                     //keep going
    }
  }
  
  //Serial.println(PosNow);

  fillPixel(10,0,0);                //Fill everything red
    
  singlePixel(PosNow, 200,0,0);     //Middle LED
  singlePixel(PosNow-1, 70,0,0);    //1 Lower LED
  singlePixel(PosNow+1, 70,0,0);    //1 Higher LED
}

void singlePixel(uint8_t Pos, uint8_t R_RGB, uint8_t G_RGB, uint8_t B_RGB)
{
   pixels[Pos].r = R_RGB;
   pixels[Pos].g = G_RGB;
   pixels[Pos].b = B_RGB; 
}
