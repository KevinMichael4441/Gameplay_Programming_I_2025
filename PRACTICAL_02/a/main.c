#include <iostream>

int main()
{
	
	int a = 10;
	int *p = &a;

	std::cout << "Value of a: " << a << "\n";
	std::cout << "Address of a: " << &a << "\n";
	std::cout << "Pointernp points to: " << p << "\n";
	std::cout << "Value pointed by p: " << *p << "\n";
		
	return 0;
}
