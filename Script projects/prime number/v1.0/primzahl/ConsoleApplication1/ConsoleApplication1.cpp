// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include <iostream>
#include <fstream>

using namespace std;

#define CalculateUpTo 1000000

int main()
{
	unsigned long long int AMOUNT = 0;
	printf("Enter a number to calculate up to:");
	scanf_s("%i",&AMOUNT);
	unsigned long long int divider = 2;
	unsigned long long int nextNumber = 2;
	/*
	unsigned int primzahlen[100000];
	unsigned int primzahlCounter = 0;
	*/
	unsigned int icounter = 0;

	unsigned int buffer = 0;

	bool notDone = true;
	bool currentPrimzahl = true;
	bool Primfound = false;

	/*for (icounter = 0; icounter != 1000; icounter++)
	{
		primzahlen[icounter] = '\0';
	}*/

	ofstream MyFile("primzahlen.txt");

	while (notDone)
	{
		while (currentPrimzahl)
		{
			buffer = nextNumber % divider;
			if ((buffer == 0) && (nextNumber == divider))
			{	
				Primfound = true;
				currentPrimzahl = false;
			}
			else if ((buffer == 0) && (nextNumber != divider))
			{
				currentPrimzahl = false;
			}
			else
			{
				divider++;
			}
			/*
			{
				if (nextNumber == divider)
				{
					currentPrimzahl = false;
				}
				else
				{
					divider++;
				}
			}*/
		}

		if(Primfound)
		{
			//primzahlen[primzahlCounter] = nextNumber;
			printf("%i\n", nextNumber);
			//MyFile << nextNumber << '\n';
			//primzahlCounter++;
			Primfound = false;
		}
		nextNumber++;
		divider = 2;
		if (nextNumber == AMOUNT)
		{
			notDone = false;
		}
		else
		{
			currentPrimzahl = true;
		}
	}
	MyFile.close();
	printf("done");
	_getch();
	return 0;
}

