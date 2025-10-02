#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <iostream>

// Define Position xy struct
typedef struct Position
{
  int x;
  int y;
} Coordinates;

// Define WarHead enum type
typedef enum
{
  EXPLOSIVE,
  NUCLEAR
} WarHead;

// Define Enemy struct type with Coordinates
typedef struct Target
{
  Coordinates coordinates;
} Target;

// Define Missile struct type with WarHead, Coordinates, Target, and armed status
typedef struct Missile
{
  WarHead payload;
  Coordinates coordinates;
  Target target;

  bool armed;

  // ADVANCED: Function pointers (direct function calls can be used instead)
  // Function pointer to update missile position

  void (*update)(struct Missile *missile);

  // Function pointer to arm or disarm missile
  void (*arm)(struct Missile *missile);

} Missile;

// Function to arm or disarm a missile
void armMissile(struct Missile *missile)
{
  bool playerArming;
  std::cout << "Arm Missile?(0 for no; 1 for ye)\n";
  std::cin >> playerArming;
  
  if (playerArming)
    missile->armed = true;
  else
    missile->armed = false;
}

bool checkStrike(struct Missile *missile, struct Target *target1, struct Target *target2)
{
  if (missile->payload == WarHead::EXPLOSIVE)
  {  
    if((missile->coordinates.x == target1->coordinates.x && 
        missile->coordinates.y == target1->coordinates.y) ||
       (missile->coordinates.x == target2->coordinates.x &&
        missile->coordinates.y == target2->coordinates.y))
    {
      return true;
    }
  }

  else if (missile->payload == WarHead::NUCLEAR)
  {
    int const MAX_SIZE = 3;
    Coordinates affected[MAX_SIZE][MAX_SIZE];
    Coordinates pointOfContact = missile->coordinates;

    for (int i = 0; i < MAX_SIZE; i++)
    {
      for (int j = 0; j < MAX_SIZE; j++)
      {
        affected[i][j].x = pointOfContact.x + i - 1;
        affected[i][j].y = pointOfContact.y + j - 1;	      
      } 
    }
  

    for (int i = 0; i < MAX_SIZE; i++)
    {
      for (int j = 0; j < MAX_SIZE; j++)
      {
        if (target1->coordinates.x == affected[i][j].x &&
            target1->coordinates.y == affected[i][j].y)
        {
          return true;
        }
      } 
    }
  }

  return false;
}

// Function to update missile position
void updateMissile(struct Missile *missile)
{
  if (missile->target.coordinates.x < missile->coordinates.x)
  {
    missile->coordinates.x--;
  }else if (missile->target.coordinates.x > missile->coordinates.x)
  {
    missile->coordinates.x++;
  }

  if (missile->target.coordinates.y < missile->coordinates.y)
  {
    missile->coordinates.y--;
  }else if (missile->target.coordinates.y > missile->coordinates.y)
  {
    missile->coordinates.y++;
  }
}

// Function to print coordinates
void printCoordinates(Coordinates c)
{
  printf("X: %d, Y: %d\n", c.x, c.y);
}

// Main entry point for the game
int main()
{
  srand(time(nullptr));
  // Create a new Target
  Target *target1 = (Target *)malloc(sizeof(Target));
  Target *target2 = (Target *)malloc(sizeof(Target));


  // Set Enemy Position / Target coordinates
  target1->coordinates.x = floor(rand()%10);
  target1->coordinates.y = floor(rand()%10);

  target2->coordinates.x = floor(rand()%10);
  target2->coordinates.y = floor(rand()%10);


  // Print Target Coordinates
  printf("Print Target Coordinates\n");
  printCoordinates(target1->coordinates);
  printCoordinates(target2->coordinates);

  // Create a new Missile
  Missile *missile = (Missile *)malloc(sizeof(Missile));

  // Set Missile Payload
  std::cout << "Enter Target x: \n";
  std::cin >> missile->target.coordinates.x;
  std::cout << "Enter Target y: \n";
  std::cin >> missile->target.coordinates.y;
  std::cout << missile->target.coordinates.x;
  std::cout << missile->target.coordinates.y;

  missile->payload = NUCLEAR;
  missile->arm = armMissile;
  missile->update = updateMissile;

  // Set Missile Armed Status
  missile->arm(missile);

  // Print Missile Armed Status
  if (missile->armed)
    printf("Missile is Armed\n");
  else
    printf("Missile is NOT Armed\n");

  // Set Initial Position
  missile->coordinates.x = 0;
  missile->coordinates.y = 0;

  // Update Position
  while(missile->coordinates.x != missile->target.coordinates.x ||
  missile->coordinates.y != missile->target.coordinates.y)
  {
    missile->update(missile);
    printf("Missile Updated!");
    printCoordinates(missile->coordinates);
  }

  // Print Missile Position
  printf("Print Missile Position after an Update\n");
  printCoordinates(missile->coordinates);

  // Print Missile target
  printf("Print Missile Target Position\n");
  printCoordinates(missile->target.coordinates);

  std::cout << "\n\n";
  std::cout << checkStrike(missile, target1,target2) << "\n";
  

  // Free Memory
  free(target2);
  free(target1);
  free(missile);

  // Pause
  printf("Press Enter to end game.\n");
  getchar();

  return 0;
}

