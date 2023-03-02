#include <NEMain.h>


#include "cube_bin.h"
#include "debug_plane_bin.h"
#include "white_wall_tile003a_tex_bin.h"
#include "white_wall_tile003a_pal_bin.h"
#include "white_ceiling_tile002a_tex_bin.h"
#include "white_ceiling_tile002a_pal_bin.h"
#include "white_floor_tile002a_tex_bin.h"
#include "white_floor_tile002a_pal_bin.h"
#include "black_floor_metal_001c_tex_bin.h"
#include "black_floor_metal_001c_pal_bin.h"
#include "black_wall_metal_002c_tex_bin.h"
#include "black_wall_metal_002c_pal_bin.h"
#include "Debug_tex_bin.h"
#include "debugempty_tex_bin.h"

extern NE_Material* white_wall_tile003a, * white_ceiling_tile002a, * white_floor_tile002a, * black_floor_metal_001c, * black_wall_metal_002c, * Debug_Material, * debugempty;
extern NE_Palette* white_wall_tile003aPal, * white_ceiling_tile002aPal, * white_floor_tile002aPal, * black_floor_metal_001cPal, * black_wall_metal_002cPal;

void LoadTextures(int textureMode);

void CreateBlockSide(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, double u, double v, NE_Material *Material, int Zone, int id);

// 3D point 
typedef struct
{
	float x;
	float y;
	float z;
} Vector3;

typedef struct // Block values
{
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 vertex3;
	Vector3 vertex4;
	NE_Physics* Physics;
} Block;