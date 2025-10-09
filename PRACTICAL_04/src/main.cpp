#include <iostream>

#include <./include/Player.h>
#include <./include/NPC.h>

using namespace std;

class Game
{
private:
    Player player;
    NPC npc;

    GameObject *winner = nullptr;

public:
    Game() : player("Orc (Player)"), npc("Troll (Boss)") {}

    void gameloop()
    {
        cout << "Let make a virtual ;-) Turn Based Console Game" << endl;

        // Uncomment and try to compile. Why are errors produced?
        // GameObject go; // Error: Cannot instantiate an abstract class (GameObject has pure virtual methods)
        // go.attack(); // Error: attack is a pure virtual method

        // Uncomment and try to compile. What happens when we try to access a pure virtual method directly?
        // NPC npc;
        // npc.attack(nullptr); // Error: attack is a pure virtual method - Cannot call this directly from the base class

        // Uncomment and try to compile. What happens if we try to access a non-virtual method?
        // NPC npc;
        // npc.getHealth(); // This is fine, but if getHealth() is not overridden, it uses the base class method

        cout << "Let go create a Player" << endl;
        player.walk(); // Method call walk() - Bound at compile time to Player's walk()

        cout << "Let go create an NPC" << endl;
        npc.walk(); // Method call walk() - Bound at compile time to NPC's walk()

        // Uncomment to see the issue with calling the pure virtual method
        // player.attack(nullptr); // Error: Cannot call attack on Player; it must be implemented

        // Main GameLoop
        while (player.getHealth() > 0 && npc.getHealth() > 0)
        {
            // Player attacks NPC
            player.attack(npc); // Player attacks NPC - Bound at runtime to Player's attack()
            player.defend();    // Player defends - Bound at compile time to Player's defend()

            // NPC attacks Player
            npc.attack(player); // NPC attacks Player - Bound at runtime to NPC's attack()
            npc.defend();       // NPC defends - Bound at compile time to NPC's defend()

            // Assign NPC memory address to GameObject pointer
            GameObject *ptr_go = &npc;
            ptr_go->walk();         // Bound at runtime -> action based on pointer (NPC's walk())
            ptr_go->attack(player); // NPC attacks Player through GameObject pointer - Bound at runtime to NPC's attack()
            ptr_go->defend();       // NPC defends through GameObject pointer - Bound at runtime to NPC's defend()

            // Assign Player memory address to GameObject pointer
            ptr_go = &player;
            ptr_go->walk();      // Bound at runtime -> action based on pointer (Player's walk())
            ptr_go->attack(npc); // Player attacks NPC through GameObject pointer - Bound at runtime to Player's attack()
            ptr_go->defend();    // Player defends through GameObject pointer - Bound at runtime to Player's defend()

            // Check for winner
            if (player.getHealth() <= 0)
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
    cin.get();
}
