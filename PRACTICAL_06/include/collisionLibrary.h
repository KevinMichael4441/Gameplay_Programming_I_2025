#ifndef COLLISION_LIBRARY_H
#define COLLISION_LIBRARY_H

#include <math.h>


typedef struct myCircle
{
    float x, y;
    float radius;
} myCircle;

typedef struct myRectangle
{
    float x, y;
    float width, height;
} myRectangle;


bool circleToCircle(myCircle* t_c1, myCircle* t_c2)
{
    // Distace b/w c1 and c2
    float deltaX = (t_c1->x) - (t_c2->x);
    float deltaY = (t_c1->y) - (t_c2->y);

    float dXSquared = deltaX * deltaX;
    float dYSquared = deltaY * deltaY;

    float distance = sqrt(dXSquared + dYSquared);

    

    // sum of radius
    float radiusSum = t_c1->radius + t_c2->radius;


    // if radiusSum > distance( then collision)
    if (radiusSum >= distance)
    {
        return true;
    }
    else 
    {
        return false;
    }
}


bool valueInRange(int value, int min, int max)
{
  return (value >= min) && (value <= max); 
}

bool rectangleToRectangle(myRectangle* t_r1, myRectangle* t_r2)
{
    bool xAxisOverlap = valueInRange(t_r1->x, t_r2->x, t_r2->x + t_r2->width) ||
			valueInRange(t_r2->x, t_r1->x, t_r1->x + t_r1->width);

    bool yAxisOverlap = valueInRange(t_r1->y, t_r2->y, t_r2->y + t_r2->height) ||
			valueInRange(t_r2->y, t_r1->y, t_r1->y + t_r1->height);

    return xAxisOverlap && yAxisOverlap;

}


#endif
