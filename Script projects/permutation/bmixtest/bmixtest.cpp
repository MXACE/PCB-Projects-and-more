// i/o example
#include <conio.h>
#include "stdafx.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <windows.h>

#define DATPATH "Permutationen.txt"

int main() {

	char Alpha_IN[200] = { 0 };
	char myints[200] = {1,2,3,4,5,6};

	unsigned int i = 0;
	unsigned char ucStop = 0;
	unsigned char ucMode = 0;
	double dCounter = 0;

	FILE *f;

	fopen_s(&f, DATPATH, "w");

	if (f == NULL) perror("Error opening file");

	for (i = 0; i != sizeof(Alpha_IN); i++)
	{
		Alpha_IN[i] = '\n';
	}


	  ////////////////////////
			ucMode = 2;
	////////////////////////

	switch (ucMode)
	{
		case 1:
			//--------------------------------------------------------------------

			printf("Geben Sie die gewuenschten Buchstaben ein: ");
			gets_s(Alpha_IN);

			system("cls");
			//--------------------------------------------------------------------

			for (i = 0; Alpha_IN[i] != '\0'; i++)
			{
				ucStop++;
			}

			//--------------------------------------------------------------------

			std::sort(Alpha_IN, Alpha_IN + ucStop);

			//--------------------------------------------------------------------

			do {

				dCounter++;

				
				for (i = 0; i != ucStop; i++)
				{
					fprintf_s(f,"%c ", Alpha_IN[i]);
				}

				printf("%.0f\n", dCounter);
				fprintf(f,"\n");

			} while (std::next_permutation(Alpha_IN, Alpha_IN + ucStop));
			break;
			//--------------------------------------------------------------------

		case 2:

			//--------------------------------------------------------------------

			system("cls");

			//--------------------------------------------------------------------

			std::sort(myints, myints + 6);

			//--------------------------------------------------------------------

			do {
				for (i = 0; i != 6; i++)
				{
					printf("%i ", myints[i]);
				}

				printf("\n");

				printf("%i ", myints[3] + myints[4] + myints[5]);
				printf("\n");

				system("pause");

			} while (std::next_permutation(myints, myints + 6));
			break;
			//--------------------------------------------------------------------
		default:
			printf("Error");
	}
	
	system("pause");
	return 0;
}