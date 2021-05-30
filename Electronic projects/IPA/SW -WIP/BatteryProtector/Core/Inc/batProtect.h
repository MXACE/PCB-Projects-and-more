#ifndef _BATPROTECT_H_
#define _BATPROTECT_H_

#endif

void LEDS(char color, char state);
void LED_Feedback(char batState);

void setGate(char state);
void STOP();
char Balancer();
void COM_TX(char string[]);
void current();
void temperature();

void debug_adc(char channel);
