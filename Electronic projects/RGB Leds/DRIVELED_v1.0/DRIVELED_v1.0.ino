#include <SD.h>
#include <FAB_LED.h>
#include <FastCRC.h>
//---------------------------------------------------------------------------
// LED Indicator for the GoKart for driving
// Communication with UART 9600 8n1
//
// The LEDs are at the begin blue until it receives the first correct 6 bytes
//
// Send 6 Bytes:
// 1-2
//  Wheel led bar
//   First for position green
//   Second for position red
// 3-5
//  RGB single LED
//   Fourth Red value
//   Fifth Green value
//   Sixth Blue value
// 6
//  CRC MAXIM
//  (poly=0x31 init=0x00 refin=true refout=true xorout=0x00 check=0xa1)
//
// ->Position starts with 0!
//  
// Serial timeout at 1 second
// If check fails it sends back a 'E'
//
// Marco Stauber, 20.1.2020
//---------------------------------------------------------------------------

//Max Pixel using
//Speed of the pixel refresh with additional delay
/////////////////////////////
const uint8_t numPixels = 29;
/////////////////////////////

ws2812b<D, 6>  LEDstrip;
hbgr  pixels[numPixels] = {};
FastCRC8 CRC8;

// S E T U P
void setup()
{  
  Serial.begin(9600); //Communication to gokart
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  
  for (uint8_t pos = 0; pos < (numPixels*2); pos++) //Setup blue and set other values to 0
  {
    pixels[pos].h = 0xFF; // hgrb has h field
    pixels[pos].g = 0;
    pixels[pos].b = 20;
    pixels[pos].r = 0;
  }
  LEDstrip.sendPixels(numPixels,pixels); //Refresh Pixels

}

// L O O P
void loop()
{
  uint8_t BUFF[6] = {0,0,0,0,0,0}; //GREEN, RED, RED, GREEN, BLUE, CRC
  char cGetBytes = 0; //Received bytes from serial
//---------------------------------------------------------------------
  
  while(1)
  {    
    if (Serial.available() > 0) //Serial not busy?
    {
      cGetBytes = Serial.readBytes(BUFF, 6); //Read serial and save number of bytes received
      
      if((cGetBytes == 6) && (CRC8.maxim(BUFF, 5) == BUFF[5]) && ((BUFF[0] < (numPixels -1)) && (BUFF[1] < (numPixels -1)))) //6 Bytes received, Calculated CRC correct with the received one, Red Pos and Green Pos Below max pixels -2
      {
        
        fillPixel(0,0,0); //Clear all leds
        
        singlePixel(BUFF[0], 0,50,0);  //GREEN DOT, Byte 1
        singlePixel(BUFF[1], 50,0,0);  //RED DOT, Byte 2
        
        if(BUFF[0] == BUFF[1])  //If both at the same position?
        {
          singlePixel(BUFF[1], 0,0,50);  //BLUE DOT
        }

        singlePixel(numPixels - 1, BUFF[2],BUFF[3],BUFF[4]); //Create RGB led from rgb value (bytes 3-5)
        
        LEDstrip.sendPixels(numPixels, pixels);  //Refresh Pixels
      }
      else
      {
        Serial.write("E");  //E for ERROR
      }        
      delay(100);
    }
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
