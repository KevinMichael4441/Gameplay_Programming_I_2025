#include <./include/GameObject.h>

// Implementation of GameObject Methods

// Getter for name, marked as const
std::string GameObject::getName() const
{
    return name;
}

// Getter for health, marked as const
int GameObject::getHealth() const
{
    return health;
}

// Default defend implementation
void GameObject::setDefendState()
{
    state = GameObject::States::DEFEND;
}

void GameObject::setAttackState()
{
    state = GameObject::States::ATTACK;
}

void GameObject::defend()
{
    std::cout << name << " GameObject : Defending..." << std::endl;
}

// Default takeDamage implementation
void GameObject::takeDamage(int damage)
{
    health -= damage;
    std::cout << name << " GameObject : Takes Damage : " << damage << " Health : " << health << std::endl;
}