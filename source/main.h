#ifndef MAIN_H
#define MAIN_H
#include <NEMain.h>
#include <squirrel.h>

#define LEVEL_SIZE 1
#define LEVEL_RENDER_SIZE 4

#define MAX_PLANES 100
#define MAX_HITBOXES 120
#define PLAYER_HIGHT 64 * LEVEL_SIZE //space below the camera
#define PLAYER_HIGHT_TOP 2 * LEVEL_SIZE //space above the camera
#define PLAYER_WIDTH 15 * LEVEL_SIZE
#define PLAYER_JUMPFORCE 2

#define SINMULTIPLIER 32790

#define PORTAL_PROJECTILE_WIDTH 64 * LEVEL_SIZE

#define CONSOLE_BACKGROUND_LAYER 2

// 2D point 
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
	Vector3 vertex[8];
	Vector3 vector[3];
	float sizeX;
	float sizeY;
	float sizeZ;
	Vector3 position;
	Vector3 rotation;
	Vector3* attachedPosition; // Position for dynamic hitboxes
	Vector3* attachedRotation; // Rotation for dynamic hitboxes
	bool isDynamic; //if the hitbox can't move
	bool isPlane; // it is only a Plane
	PLANE* attachedPlane; // The plane it belongs to
} hitbox;

typedef struct
{
	Vector3 position;
	Vector3 rotation;
} Cube;

typedef struct
{
	PLANE* plane;
	Vector2 portalPosition;
} PortaledPlane;

typedef struct
{
	bool type; //color
	bool onFloor; //if the portal is on the floor/cieling
	Vector3 position;
	Vector3 rotation;
	PortaledPlane portaledPlane;
} Portal;


typedef struct
{
	char* name;
	PLANE Plane[MAX_PLANES];
	Portal portal[2];
	int planeCount;
	hitbox allHitboxes[MAX_HITBOXES];
	int currentHitbox;
	int dynamicHitbxes[10]; // Wich hitboxes are Dynamic
	int currentDynamicHitbox;
} Level;

typedef struct
{
	char* name; //Player Name
	Vector3 position; //Player Position (x,y,z)
	Vector3 rotation; //Player Rotaion (x,y,z)
	Vector3 lookVector; // vector in witch direction the player is looking
	bool isJumping;
	PHYSICS physics;
	hitbox hitbox;
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
extern bool isConsoleOpen;
extern Keyboard *keyboard;

// Call a Squirrel (ingame script language) function
int callSquirrel(HSQUIRRELVM vm, const char* function);

#endif