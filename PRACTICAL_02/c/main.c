#include <iostream>

int main()
{
	int *dynamicArray = new int[5];	// Allocates memory for 5 integers
	for (int i = 0; i < 5; i++) {
	
		dynamicArray[i] = i + 1;	// Assigns value to the array
		std::cout << dynamicArray[i] << " is in memory " << &dynamicArray[i] << "\n";
	}

	delete[] dynamicArray;	// Frees the allocated memory

	return 0;
}
