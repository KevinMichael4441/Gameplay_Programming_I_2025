#include <iostream>

int main()
{	
	int x = 5;
	int *px = &x;

	std::cout << "Address of x: " << px << "\n";
	std::cout << "Value of x: " << *px << "\n";
	

	return 0;
}
