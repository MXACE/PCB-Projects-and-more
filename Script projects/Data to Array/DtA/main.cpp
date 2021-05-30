
#include <iostream>
using namespace std;

#include "conio.h"
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <time.h>

void sleep_ms(int i);
void write(char c);
void writeArray(int* number);

char nl = 0;
char fill2 = 0;

char writetofile = 0;
ofstream myfile;

int main(void)
{
	while (1)
	{
		unsigned char mode = 0;
		char err = 0;

		string size;
		
		char checkcounter = 0;
		int number[2] = { 0,0 };
		char sizeCorrect = 0;
		int SizeCounterA = 0, SizeCounterB = 0;

		char fill = 0;
		
		printf_s("Generate Array[1] or Convert Data[2]: ");
		scanf_s("%i", &mode);
		getchar();
		switch (mode)
		{
			case 1:
			//GET ARRAY SIZE
			printf_s("Size? example: 8x2; : ");
			getline(cin, size);

			//Get number 1 out of string
			while ((size[checkcounter] != 'x') && (size[checkcounter] != 'X'))
			{
				number[0] = number[0] * 10 + size[checkcounter]-48;
				checkcounter++;
			}
			//Check and skip x/X
			if (!(size[checkcounter] == 'x' || size[checkcounter] == 'X'))
			{
				err = 1;
				goto ENDinLOOP;
			}
			checkcounter++;
			//Get number 2 out of string
			while ((size[checkcounter] != '\n') && size[checkcounter] != '\0')
			{
				number[1] = number[1] * 10 + size[checkcounter]-48;
				checkcounter++;
			}

			//Get fill value
			printf_s("How to fill?: ");
			scanf_s(" %c", &fill);
			getchar();
			fill2 = fill;
			//If more than 1 rows
			if (number[0] > 1)
			{
				//Get if newlines are wanted
				printf_s("With newlines? y/n: ");
				scanf_s(" %c", &nl);
				getchar();
			}

			//check if newline yes
			if ((nl == 'y') || (nl == 'Y'))
			{
				//set to 1, makes it easier
				nl = 1;
			}
			else
			{
				//set to 0, makes it easier
				nl = 0;
			}

			//Get if write to file wanted
			printf_s("Write to file? y/n: ");
			scanf_s(" %c", &writetofile);
			getchar();

			//check if writetofile yes
			if ((writetofile == 'y') || (writetofile == 'Y'))
			{
				//set to 1, makes it easier
				writetofile = 1;
				//open file
				myfile.open("ARRAYS.txt");
			}
			else
			{
				//set to 0, makes it easier
				writetofile = 0;
			}

			writeArray(number);
			/*//Spacer
			printf("\n\n");
			if (number[0] > 1)
			{
				//For multi-row arrays
				write('{');
			}
			//rows
			for (SizeCounterA = 0; SizeCounterA != number[0]; SizeCounterA++)
			{
				//not first line
				if (SizeCounterA && nl)
				{
					write(' ');
					write('{');
				}
				//this is the first line
				else
				{
					write('{');
				}
				if (number[1] == 1)
				{
					//only 1 colum
					write(fill);
				}
				else
				{
					//multiple colum
					for (SizeCounterB = 0; SizeCounterB != number[1]; SizeCounterB++)
					{
						write(fill);
						write(',');
					}
				}
				//end of array group
				write('}');
				if ((number[0] - SizeCounterA) >= 2)
				{
					//seperate single array values
					write(',');
				}
				//mewline?
				if (nl)
				{
					if(!(SizeCounterA == number[0]-1)) write('\n');
				}
			}
			//Close Array
			if (number[0] > 1)
			{
				write('}');
			}*/
			printf("\n\nDone!");			
			break;
		
			case 2:


			break;

		default:
			break;
		}
		ENDinLOOP:if(err)
		{
			err = 0;
			printf("nA");
			_getch();
			system("cls");
		}
		myfile.close();
		printf("\nPress a button to restart");
		_getch();
		system("cls");
	}
	_getch();

	return 0;
}

void sleep_ms(int i)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(i));
}

void write(char c)
{
	cout << c;
	if (writetofile)
	{
		myfile << c;
	}
}

void writeArray(int* number)
{
	int SizeCounterA = 0, SizeCounterB = 0;

	printf("\n\n");
	if (number[0] > 1)
	{
		//For multi-row arrays
		write('{');
	}
	//rows
	for (SizeCounterA = 0; SizeCounterA != number[0]; SizeCounterA++)
	{
		//not first line
		if (SizeCounterA && nl)
		{
			write(' ');
			write('{');
		}
		//this is the first line
		else
		{
			write('{');
		}
		if (number[1] == 1)
		{
			//only 1 colum
			write(fill2);
		}
		else
		{
			//multiple colum
			for (SizeCounterB = 0; SizeCounterB != number[1]; SizeCounterB++)
			{
				write(fill2);
				write(',');
			}
		}
		//end of array group
		write('}');
		if ((number[0] - SizeCounterA) >= 2)
		{
			//seperate single array values
			write(',');
		}
		//mewline?
		if (nl)
		{
			if (!(SizeCounterA == number[0] - 1)) write('\n');
		}
	}
	//Close Array
	if (number[0] > 1)
	{
		write('}');
	}
}
