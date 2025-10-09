#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <string>

// Abstract GameObject Class
class GameObject
{
protected:
    std::string name; // Protected so derived classes can access it
    int health;       // Protected so derived classes can access it

public:
    // Constructor to initialize health (default is set to 100)
    GameObject(std::string name = "PlayerUnknown", int health = 100) : name(name), health(health) {}

    // GameObject Methods

    // Returns the current health of the GameObject
    // Marked as const as it does not modify member variable
    int getHealth() const;

    // Returns the name of the GameObject
    // Marked as const as it does not modify member variable
    std::string getName() const;

    // Pure virtual function for attack. This function must be implemented by derived classes.
    virtual void attack(GameObject&) = 0;

    // Virtual method for defense. This can be overridden by derived classes if needed.
    virtual void defend();

    // Virtual method for walking behavior. Can be overridden by subclasses to provide specific implementations.
    virtual void walk();

    // Instance method takeDamage
    void takeDamage(int);
};

#endif // GAME_OBJECT_H
