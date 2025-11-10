#include <iostream>
#include <string>

#include "../include/collisionLibrary.h"


int main()
{
    Circle *c1;
    c1->x = 5;
    c1->y = 0;
    c1->radius = 2;
 
    Circle *c2;
    c2->x = 0;
    c2->y = -5;
    c2->radius = 5;
    
    std::cout << "\n\nIt is " + std::to_string(circleToCircle(c1, c2)) + " that the circles collide!\n\n";


    return 0;
}
