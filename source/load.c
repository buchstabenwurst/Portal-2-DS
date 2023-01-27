
#include <NEMain.h>
#include "main.h"

#include "plane_bin.h"

//TODO Bessere physics: 
//Oriented bounding box [ ]
//(Convex hull [ ])
//(Bounding Sphere [ ])


//i split blocks to sides for using the nodraw texture
// @param x1,y1,z1 vertex 1 position
// @param x2,y2,z2 vertex 2 position
// @param x3,y3,z3 vertex 3 position

void CreateBlockSide(s16 x1, s16 y1, s16 z1, s16 x2, s16 y2, s16 z2, s16 x3, s16 y3, s16 z3, int Zone, int id) {
    NE_CameraUse(Camara);

    block->Model = NE_ModelCreate(NE_Static);
    block->Physics = NE_PhysicsCreate(NE_BoundingBox);

    NE_ModelLoadStaticMesh(block->Model, (u32*)plane_bin);

    NE_PhysicsSetModel(block->Physics, // Physics object
        (void*)block->Model); // Model assigned to it

    NE_PhysicsEnable(block->Physics, false);
    NE_PolyFormat(31, 1, NE_LIGHT_0, NE_CULL_NONE, 0);
    NE_ModelDraw(block->Model);
}