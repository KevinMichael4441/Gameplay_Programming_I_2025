#include <iostream>

int main() {
	
	int arr[3] = {10,20,30};
	int *pArr = arr;

	for (int i = 0; i < 3; i++)
	{
		std::cout << "Element " << i << " is: " << *(pArr + i) << "\n";
	}
	
	return 0;
}

