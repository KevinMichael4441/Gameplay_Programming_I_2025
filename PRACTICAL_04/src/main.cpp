#include <iostream>

#include <./include/Player.h>
#include <./include/NPC.h>

class Game
{
private:
    Player player;
    NPC npc;

    GameObject *winner = nullptr;

public:
    Game() : player("Orc (Player)"), npc("Troll (Boss)") {}


	void setStates()
	{
		int playerAction  = 0;
	
		while(playerAction == 0)
		{
			std::cout << "Choose your Action:\n";
			std::cout << "1 - Attack\n2 - Defend";
			std::cin >> playerAction;
			
			if (playerAction == 1)
			{
				player.setAttackState();
			}
			else if (playerAction == 2) 
			{
				player.setDefendState();
			}
			else
			{
				std::cout << "Choose one of these options!\n";
				playerAction = 0;
			}	
		}
		
		int aiState = rand() % 11;
		
		if (aiState < 5)
		{
			npc.setAttackState();
		}
		else if (aiState < 10)
		{
			npc.setDefendState();
		}
		else
		{
			npc.setTauntState();
		}	
	}	

    void gameloop()
    {
        std::cout << "Let make a virtual ;-) Turn Based Console Game" << std::endl;

        // Uncomment and try to compile. Why are errors produced?
        // GameObject go; // Error: Cannot instantiate an abstract class (GameObject has pure virtual methods)
        // go.attack(); // Error: attack is a pure virtual method

        // Uncomment and try to compile. What happens when we try to access a pure virtual method directly?
        // NPC npc;
        // npc.attack(nullptr); // Error: attack is a pure virtual method - Cannot call this directly from the base class

        // Uncomment and try to compile. What happens if we try to access a non-virtual method?
        // NPC npc;
        // npc.getHealth(); // This is fine, but if getHealth() is not overridden, it uses the base class method

        std::cout << "Let go create a Player" << std::endl;
        player.walk(); // Method call walk() - Bound at compile time to Player's walk()

        std::cout << "Let go create an NPC" << std::endl;
        npc.walk(); // Method call walk() - Bound at compile time to NPC's walk()

        // Uncomment to see the issue with calling the pure virtual method
        // player.attack(nullptr); // Error: Cannot call attack on Player; it must be implemented

        // Main GameLoop
        while (player.getHealth() > 0 && npc.getHealth() > 0)
        {

			setStates();
			
			if (npc.state == GameObject::States::TAUNT)
			{
				if (player.state == GameObject::States::ATTACK)
				{
					npc.taunt();
					player.attack(npc);
				}	
				else if (player.state == GameObject::States::DEFEND)
				{
					player.defend();
				}	
			}
			else if (npc.state == GameObject::States::DEFEND)
			{
				if (player.state == GameObject::States::ATTACK)
				{
					npc.defend();
				}	
				else if (player.state == GameObject::States::DEFEND)
				{
					player.defend();
					npc.defend();
				}	
			}
			else if (npc.state == GameObject::States::ATTACK)
			{
				if (player.state == GameObject::States::ATTACK)
				{
					//resolveAttack();
					npc.attack(player);
					player.attack(npc);
				}	
				else if (player.state == GameObject::States::DEFEND)
				{
					player.defend();
				}	
			}

			
            // Check for winner
            if (player.getHealth() == 0)
            {
                winner = &npc;
                break; // End loop if winner is determined
            }
            else if (npc.getHealth() <= 0)
            {
                winner = &player;
                break; // End loop if winner is determined
            }
        }

        // Output the winner
        if (winner)
        {
            std::cout << winner->getName() << " has won the battle!" << std::endl;
        }
    }
};

int main()
{
    Game game;
    game.gameloop();
    std::cin.get();
}
