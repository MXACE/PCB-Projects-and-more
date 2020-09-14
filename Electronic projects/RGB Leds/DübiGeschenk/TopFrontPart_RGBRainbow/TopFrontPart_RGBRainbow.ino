#include <SD.h>
#include <FAB_LED.h>
#include "math.h" // Needed for fmod()

using namespace std;
//-------------------------------------------------
// Just unnecessary, but cool leds for the gokart.
// Made for the top-front part of the gokart, to
// let it shine.
//
// Follows the HSV (hue, saturation, value) model
// with an own improvised hue(degree counter)
//
// Autor: Marco Stauber, 28.11.2019
//-------------------------------------------------


//Max Pixel using
//Speed of the pixel refresh with additional delay
/////////////////////////////
const uint8_t numPixels = 40;
/////////////////////////////
#define SPEED 20
/////////////////////////////

ws2812b<D, 6>  LEDstrip;
hbgr  pixels[numPixels] = {};

// S E T U P
void setup()
{  
  //Serial.begin(9600); //Feedback console
  
  for (uint8_t pos = 0; pos < (numPixels*2); pos++) //Clear all LED
  {
    pixels[pos].h = 0xFF; // hgrb has h field
    pixels[pos].g = 0;
    pixels[pos].b = 0;
    pixels[pos].r = 0;
  }
  
  LEDstrip.sendPixels(numPixels*2,pixels);
}


// L O O P
void loop()
{
  uint8_t rgbArr[3] = {0,0,0};
//---------------------------------------------------------------------
  
  while(1)
  {
    rainbow(rgbArr); //Rainbow cycle (one of 360)

    /*
    Serial.print(rgbArr[0]);
    Serial.print(", ");
    Serial.print(rgbArr[1]);
    Serial.print(", ");
    Serial.print(rgbArr[2]);
    Serial.println("");
    */
        
    fillPixel(rgbArr[0],rgbArr[1],rgbArr[2]);
    
    LEDstrip.sendPixels(numPixels, pixels); 
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

void singlePixel(uint8_t Pos, uint8_t R_RGB, uint8_t G_RGB, uint8_t B_RGB)
{
   pixels[Pos].r = R_RGB;
   pixels[Pos].g = G_RGB;
   pixels[Pos].b = B_RGB; 
}

void rainbow(uint8_t *rgbArr)
{
    //Just look at this
    //https://upload.wikimedia.org/wikipedia/commons/thumb/5/5d/HSV-RGB-comparison.svg/451px-HSV-RGB-comparison.svg.png
    
    static int Counter = 0;   //=degrees

    if(Counter <= 60)
    { 
        rgbArr[0] = 240;                    //(R)GB, 240 as max
        rgbArr[1] = rgbArr[1] + 4;          //R(G)B, 60 * 4 = 240
        rgbArr[2] = 0;                      //RG(B), 0 as min
    }
    if((Counter > 60) && (Counter <= 120))
    {
        rgbArr[0] = rgbArr[0] - 4;
        rgbArr[1] = 240;
    }
    if((Counter > 120) && (Counter <= 180))
    {
        rgbArr[0] = 0;
        rgbArr[2] = rgbArr[2] + 4;
    }
    if((Counter > 180) && (Counter <= 240))
    {
        rgbArr[1] = rgbArr[1] - 4;
        rgbArr[2] = 240;
    }
    if((Counter > 240) && (Counter <= 300))
    {
        rgbArr[0] = rgbArr[0] + 4;
        rgbArr[1] = 0;
    }
    if((Counter > 300) && (Counter <= 360))
    {
        rgbArr[0] = 240;
        rgbArr[2] = rgbArr[2] - 4;;
    }
    if(Counter == 360) //Max limit reached
    {
      Counter = 0;     //restart Counter at 0
    } 
    else
    {
      Counter++;       //increase Counter
    }

    /*
    Serial.print(Counter);
    Serial.print(", ");
    */
}

//it finally works!
