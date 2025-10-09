#ifndef PLAYER_H
#define PLAYER_H

#include <./include/GameObject.h> // Include the GameObject header

// Player is a GameObject
class Player : public GameObject
{
public:
    Player(std::string name, int health = 100) : GameObject(name, health) {} // Constructor to initialize name and health

    void charge();                            // Method for Player to charge at an enemy
    void walk() override;                     // Specific implementation of walk()
    void attack(GameObject& target) override; // Implementation of pure virtual attack method
    void defend() override;                   // Optionally override defend method
};

#endif // PLAYER_H
