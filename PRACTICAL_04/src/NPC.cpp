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