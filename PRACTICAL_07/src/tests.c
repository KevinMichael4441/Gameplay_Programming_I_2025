// Please collision tests here

#include "tests.h"

// Recommend starting here so you get familiar with cute_c2 API

void TestCollisions(void)
{
	printf("Collision Tests\n");

	// Test 1: Circle to Circle
	c2Circle c1 = {{100, 100}, 50};
	c2Circle c2 = {{180, 100}, 50};
	printf("Circle-Circle (overlapping ?): %s\n",
		c2CircletoCircle(c1, c2) ? "PASS" : "FAIL");

	// Test 2: Ray to Circle
	// Ray starting at (0,100) going right with length 200
	c2Ray ray = {{0, 100}, {1, 0}, 200};

	// c2Raycast to store result
	c2Raycast out;
	printf("Ray-Circle (hit ?): %s\n",
		c2RaytoCircle(ray, c1, &out) ? "PASS" : "FAIL");

	// Add more tests...
}