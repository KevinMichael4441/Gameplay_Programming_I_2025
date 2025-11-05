#include "raylib.h"
#include "stdio.h"
#include "../include/game.h"


Texture2D m_texture, idle, walkA, walkB;
Vector2 m_direction, m_position;
int m_velocity;

int m_currentWalk = 0;
int m_walkDelay = 15;
int m_walkTimer = 0;

void InitGame() {

	idle = LoadTexture("resources/player.png");
	walkA = LoadTexture("resources/walkA.png");
	walkB = LoadTexture("resources/walkB.png");
	m_texture = idle;
	
	m_direction = (Vector2){0,0};
	m_position = (Vector2){100,100};
	m_velocity = 4;
	
	printf("Game Initialized!\n");
}

void UpdateGame() {
    
	UpdatePlayer();
	
}

void DrawGame() {
    
	if(IsMouseButtonDown(0) || IsMouseButtonDown(1) ||IsMouseButtonDown(2))
	{
		DrawChristmasTree();
	}
		
	if (IsKeyDown(KEY_SPACE))
	{
		DrawTexture(m_texture,m_position.x,m_position.y,LIME);
	}
	else 
	{
		DrawTexture(m_texture,m_position.x,m_position.y,WHITE);
	}
	
}

void DrawChristmasTree()
{
    DrawCircle(410,120,110,RED);
    DrawRectangle(260,310,50,90,RED);
    DrawTriangle((Vector2){410,200},(Vector2){290,330},(Vector2){530,330}, GREEN);
    DrawTriangle((Vector2){410,330},(Vector2){280,475},(Vector2){540,475}, GREEN);
    DrawRectangle(500,450,60,80, RED);
    DrawRectangle(260,310,50,90,RED);
    DrawTriangle((Vector2){410,475},(Vector2){325,590},(Vector2){490,590},DARKBROWN);
    DrawCircle(410,120,110,(Color){253,240,0,255});
    DrawLineEx((Vector2){300,120},(Vector2){520,120},5,BLACK);

}


void CloseGame() {
    printf("Game Closed!\n");
}


void UpdatePlayer()
{
	m_direction.x = (int)(IsKeyDown(KEY_RIGHT)) - (int)(IsKeyDown(KEY_LEFT));
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