#include <stdlib.h>
#include <time.h>

#include "./command/command.h"
#include "./utils/ai_manager.h"
#include "./gameobjects/npc.h"

/**
 * InitAIManager : Sets up the AI manager....or at least pretends to. It does 
 * not a thing at the moment.
 *
 * Here for when you eventually give your NPCs a few more brain cells 
 * to rub together.
 *
 * Add proper setup later if the AI gets notions.
 */

void InitAIManager()
{
	// Initialize AI
}

/**
 * PollAI : Gets a random command from the AI, sure why not.
 *
 * This fella doesn't think too hard...he just picks a command at random
 * like someone closing their eyes and throwing darts at a pub wall.
 *
 * Handy for testing or for NPCs that aren't exactly the sharpest tools
 * in the shed (yet).
 *
 * @return: A random Command somewhere between 0 and COMMAND_COUNT-1.
 */

Command PollAI(NPC *npc)
{
	Vector2 targetCenter = npc->base.target;
	Vector2 AICenter = npc->base.position;

	float distance = Vector2Distance(targetCenter, AICenter);

	if (distance > 500)
	{
		return NONE;
	}
	else if (distance > 100)
	{
		int action = rand() % 2;
		switch (action)
		{
			case 0:
				return getMoveCommand(AICenter, targetCenter);
				break;
			case 1:
				return NONE;
				break;
		}
	}
	else
	{
		int action = rand() % 10;
		switch (action)
		{
			case 0:
			case 1:
			case 2:
			case 3:
				return getMoveCommand(AICenter, targetCenter);
				break;
			case 4:
			case 5:
			case 6:
				return ATTACK;
				break;
			case 7:
			case 8:
			case 9:
				return DEFEND;
				break;

		}
	}

	return NONE;
}

Command getMoveCommand(Vector2 t_AICenter, Vector2 t_targetCenter)
{
	Vector2 futureAICenter = Vector2MoveTowards(t_AICenter, t_targetCenter, 10);
	Vector2 directionToMove = {futureAICenter.x - t_AICenter.x, futureAICenter.y - t_AICenter.y};
	Command command = NONE;

	if (directionToMove.x >= 0 && directionToMove.y >= 0)
	{
		command |= MOVE_RIGHT;
		command |= MOVE_DOWN;
	}
	else if (directionToMove.x >= 0 && directionToMove.y <= 0)
	{
		command |= MOVE_RIGHT;
		command |= MOVE_UP;
	}
	else if (directionToMove.x <= 0 && directionToMove.y >= 0)
	{
		command |= MOVE_LEFT;
		command |= MOVE_DOWN;
	}
	else if (directionToMove.x <= 0 && directionToMove.y <= 0)
	{
		command |= MOVE_LEFT;
		command |= MOVE_UP;
	}

	return command;
}

/**
 * ExitAIManager : Cleans up after the AI manager... in theory.
 *
 * There's nothing to tidy up yet, but this is the spot for it
 * once the AI starts doing more than guessing like a toddler.
 *
 * Add proper cleanup here when the AI grows up a bit.
 */

void ExitAIManager()
{
	// Cleanup resources if needed : Currently a placeholder.
	// Add any necessary cleanup logic here (e.g., freeing memory, closing files).
}
