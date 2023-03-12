#include <NEMain.h>

extern int textureMode;

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
	int id;
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 vertex3;
	Vector3 vertex4;
	NE_Material* material;
	bool isDrawn;
	NE_Physics* Physics;
} PLANE;