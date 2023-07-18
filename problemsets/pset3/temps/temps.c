#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    char *city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);
void sort(avg_temp *temps, int leftIndex, int rightIndex);
void merge(avg_temp *temps, int leftIndex, int middleIndex, int rightIndex);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// mergesort
void sort_cities(void)
{
    int leftIndex = 0;
		int rightIndex = NUM_CITIES - 1;
		sort(temps, leftIndex, rightIndex);
}

void sort(avg_temp *temps, int leftIndex, int rightIndex)
{
		if(leftIndex >= rightIndex) return;

		int middleIndex = (leftIndex + rightIndex) / 2;

		sort(temps, leftIndex, middleIndex);
		sort(temps, middleIndex + 1, rightIndex);
		merge(temps, leftIndex, middleIndex, rightIndex);
}

void merge(avg_temp *temps, int leftIndex, int middleIndex, int rightIndex)
{
		int lArrayLength = middleIndex - leftIndex + 1;
		int rArrayLength = rightIndex - middleIndex;

		avg_temp lArray[lArrayLength], rArray[rArrayLength];

		for (int i = 0; i < lArrayLength; i++)
		{
				lArray[i] = temps[leftIndex + i];
		}

		for (int i = 0; i < rArrayLength; i++)
		{
				rArray[i] = temps[(middleIndex + 1) + i];
		}

		int lArrayIndex = 0;
		int rArrayIndex = 0;
		int mergedArrayIndex = leftIndex;

		while(lArrayIndex < lArrayLength && rArrayIndex < rArrayLength)
		{
				if (lArray[lArrayIndex].temp >= rArray[rArrayIndex].temp)
				{
						temps[mergedArrayIndex] = lArray[lArrayIndex];
						lArrayIndex++;
				}
				
				else
				{
						temps[mergedArrayIndex] = rArray[rArrayIndex];
						rArrayIndex++;
				}

				mergedArrayIndex++;
		}

		while(lArrayIndex < lArrayLength)
		{
				temps[mergedArrayIndex] = lArray[lArrayIndex];
				lArrayIndex++;
				mergedArrayIndex++;
		}	

		while(rArrayIndex < rArrayLength)
		{
				temps[mergedArrayIndex] = rArray[rArrayIndex];
				rArrayIndex++;
				mergedArrayIndex++;
		}
}
