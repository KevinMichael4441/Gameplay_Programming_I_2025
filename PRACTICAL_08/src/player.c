#include <stdio.h>

#include "../include/player.h"

// Move player up
void player_move_up(Player* player) {
    player->y -= 1;
    printf("Player moved up to (%d, %d)\n", player->x, player->y);
}

void player_move_up_fire(Player* player) {
    player->y -= 1;
    printf("\n\nPlayer moved up to (%d, %d) and FIRED\n\n", player->x, player->y);
}

// Move player down
void player_move_down(Player* player) {
    player->y += 1;
    printf("Player moved down to (%d, %d)\n", player->x, player->y);
}

// Move player left
void player_move_left(Player* player) {
    player->x -= 1;
    printf("Player moved left to (%d, %d)\n", player->x, player->y);
}

// Move player right
void player_move_right(Player* player) {
    player->x += 1;
    printf("Player moved right to (%d, %d)\n", player->x, player->y);
}

// Player fires
void player_fire(Player* player) {
    printf("Player fired at position (%d, %d)\n", player->x, player->y);
}

void player_jump(Player* player){
    printf("Player jumped at position (%d, %d)\n", player->x, player->y);

    // Send Event!!!
}

void player_jump_fire(Player* player){
    (void)player;
    printf("\n\nJumping and Firing\n\n");
}
