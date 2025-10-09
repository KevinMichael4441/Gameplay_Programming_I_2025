#include <./include/Player.h>        // Include the Player header
#include <iostream>       // For std::cout
#include <string>         // For std::string

// Method for Player to charge at an enemy
void Player::charge() {
    std::cout << name << " charges at the enemy!" << std::endl;
}

// Specific implementation of walk()
void Player::walk() {
    std::cout << name << " walks forward." << std::endl;
}

// Implementation of pure virtual attack method
void Player::attack(GameObject& target) {
    std::cout << name << " attacks " << target.getName() << "!" << std::endl;
    // Add logic to modify the target's health
    target.takeDamage(10); // Example: deal 10 damage to the target
}

// Optionally override defend method
void Player::defend() {
    std::cout << name << " takes a defensive stance." << std::endl;
}
