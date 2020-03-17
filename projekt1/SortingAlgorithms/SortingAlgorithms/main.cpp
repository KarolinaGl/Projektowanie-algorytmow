#include <iostream>
#include "MergeSort.h"
#include "QuickSort.h"
#include "IntroSort.h"
#include "Utility.h"
#include "HeapSort.h"
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;


const int lower = -1000000;
const int upper = 1000000;
const int arraySize = 1000;
const bool isAscending = false;
int* array = generateRandomArray(arraySize, lower, upper);

void testMergeSort(int* array, const int arraySize, const bool isAscending = true)
{
	std::cout << "Original array: ";
	printArray(array, arraySize);
	mergeSort(array, arraySize, isAscending);
	std::cout << "Array after merge sorting: ";
	printArray(array, arraySize);
	std::cout << "Array was " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted successfully" << std::endl;
	delete[] array;
}

void testQuickSort(int* array, const int arraySize, const bool isAscending = true)
{
	std::cout << "Original array: ";
	printArray(array, arraySize);
	quickSort(array, arraySize, isAscending);
	std::cout << "Array after quick sorting: ";
	printArray(array, arraySize);
	std::cout << "Array was " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted successfully" << std::endl;
	delete[] array;
}

void testHeapSort(int* array, const int arraySize, const bool isAscending = true)
{
	std::cout << "Original array: ";
	printArray(array, arraySize);
	std::cout << "Array after heap sorting: ";
	heapSort(array, arraySize, isAscending);
	printArray(array, arraySize);
	std::cout << "Array was " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted successfully" << std::endl;
	delete[] array;
}

void testIntroSort(int* array, const int arraySize, const bool isAscending = true)
{
	std::cout << "Original array: ";
	printArray(array, arraySize);
	introSort(array, arraySize, isAscending);
	std::cout << "Array after intro sorting: ";
	printArray(array, arraySize);
	std::cout << "Array was " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted successfully" << std::endl;
	delete[] array;
}

template<typename T>
double countTimeInSeconds(T* array, const int arraySize, std::string sortingType)
{
	high_resolution_clock::time_point start = high_resolution_clock::now();
	if (sortingType == "merge")
		mergeSort(array, arraySize);
	else if (sortingType == "quick")
		quickSort(array, arraySize);
	else
		introSort(array, arraySize);
	high_resolution_clock::time_point stop = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(stop - start);
	return time_span.count();
}

int main()
{
	/*
	printArray(array, arraySize);
	sortInPercent(array, arraySize, 0);
	printArray(array, arraySize);
	
	sortInPercent(array, arraySize, 0);
	std::cout << countTimeInSeconds(array, arraySize);
	*/
	int arraySizes[5] = { 10000, 50000, 100000, 500000, 1000000 };
	double percentOfSortedElements[8] = { 0, 25, 50, 75, 95, 99, 99.7, 100 };
	std::string sortingTypes[3] = {"merge", "quick", "intro"};
	int numberOfLoops = 1;

	for (std::string type : sortingTypes)
	{
		std::cout << type << " sort:\n";
		for (double percent : percentOfSortedElements)
		{
			std::cout << percent << "%: \n";
			for (int size : arraySizes)
			{
				std::cout << "size: " << size << "\n";
				for (int i = 0; i < numberOfLoops; i++)
				{
					int* array = generateRandomArray(size, lower, upper);
					sortInPercent(array, size, percent);
					std::cout << countTimeInSeconds(array, arraySize, type) << "\n";
				}
			}
		}
	}
	return 0;
}
