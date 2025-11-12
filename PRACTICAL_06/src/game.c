#include "raylib.h"
#include "stdio.h"
#include "../include/game.h"
#include "../include/collisionLibrary.h"


Texture2D m_texture, idle, walkA, walkB, background;
myCircle m_circle;
myRectangle m_rect1, m_rect2;

myCircle m_playerCircle;
myRectangle m_playerRectangle;

Vector2 m_direction, m_position;
int m_velocity;

int m_currentWalk = 0;	// 0 or 1 for each animation frame
const int m_walkDelay = 15;	
int m_walkTimer = 0;
const int m_playerHeight = 102;
const int m_playerWidth = 84;


void InitGame() {
	
	// Loading Textures
    background = LoadTexture("resources/background.png");
    idle = LoadTexture("resources/player.png");
    walkA = LoadTexture("resources/walkA.png");
    walkB = LoadTexture("resources/walkB.png");
    m_texture = idle;
    m_direction = (Vector2){0,0};
    m_position = (Vector2){100,100};
    m_velocity = 4;
	
	m_circle = (myCircle){410,120,110};
	m_rect1 = (myRectangle){500,450,60,80};
	m_rect2 = (myRectangle){260,310,50,90};

    printf("Game Initialized!\n");
}

void UpdateGame() {
    UpdatePlayer();
}

void DrawMessage()
{
    DrawText("Click mouse button to draw primitives", 100,30,30, BLACK);
    DrawText("Press space to change colour", 100, 70, 30, BLACK);
    DrawText("Use Arrows to move", 100, 150, 30, BLACK);
}

void DrawGame() {

    DrawTexture(background,0,0,WHITE);
    
    if(IsMouseButtonDown(0) || IsMouseButtonDown(1) ||IsMouseButtonDown(2))
	// Drawing primitives only if mouse buttons are clicked
    {
	    DrawChristmasTree();
    }
		
		
	DrawRectangle(m_playerRectangle.x,m_playerRectangle.y,m_playerRectangle.width,m_playerRectangle.height, RAYWHITE);
	DrawCircle(m_playerCircle.x,m_playerCircle.y,m_playerCircle.radius,GOLD);	
	
    if (IsKeyDown(KEY_SPACE))
    {
	// Changin color of player when space is pressed
	    DrawTexture(m_texture,m_position.x,m_position.y,LIME);
    }
    else 
    {
	    DrawTexture(m_texture,m_position.x,m_position.y,WHITE);
    }

    DrawMessage();
	
}

void DrawChristmasTree()
{
	DrawCircle(m_circle.x,m_circle.y,m_circle.radius,(Color){253,240,0,255});	
	
    DrawRectangle(m_rect1.x,m_rect1.y,m_rect1.width,m_rect1.height,RED);
    DrawRectangle(m_rect2.x,m_rect2.y,m_rect2.width,m_rect2.height, RED);
		
    DrawTriangle((Vector2){410,200},(Vector2){290,330},(Vector2){530,330}, GREEN);
    DrawTriangle((Vector2){410,330},(Vector2){280,475},(Vector2){540,475}, GREEN);
    DrawTriangle((Vector2){410,475},(Vector2){325,590},(Vector2){490,590},DARKBROWN);
	
    DrawLineEx((Vector2){300,120},(Vector2){520,120},5,BLACK);
}


void CloseGame() {
    UnloadTexture(m_texture);
    UnloadTexture(walkA);
    UnloadTexture(walkB);
    UnloadTexture(background);
    UnloadTexture(idle);

    printf("Game Closed!\n");
}


void UpdatePlayer()
{
    m_direction.x = (int)(IsKeyDown(KEY_RIGHT)) - (int)(IsKeyDown(KEY_LEFT));
	// 1-0 = 1 if right key down; 0-1 = -1 if left key down
    m_direction.y = (int)(IsKeyDown(KEY_DOWN)) - (int)(IsKeyDown(KEY_UP));

    m_direction = Vector2Normalize(m_direction);

    if (m_direction.x == 0 && m_direction.y == 0)
    {
	    m_texture = idle;
    }
    else if (m_currentWalk == 0 && m_walkTimer > m_walkDelay)
    {
        m_currentWalk = 1;
        m_texture = walkA;
        m_walkTimer = 0;
    }
    else if ((m_currentWalk == 1 && m_walkTimer > m_walkDelay))
    {
        m_currentWalk = 0;
        m_texture = walkB;
        m_walkTimer = 0;
    }

    m_walkTimer++;


    MovePlayer();
    BoundaryChecking();
	
	m_playerCircle = (myCircle){m_position.x + m_playerWidth/2, m_position.y + m_playerHeight/2, (int)(m_playerHeight/2)};
	m_playerRectangle = (myRectangle){m_position.x, m_position.y, m_playerWidth, m_playerHeight};
}

void MovePlayer()
{   
    m_position.x += m_direction.x * m_velocity;
    m_position.y += m_direction.y * m_velocity;
}

void BoundaryChecking()
{
    if (m_position.x < 0)
    {
        m_position.x += m_velocity;
    }
    else if (m_position.x > 800 - 128)
    {
        m_position.x -= m_velocity;
    }

    if (m_position.y < 0)
    {
        m_position.y += m_velocity;
    }
    else if (m_position.y > 600 - 128)
    {
        m_position.y -= m_velocity;
    }
}
