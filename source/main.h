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

extern NE_Material* white_wall_tile003a, * white_ceiling_tile002a, * white_floor_tile002a, * black_floor_metal_001c, * black_wall_metal_002c, * Debug_Material, * debugempty;
extern NE_Palette* white_wall_tile003aPal, * white_ceiling_tile002aPal, * white_floor_tile002aPal, * black_floor_metal_001cPal, * black_wall_metal_002cPal;
extern Block* block;
