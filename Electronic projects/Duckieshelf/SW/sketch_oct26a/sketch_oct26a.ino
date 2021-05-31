#include <SD.h>
#include <SPI.h>
#include <FAB_LED.h>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//Max Pixel using
//Speed of the pixel refresh with additional delay
/////////////////////////////
const uint8_t numPixels = 30;
/////////////////////////////

ws2812b<D, 2>  LEDstrip;
hbgr  pixels[numPixels] = {};

#define READ 0

const int EOC_Right = 5;
const int CS_Right = 6;

const int EOC_Left = 7;
const int CS_Left = 8;

const int EOC_Middle = 9;
const int CS_Middle = 10;

const int ADCsetup = B01101000;
const int getChannel = B11001000;
const int averaging = B00100010;
const int ADCreset = B00010000;

//const char assignedLED[30] = {11,20,21,30,29,22,19,12,9,10,1,2,3,8,13,18,23,28,27,24,17,14,7,4,5,6,15,16,25,26};
const char assignedLED[30] = {11,12,13,24,25,26,23,14,9,10,1,8,15,22,27,28,21,16,7,2,3,6,17,20,29,30,19,18,5,4};
volatile unsigned char ChannelValues[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

volatile unsigned char setLED[2][30] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
// S E T U P
void setup()
{  
  Serial.begin(9600); //Communication to gokart
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("Start");
  
  delay(100);
  for (uint8_t pos = 0; pos < (numPixels*2); pos++) //Setup blue and set other values to 0
  {
    pixels[pos].h = 0xFF; // hgrb has h field
    pixels[pos].g = 0;
    pixels[pos].b = 20;
    pixels[pos].r = 0;
  }
  delay(100);
  LEDstrip.sendPixels(numPixels,pixels); //Refresh 
  delay(100);
  
  //while(1);
  // start the SPI library:
  SPI.begin();
  //SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  
  // initalize the  data ready and chip select pins:
  pinMode(EOC_Right, INPUT);
  pinMode(CS_Right, OUTPUT);
  pinMode(EOC_Left, INPUT);
  pinMode(CS_Left, OUTPUT);
  pinMode(EOC_Middle, INPUT);
  pinMode(CS_Middle, OUTPUT);

  digitalWrite(CS_Left, HIGH);
  digitalWrite(CS_Middle, HIGH);
  digitalWrite(CS_Right, HIGH);
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);

}

// L O O P
void loop()
{
  
//---------------------------------------------------------------------
  ADC_setup();
  /*
  spi_transfer(getChannel,2);
  while(digitalRead(EOC_Middle));
  spi_read(2);*/

  //while(digitalRead(9));
  while(1)
  { 
    spi_transfer(getChannel,1);
    spi_transfer(getChannel,2);
    spi_transfer(getChannel,3);

    if(!digitalRead(EOC_Left))
    {
      spi_read(1);
    }
    if(!digitalRead(EOC_Middle))
    {
      spi_read(2);
    }
    if(!digitalRead(EOC_Right))
    {
      spi_read(3);
    }

    /*------------------------------
    
    spi_transfer(getChannel,1);
    while(digitalRead(EOC_Left));
    spi_read(1);
    
    spi_transfer(getChannel,2);
    while(digitalRead(EOC_Middle));
    spi_read(2);
    
    //Serial.println(ChannelValues[19], DEC);
    
    //delay(100);
    
    spi_transfer(getChannel,3);
    while(digitalRead(EOC_Right));
    spi_read(3);
    ------------------------------------*/
  //Serial.println(ChannelValues[20], DEC);
    ///*
    for(int i = 0; i != 30; i++)
    {
        Serial.println(" ");
        Serial.println(i+1, DEC);
        Serial.println(assignedLED[i], DEC);
        Serial.println(ChannelValues[i], DEC);
        Serial.println(" ");
      if(ChannelValues[i] > 10)
      {
        setLED[1][i] = 1;
      }
      if(ChannelValues[i] > 55)
      {
        setLED[1][i] = 0;
        setLED[0][i] = 1;
        //singlePixel(assignedLED[i], 50,0,0);
        /*Serial.println(" ");
        Serial.println(i+1, DEC);
        Serial.println(assignedLED[i], DEC);
        Serial.println(ChannelValues[i], DEC);
        //Serial.println("YES");
        Serial.println(" ");*/
      }
      if(ChannelValues[i] < 11)
      {
        setLED[0][i] = 0;
        setLED[1][i] = 0;  
      }     
    }
    //*/
    //Serial.println(ChannelValues[17], DEC);
    /*if(ChannelValues[19] > 100)
    {
      fillPixel(50,0,0);
    }
    else
    {
     fillPixel(0,0,0);
    }*/
    for(int i = 0; i != 30; i++)
    {
      if(setLED[1][i])
      {
        singlePixel(assignedLED[i]-1, 0,80,0);
      }
      else if(setLED[0][i])
      {
        singlePixel(assignedLED[i]-1, 50,0,0);
      }
      else
      {
        singlePixel(assignedLED[i]-1, 0,0,0);
      }
    }
    LEDstrip.sendPixels(numPixels,pixels);

    for(int i = 0; i != 30; i++)
    {
      ChannelValues[i] = 0;
    }
    /*  
    if (Serial.available() > 0) //Serial not busy?
    {
      cGetBytes = Serial.readBytes(BUFF, 6); //Read serial and save number of bytes received
      
    }*/
   
    
  }
}

//---------------------------------------------------------------------

void ADC_setup()
{
  char i = 0;
  for(i = 1; i != 4; i++)
  {
    spi_transfer(ADCreset,i);
    spi_transfer(averaging,i);
    spi_transfer(ADCsetup,i);
  }
}

void spi_read(char adc)
{
  unsigned char result = 0;
    for(int i = 0; i != 20; i++)
    {
      result = spi_transfer(READ, adc);
      /*Serial.print(adc*10-10+i/2, DEC);
      Serial.print(":");
      Serial.println(result, DEC);*/
      /*while (!(SPSR & (1<<SPIF)))     // Wait the end of the transmission
      {
    
      };*/
      if(i%2)
      {
        ChannelValues[adc*10-10+i/2] |= result >> 4;           // return the received byte
        /*if(i == 18 || i == 19)
        {
          Serial.println(result << 4, DEC);
        }*/
      }
      else
      {
        ChannelValues[adc*10-10+i/2] |= result << 4;           // return the received byte
      }
      //Serial.println(adc, DEC);
      //Serial.println(ChannelValues[19], DEC);
      /*
      if(i == 18 || i == 19)
      {
        Serial.println(adc, DEC);
        Serial.println(ChannelValues[19], DEC);
      }*/
   }
  
}

unsigned char spi_transfer(volatile char data, char adc)
{
  unsigned char temp = 0;
  switch(adc)
  {
    case 1:
       digitalWrite(CS_Left, LOW);
       temp = SPI.transfer(data);
       digitalWrite(CS_Left, HIGH);
       break;

    case 2:
       digitalWrite(CS_Middle, LOW);
       temp = SPI.transfer(data);
       digitalWrite(CS_Middle, HIGH);
       break;
    
    case 3:
       digitalWrite(CS_Right, LOW);
       temp = SPI.transfer(data);
       digitalWrite(CS_Right, HIGH);
       break;
  }
  return temp;
}
  
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

volatile void singlePixel(uint8_t Pos, uint8_t R_RGB, uint8_t G_RGB, uint8_t B_RGB)
{
   pixels[Pos].r = R_RGB;
   pixels[Pos].g = G_RGB;
   pixels[Pos].b = B_RGB; 
}
