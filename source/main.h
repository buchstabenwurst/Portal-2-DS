#ifndef MAIN_H
#define MAIN_H
#include <NEMain.h>

#define LEVEL_SIZE 0.001

#define MAX_PLANES 100
#define PLAYER_HIGHT 64 * LEVEL_SIZE //space below the camera
#define PLAYER_HIGHT_TOP 2 * LEVEL_SIZE //space above the camera
#define PLAYER_WIDTH 15 * LEVEL_SIZE
#define PLAYER_JUMPFORCE 0.0048

// 3D point 
typedef struct
{
	float x;
	float y;
	float z;
} Vector3;

typedef struct
{
    Vector3 velocity;
	bool isGrounded;
} PHYSICS;

// Plane values
typedef struct
{
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 vertex3;
	Vector3 vertex4;
	NE_Material* material;
	int x0;
	int x1;
	int y0;
	int y1;
	float nx;
	float ny;
	float nz;
	bool isDrawn;
	NE_Physics* Physics;
} PLANE;

typedef struct
{
	char* name;
	PLANE Plane[MAX_PLANES];
	int planeCount;
} Level;

typedef struct
{
	char* name; //Player Name
	Vector3 position; //Player Position (x,y,z)
	Vector3 rotation; //Player Rotaion (x,y,z)
	bool isJumping;
	PHYSICS physics;
} PLAYER;

extern int textureMode;
extern int sensitivityHorizontal;
extern int sensitivityVertical;
extern bool debugText;
extern bool debugVision;
extern bool drawCollision;
extern Level level;
extern PLAYER localPlayer;
#endif