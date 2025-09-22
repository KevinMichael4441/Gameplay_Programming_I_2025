#include <iostream>

int main(){
	
	int b = 20;
	int *pb = &b;
	*pb = 30;
 
	std::cout << "New value of b: " << b << "\n";

	return 0;
}
