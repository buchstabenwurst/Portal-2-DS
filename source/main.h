#include <NEMain.h>

#define MAX_PLANES 100

// 3D point 
typedef struct
{
	float x;
	float y;
	float z;
} Vector3;

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
} Level;

extern int textureMode;
extern Level level;