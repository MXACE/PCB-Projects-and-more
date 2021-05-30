#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern uint32_t ADCvalues[5];
extern char BATTERY_STATE;
extern char NMOS_SWITCH;

extern UART_HandleTypeDef huart2;


void COM_TX(char string[]);

/* @param color:
 *
 *        1: RED
 * 		  2: ORANGE
 * 		  3: GREEN
 * 		  DEF: NOP
 *
 * @param state:
 *
 * 		  1: ON
 *        0: OFF
 */
void LEDS(char color, char state)
{
	switch(color)
	{
	case 1:
		state ? HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin, GPIO_PIN_SET) :
				HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin, GPIO_PIN_RESET);
		break;

	case 2:
		state ? HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port,LED_ORANGE_Pin, GPIO_PIN_SET) :
						HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port,LED_ORANGE_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		state ? HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin, GPIO_PIN_SET) :
						HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin, GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}

/* @param batState:
 *
 *        1: EMPTY
 * 		  2: LOW
 * 		  3: GOOD
 * 		  DEF: All LEDS OFF
 */
void LED_Feedback(char batState)
{
	switch(batState)
	{
	case 1:
			LEDS(1,1);
			LEDS(2,0);
			LEDS(3,0);
			break;

	case 2:
			LEDS(1,0);
			LEDS(2,1);
			LEDS(3,0);
			break;
	case 3:
			LEDS(1,0);
			LEDS(2,0);
			LEDS(3,1);
			break;
		default:
			LEDS(1,0);
			LEDS(2,0);
			LEDS(3,0);
			break;
	}
}

/*
 *  @param state: Gate on/off
 *
 *  priority 1: NMOS Switch
 *  		 2: parameter state
 */

void setGate(char state)
{
	static char oldstate = 0;

	if(state > 1) state = 1;

	if(NMOS_SWITCH)
	{
		HAL_GPIO_WritePin(NMOS_OFF_GPIO_Port, NMOS_OFF_Pin, GPIO_PIN_RESET);
	}
	else if(state && !oldstate)
	{
		HAL_GPIO_WritePin(NMOS_OFF_GPIO_Port, NMOS_OFF_Pin, GPIO_PIN_SET);
	}
	else if(!state && oldstate)
	{
		HAL_GPIO_WritePin(NMOS_OFF_GPIO_Port, NMOS_OFF_Pin, GPIO_PIN_RESET);
	}

	oldstate = state | NMOS_SWITCH;
}

void STOP()
{
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}

char Balancer()
{
	/*
	 *  4.2V -> 2.8V = 3500
	 *  3.6V -> 900mV = 1117
	 *  3.4V -> 300mV = 372
	 *
	 * 	< 300mV = EMPTY
	 *  < 900mV = LOW
	 *  < 2.7V = GOOD
	 *
	 *  @return 0bzyx, cell ok = 1, empty = 0
	 */

	char cellCounter = 0;

	if((ADCvalues[1] > 372) || (ADCvalues[1] < 3500))
	{
		cellCounter = 0x01;
	}
	else 
	{
		COM_TX("Cell 1 below min.");
		setGate(0);
	}

	if((ADCvalues[2] > 372) || (ADCvalues[2] < 3500))
	{
		cellCounter = cellCounter || 0x02;
	}
	else 
	{
		COM_TX("Cell 2 below min.");
		setGate(0);
	}

	if(ADCvalues[3] < 372)
	{
		COM_TX("Cell 3 below min.");
		setGate(0);
		BATTERY_STATE = 1;	//EMPTY
	}
	else if(ADCvalues[3] < 1117) // < 900mV
	{
		cellCounter = cellCounter || 0x04;
		BATTERY_STATE = 2;	//LOW
	}
	else if(ADCvalues[3] < 3500) // < 2.8Vmv
	{
		cellCounter = cellCounter || 0x04;
		BATTERY_STATE = 3;  //GOOD
	}

	if(cellCounter == 3)
	{
		return 0;
	}
	else
	{
		setGate(1);
		return cellCounter;
	}
}

void COM_TX(char string[])
{
	HAL_UART_Transmit(&huart2, (uint8_t *)string, strlen(string), 2000);
	HAL_UART_Transmit(&huart2, "\n\r", 2, 2000);
}

void current()
{
	int curr = ADCvalues[0];

	if(curr < 1840) //less then -1A.
	{
		setGate(0);
	}
	else
	{
		setGate(1);
	}

	char str[50];
	int i = 0;
	for(i = 0; i<= 50; i++)
	{
		str[i] = 0;
	}

	long int voltage = ADCvalues[0]*806;
	long int fcurrent = abs(voltage-1500000)*50;

	int first_1 = (fcurrent - fcurrent % 1000000);
	int first_2 = first_1 / 1000000;
	int sec = (fcurrent - first_1) / 10000;

	char a[3] = {0,0,0};
	char b[3] = {0,0,0};

	sprintf(a, "%i", first_2);
	sprintf(b, "%i", sec);

	if(sec < 10)
	{
		sprintf(str, "C%s.0%s", a,b);
	}
	else if(sec == 0)
	{
		sprintf(str, "C%s.00", a);
	}
	else
	{
		sprintf(str, "C%s.%s", a,b);
	}
	COM_TX(str);
}

void temperature()
{

	char str[50];
	int i = 0;
	for(i = 0; i<= 50; i++)
	{
		str[i] = 0;
	}

	long int voltage = ADCvalues[4]*806;

	long int temp = 0;// ENTER VALUE

	int first_1 = (temp - temp % 1000000);
	int first_2 = first_1 / 1000000;
	int sec = (temp - first_1) / 10000;

	char a[3] = {0,0,0};
	char b[3] = {0,0,0};

	sprintf(a, "%i", first_2);
	sprintf(b, "%i", sec);

	if(sec < 10)
	{
		sprintf(str, "T%s.0%s", a,b);
	}
	else if(sec == 0)
	{
		sprintf(str, "T%s.00", a);
	}
	else
	{
		sprintf(str, "T%s.%s", a,b);
	}
	COM_TX(str);
}

void debug_adc(char channel)
{
	char str[10];

	if(channel > 4) channel = 4;

	sprintf(str, "%i", ADCvalues[channel]);
	COM_TX(str);
}

