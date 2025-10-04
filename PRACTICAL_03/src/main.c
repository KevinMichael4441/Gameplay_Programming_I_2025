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
  bool hit;
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
  std::cout << "\nArm Missile?\n";
  std::cout << "Enter 0 to NOT arm missile.\n";
  std::cout << "Enter 1 TO arm missile.\n";
  std::cin >> playerArming;
  
  if (playerArming)
  {
    missile->armed = true;
    std::cout << "\nMissile Armed!\n";
  }
  else
  {
    missile->armed = false;
    std::cout << "\nMissile NOT Armed!\n";
  }
}

void setPayload(struct Missile *missile)
{
  bool choiceAccepted = false;	
  while (!choiceAccepted)
  {	
    int choice = 0;
    std::cout << "Enter 1 for EXPLOSIVE payload.\n";
    std::cout << "Enter 2 for NUCLEAR payload.\n";
    std::cin >> choice;
    std::cout << "\n";
	
    if (choice == 1 || choice == 2)
    {
      if (choice == 1)
        missile->payload = WarHead::EXPLOSIVE; 
      else if (choice == 2)
	missile->payload = WarHead::NUCLEAR;
	  
      choiceAccepted = true;
    }
    else 
    {
      std::cout << "ERROR - Enter 1 or 2!\n";
    }	
  }	
}


bool checkStrike(struct Missile *missile, struct Target *t_target)
{
  if (missile->payload == WarHead::EXPLOSIVE)
  {  
    if(missile->coordinates.x == t_target->coordinates.x && 
       missile->coordinates.y == t_target->coordinates.y)
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
        if (t_target->coordinates.x == affected[i][j].x &&
            t_target->coordinates.y == affected[i][j].y)
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

  std::cout << "Function Entered!!!\n\n";
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

  std::cout << "FUCTION RAN AND DONE\n\n";
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
  target1->hit = false;

  target2->coordinates.x = floor(rand()%10);
  target2->coordinates.y = floor(rand()%10);
  target2->hit = false;
  
  while (!target1->hit || !target2->hit)
  { 
    // Create a new Missile
    Missile *missile = (Missile *)malloc(sizeof(Missile));
	
    std::cout << "Enter Target x: \n";
    std::cin >> missile->target.coordinates.x;
    std::cout << "\nEnter Target y: \n";
    std::cin >> missile->target.coordinates.y;
    std::cout << "\n\n";
	
    // Set Initial Position
    missile->coordinates.x = 0;
    missile->coordinates.y = 0;

    setPayload(missile);
    armMissile(missile);

    missile->update = updateMissile;
    //checkPassword(missile);


    //Update Position
    while(missile->coordinates.x != missile->target.coordinates.x ||
    missile->coordinates.y != missile->target.coordinates.y)
    {
      std::cout << "ENTERED UPDATE WHILE LOOP\n\n";
      missile->update(missile);
      printf("Missile Updated!");
      printCoordinates(missile->coordinates);
    }

    // Print Missile Position
    printf("Print Missile Position after Update\n");
    printCoordinates(missile->coordinates);

    // Print Missile target
    printf("\nPrint Target Position\n");
    printCoordinates(target1->coordinates);
    printCoordinates(target2->coordinates);

    std::cout << "\n\n";

    if (checkStrike(missile, target1))
    {
      target1->hit = true;
      std::cout << "THE MISSILE HAS HIT THE FIRST TARGET!\n";
    }
 
    
    if (checkStrike(missile,target2))
    {
      target2->hit = true;
      std::cout << "THE MISSILE HAS HIT THE SECOND TARGET!\n";
    }
    // Free Missile Memory
    free(missile);

    
  }

  std::cout << "Congratz Comrade! You took out the targets!\n\n";
  
  free(target1);
  free(target2);
  
  return 0;
}

