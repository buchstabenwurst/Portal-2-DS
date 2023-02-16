#include <NEMain.h>

// 3D point unchanged
typedef struct
{
	float x;
	float y;
	float z;
} Vector3;

// 3D point unchanged
typedef struct
{
	int x;
	int y;
	int z;
} Vector3Int;

typedef struct // Physics values for raycasting unchanged
{
	int BoxXRangeA;
	int BoxXRangeB;
	int BoxYRangeA;
	int BoxYRangeB;
	int BoxZRangeA;
	int BoxZRangeB;
} CollisionBox;

typedef struct // Physics values for raycasting
{
	Vector3Int position;
	int ZoneCollision;
	CollisionBox BlockCollisionBox;
	NE_Model* Model;
	NE_Physics* Physics;
} Block;

extern NE_Material* white_wall_tile003a;
extern NE_Material* black_floor_metal_001c;
extern NE_Material* Debug_Material;
extern NE_Material* debugempty;
extern Block* block;
