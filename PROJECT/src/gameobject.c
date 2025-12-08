#include "./gameobjects/gameobject.h"
#include "./utils/constants.h"
/**
 * InitGameObject : Sets up a fresh GameObject with all the basics.
 *
 * Gives the poor creature a name, a position, a collider, some colour,
 * a pile of health, and whatever else it needs to exist without falling
 * apart immediately.
 *
 * @object:       The GameObject being brought into the world.
 * @name:         Its fancy new name.
 * @position:     Where it starts on the screen.
 * @currentState: Its starting state (usually IDLE unless it's dramatic).
 * @color:        The default draw colour.
 * @collider:     For bumping into things.
 * @keyframes:    The sprite sheet used for animations.
 * @health:       Starting health ... try not to waste it.
 */

void InitGameObject(GameObject *object,
                    const char *name,
                    Vector2 position,
                    State currentState,
                    Color color,
                    c2Circle collider,
                    Texture2D keyframes,
                    int health)
{
    // Set the GameObject's name
    object->name = name;

    object->position = position;

    // Initialize the previous and current states to currentState (normally IDLE)
    object->currentState = currentState;
    object->previousState = STATE_COUNT; // So that at initial load idle animation is loaded

    object->color = color;
    object->collider = collider;
    object->keyframes = keyframes;
    object->health = health;
}

/**
 * ClampGameObjectOnScreen - Keeps the object from wandering off stage.
 *
 * Ensures the object stays within screen bounds, instead of hoofing it
 * straight into the void like it has somewhere better to be, searching for 
 * a swan feather and some squid ink to take notes in class.
 *
 * @object: The GameObject being reined in.
 */

void ClampGameObjectOnScreen(GameObject *object)
{
	if (object->position.x < object->collider.r)
		object->position.x = object->collider.r;
	if (object->position.x > SCREEN_WIDTH - object->collider.r)
		object->position.x = SCREEN_WIDTH - object->collider.r;
	if (object->position.y < object->collider.r)
		object->position.y = object->collider.r;
	if (object->position.y > SCREEN_HEIGHT - object->collider.r)
		object->position.y = SCREEN_HEIGHT - object->collider.r;
}

/**
 * InitGameObjectAnimation - Gives the GameObject a working animation.
 *
 * Sets up looping animation using the object's sprite sheet and a list
 * of frames. Once this is done, the object won't just stand there like
 * a cardboard cut-out.... or even worse like a lecturer stuck on pause.
 *
 * @object:     The object that's getting animated.
 * @frames:     Rectangles describing each frame on the sprite sheet.
 * @frameCount: How many frames to play through.
 * @speed:      How fast the animation moves (seconds per frame).
 */

void InitGameObjectAnimation(GameObject *object, Rectangle *frames, int frameCount, float speed)
{
    AnimationData animation;
    InitAnimation(&animation, object->keyframes, frames, frameCount, speed, true);
    object->animation = animation;
}

/**
 * DeleteGameObject - Frees all memory linked to the GameObject.
 *
 * Cleans up state transition tables and then the object itself,
 * so you don't end up leaking memory all over the shop....see purge notes
 *
 * @object: The GameObject to be sent off outa the big heap into the sky.
 */

void DeleteGameObject(GameObject *object)
{
    if (object == NULL)
        return;

    // Check if state configurations exist for this GameObject
    if (object->stateConfigs)
    {
        // Free each state's nextStates array if it exists
        for (int i = 0; i < STATE_COUNT; i++)
        {
            if (object->stateConfigs[i].eventStateTransitions != NULL)
            {
                free(object->stateConfigs[i].eventStateTransitions);
                object->stateConfigs[i].eventStateTransitions = NULL; // Nullify the pointer after freeing
            }
        }

        // Free state configurations
        free(object->stateConfigs);
        object->stateConfigs = NULL; // Nullify after freeing
    }

    // Free the GameObject
    free(object);
    object = NULL; // Nullify
}
