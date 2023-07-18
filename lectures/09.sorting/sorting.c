#include <stdio.h>

int* bubbleSort(int *arr);
int* selectionSort(int *arr);
int* mergeSort(int *arr);

int main(void)
{
	int arr[] = { 5, 4, 3, 2, 1 };
	int length = sizeof(arr) / sizeof(arr[0]);

	int *sortedBubble = bubbleSort(arr);
	int *sortedSelection = selectionSort(arr);
	int *sortedMerge = mergeSort(arr);

	printf("Sorted with Bubble Sort:\n");
	for(int i = 0; i < length; i++)
	{
		printf("%i ", sortedBubble[i]);
	}
	printf("\n");

	printf("Sorted with Selection Sort:\n");
	for(int i = 0; i < length; i++)
	{
		printf("%i ", sortedSelection[i]);
	}
	printf("\n");

	printf("Sorted with Merge Sort:\n");
	for(int i = 0; i < length; i++)
	{
		printf("%i ", sortedMerge[i]);
	}
	printf("\n");

	return 0;
}

int* bubbleSort(int *arr)
{
	int length = sizeof(*arr) / sizeof(arr[0]);
	int *sorted = *arr;

	for(int i = 0; i < length - 1; i++)
	{
		int swaps = 0;

		for(int j = 0; j < length - 1; j++)
		{
			if(sorted[j] < sorted[j + 1])
			{
				int temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
				swaps++;
			}
		}

		if(swaps == 0)
			break;
	}

	printf("===========================\n");
	for(int i = 0; i < length; i++)
	{
		printf("%i ", sorted[i]);
	}
	printf("===========================\n");

	return sorted;
}

int* selectionSort(int *arr)
{
	return arr;
}

int* mergeSort(int *arr)
{
	return arr;
}
