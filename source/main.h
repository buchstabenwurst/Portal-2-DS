#ifndef MAIN_H
#define MAIN_H
#include <NEMain.h>

#define LEVEL_SIZE 1
#define LEVEL_RENDER_SIZE 4

#define MAX_PLANES 100
#define MAX_HITBOXES 100
#define PLAYER_HIGHT 64 * LEVEL_SIZE //space below the camera
#define PLAYER_HIGHT_TOP 2 * LEVEL_SIZE //space above the camera
#define PLAYER_WIDTH 15 * LEVEL_SIZE
#define PLAYER_JUMPFORCE 2

#define SINMULTIPLIER 32790

#define PORTAL_PROJECTILE_WIDTH 10 * LEVEL_SIZE

// 3D point 
typedef struct
{
	float x;
	float y;
} Vector2;

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

typedef struct
{
	Vector3 vertex[8];
	Vector3 vector[3];
	bool isDynamic; //if the hitbox can't move
} hitbox;

typedef struct
{
	Vector3 vertex[8];
} hitboxCollision;


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
	bool type; //color
	bool onFloor; //if the portal is on the floor/cieling
	Vector3 position;
	Vector3 rotation;
} Portal;


typedef struct
{
	char* name;
	PLANE Plane[MAX_PLANES];
	Portal portal[2];
	int planeCount;
	hitbox allHitboxes[MAX_HITBOXES];
	int currentHitbox;
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
extern hitbox testBox, testBox2;
#endif