#include <iostream>
#include <string>

#include "../include/collisionLibrary.h"


int main()
{
    Rectangle *r1;
    r1->x = 2;
    r1->y = 3;
    r1->width = 6;
    r1->height = 2;
 
    Rectangle *r2;
    r2->x = 7;
    r2->y = 1;
    r2->width = 3;
    r2->height = 3;
    
    std::cout << "\n\nIt is " + std::to_string(rectangleToRectangle(r1, r2)) + " that the rectangles collide!\n\n";


    return 0;
}
