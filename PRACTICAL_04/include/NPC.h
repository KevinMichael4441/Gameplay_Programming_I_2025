#ifndef NPC_H
#define NPC_H

#include <./include/GameObject.h> // Include the GameObject header

// NPC is a GameObject
class NPC : public GameObject
{
public:
    NPC(std::string name, int health = 100) : GameObject(name, health) {} // Constructor to initialize name and health

    void taunt();                             // Method for NPC to taunt the player
    void walk() override;                     // Specific implementation of walk()
    void attack(GameObject& target) override; // Implementation of pure virtual attack method
    void defend() override;                   // Optionally override defend method
};

#endif // NPC_H
