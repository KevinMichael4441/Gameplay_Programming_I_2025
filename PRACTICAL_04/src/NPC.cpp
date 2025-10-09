#include <./include/NPC.h> // Include the NPC header
#include <iostream>        // For std::cout
#include <string>          // For std::string

// Method for NPC to taunt the player
void NPC::taunt()
{
    std::cout << name << " taunts you: 'Is that all you've got?'" << std::endl;
}

// Specific implementation of walk()
void NPC::walk()
{
    std::cout << name << " walks forward." << std::endl;
}

// Implementation of pure virtual attack method
void NPC::attack(GameObject &target)
{
    std::cout << name << " attacks " << target.getName() << "!" << std::endl;
    // Add logic to modify the target's health
    target.takeDamage(10); // Example: deal 10 damage to the target
}

// Optionally override defend method
void NPC::defend()
{
    std::cout << name << " takes a defensive stance." << std::endl;
}
