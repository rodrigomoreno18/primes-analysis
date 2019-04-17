#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000

int* read(const char*);
void store(const char*, int*, int);

void fill(char*, char);
void graph(const char*, int*, int, int);

int* differences(int*, int);

int main()
{
	int *primes;

	primes = read("primes.txt");

	int *diffs = differences(primes, MAX);

	graph("graph.txt", diffs, 75, MAX - 1);

	store("out.txt", diffs, MAX - 1);

	free(primes);
	free(diffs);

	return 0;
}

int* read(const char* fileName)
{
	FILE *fp;

	fp = fopen(fileName, "r");

	if (!fp)
	{
		printf("Error opening file '%s', aborting...\n", fileName);
		exit(1);
	}

	int *primes = malloc(sizeof(int) * MAX);
	int i = 0;

	while (fscanf(fp, "%d,", &(primes[i])) != EOF) {
		// printf("(%d) : ", primes[i]);

		if (i == MAX - 1)
			break;

		i++;
	}

	fclose(fp);

	return primes;
}


void store(const char* fileName, int* primes, int quantity)
{
	FILE *fp;
	fp = fopen(fileName, "w");

	if (!fp)
	{
		printf("Error opening file '%s', aborting...\n", fileName);
		exit(1);
	}

	for (int i = 0 ; i < quantity ; i++)
	{
		fprintf(fp, "%d, ", primes[i]);
	}

	fclose(fp);

	return;
}


void fill(char* array, char filler)
{
	for (int i = 0 ; i < strlen(array) && i < MAX; i++)
	{
		array[i] = filler;
	}

	return;
}

void graph(const char* fileName, int* values, int height, int quantity)
{
	FILE *fp;
	fp = fopen(fileName, "w");

	if (!fp)
	{
		printf("Error opening file '%s', aborting...\n", fileName);
		exit(1);
	}

	char *line = malloc(sizeof(char) * (quantity + 1));
	line[quantity] = '\0';
	//fill(line, ' ');

	for (int i = height - 1 ; i >= 0 ; i--)
	{
		for (int j = 0 ; j < quantity ; j++)
		{
			if (i == values[j])
				line[j] = 254;
			else if (i < values[j])
				line[j] = 254;
			else
				line[j] = ' ';
		}

		fprintf(fp, "%2d | %s\n", i+1, line);
	}

	fclose(fp);

	return;
}


int* differences(int* list, int quantity)
{
	int *diffs = malloc(sizeof(int) * (quantity - 1));

	int largestDiff = 0;

	for (int i = 0 ; i < quantity - 1 ; i++)
	{
		diffs[i] = list[i + 1] - list[i];

		if (diffs[i] > largestDiff)
		{
			largestDiff = diffs[i];
			printf("(%d : at %d) | ", largestDiff, list[i+1]);
		}
	}

	printf("\nLargest difference is %d.\n", largestDiff);

	return diffs;
}