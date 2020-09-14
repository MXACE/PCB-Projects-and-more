/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED 7-Segment backpacks 
  ----> http://www.adafruit.com/products/881
  ----> http://www.adafruit.com/products/880
  ----> http://www.adafruit.com/products/879
  ----> http://www.adafruit.com/products/878

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

unsigned int timer = 0;
unsigned int timerOld = 0;
char bAct = 0;
boolean showTime = false;

void setup() {
  #ifndef __AVR_ATtiny85__
  Serial.begin(115200);
  #endif
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
    
  pinMode(13, OUTPUT);
  
  pinMode(2, INPUT_PULLUP );
  pinMode(3, INPUT_PULLUP );
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  //digitalWrite(6, HIGH);
  //digitalWrite(7, HIGH);
  
  matrix.begin(0x70);
  //matrix.setBrightness(15);
 
  noInterrupts();           // disable all interrupts

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 20000;            // compare match register 8MHz/8/100Hz

  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 >> CS10); //prescaler = 8
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  //attachInterrupt(digitalPinToInterrupt(2), blue, RISING  );
  //attachInterrupt(digitalPinToInterrupt(3), yellow, FALLING  );
  
  interrupts();
  bAct = 0;

  delay(100);
  matrix.writeDigitNum(3, 0);
  matrix.writeDigitNum(4, 0);
  matrix.writeDigitRaw(0x02, 0x02);
  matrix.writeDisplay();
  
  Serial.println("Begin");
  
}



void loop()
{
  //static boolean bOldS = 0;
  static boolean OF = false;
  
  if(bAct)
  {
    if(timer != timerOld)
    {
      timerOld = timer;
      
      /*if((timer % 50) == 0)
      {
          bOldS ^= 1;
      }
      else
      {
         if(!bOldS)
         {
            matrix.writeDigitRaw(0x02, 0x02);
         }
      }
      */
      if(timer > 9999)
      {
         matrix.clear();
         matrix.writeDigitNum(3, 0);
         matrix.writeDigitRaw(4, B1110001);
      }
      else
      {
        matrix.print(timer);
        matrix.writeDigitRaw(0x02, 0x02);
      }
      matrix.writeDisplay();

      if(showTime)
      {
        Serial.println(timer);
      }
    }
  }
  checkButton();
}

void checkButton(void)
{
  static boolean Count = true;
  static boolean Start = true;
  static unsigned char ucCounter = 0;
  
  if(!digitalRead(2))
  {
    if(Count)
    {
      if(ucCounter == 5)
        {
          ucCounter = 0;
          Count = false;
          if(bAct)
          {
            SerialInput('E');
          }
          else
          {
            SerialInput('S');
          }
        }
        else
        {
          ucCounter++;  
        }
    }
  }
  else
  {
    ucCounter = 0;
    Count = true;
  }
  if(digitalRead(3))
  {
    //Serial.println("Sensor on");
    checkSensor();
  }
}
void checkSensor(void)
{
  static boolean Count = true;
  static boolean Start = true;
  static unsigned char ucCounter = 0;
  float sensorValue = analogRead(A0);
  int voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(sensorValue);
  Serial.println(voltage);
  //Serial.println(voltage);
  //if(voltage != 1 && voltage > 0)
  if(sensorValue > 400)
  {
    if(Count)
    {
      if(ucCounter == 5)
        {
          ucCounter = 0;
          Count = false;
          if(Start)
          {
            SerialInput('S');
            Start = false;
          }
          else
          {
            SerialInput('E');
            Start = true;
          }
        }
        else
        {
          ucCounter++;  
        }
    }
  }
  else
  {
    ucCounter = 0;
    Count = true;
  }
}

void serialEvent()
{
  int incomingByte = 0;
  
  incomingByte = Serial.read(); //Read serial and save number of bytes received
  SerialInput(incomingByte);
}

void SerialInput(unsigned char C)
{
  switch(C)
  {
    case 'S':
            Serial.println("START");
            bAct = 1;
            timer = 0;
            break;
    case 'E':
            Serial.println("END");
            Serial.println(" ");
            Serial.println("Time:");
            Serial.print((timer - timer%100)/100);
            Serial.print(".");
            Serial.print(timer%100);
            Serial.println("s");
            bAct = 0;
            delay(2000);
            break;
    case 'R':
            Serial.println("RESET");
            bAct = 0;
            timer = 0;
            matrix.clear();
            matrix.writeDigitNum(4, 0);
            matrix.writeDigitNum(3, 0);
            matrix.writeDigitRaw(0x02, 0x02);
            matrix.writeDisplay();
            break;  
    case 'H':
            Serial.println(" ");
            Serial.println("------------");
            Serial.println("    HELP");
            Serial.println("------------");
            Serial.println("'S' - START");
            Serial.println("'E' - END");
            Serial.println("'R' - RESET");
            Serial.println("'T' - TIME");
            Serial.println("'H' - HELP");
            Serial.println("------------");
            Serial.println(" ");
            break;
    case 'T':
            if(showTime)
            {
              Serial.println("SHOW TIME OFF");
              showTime = false;
            }
            else
            {
              Serial.println("SHOW TIME ON");
              showTime = true;  
            }

            break;       
  }
}
ISR(TIMER1_COMPA_vect)
{
  //digitalWrite(13, digitalRead(13) ^ 1); // LED ein und aus
  
  timer++;
}
