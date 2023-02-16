
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
// @param id is id

void CreateBlockSide(s16 x1, s16 y1, s16 z1, s16 x2, s16 y2, s16 z2, s16 x3, s16 y3, s16 z3, double u, double v, NE_Material *Material, int Zone, int id) {
    int u0;
    int v0;
    int u1;
    int v1;
    int x4;
    int y4;
    int z4;
    if (z1 == z3) {  //look if side is floor and create vertex x4/y4/z4
        x4 = x3;
        y4 = y1;
        z4 = z2;
        u0 = 0;
        v0 = 0;
        u1 = (-y1 * 10 + y2 * 10) * u;
        v1 = (-x1 * 10 + x3 * 10) * v;

        if (x2 == x3) {
            x4 = x1;
            y4 = y3;
            z4 = z2;
            u0 = 0;
            v0 = 0;
            u1 = (-y1 * 10 + y2 * 10) * u;
            v1 = (-x1 * 10 + x3 * 10) * v;
        }
    }

    else if(y1 == y2){  //look if side is y aligned wall and create vertex x4/y4/z4
        x4 = x1;
        y4 = y3;
        z4 = z3;
        u0 = 0;
        v0 = (-z1 * 10 + z3 * 10) * v;
        u1 = (-x1 * 10 + x2 * 10) * u;
        v1 = 0;

        if (x1 == x2) {
            x4 = x1;
            y4 = y3;
            z4 = z3;
            u1 = (x1 * 10 + x2 * 10) * u;
            v1 = (z1 * 10 + z3 * 10) * v;
        }
    }
    else if(x2 == x3){  //else side is x aligned wall, create vertex x4
        x4 = x3;
        y4 = y1;
        z4 = z3;
        u0 = (-y1 * 10 + y2 * 10) * u;
        v0 = (-z1 * 10 + z3 * 10) * v;
        u1 = 0;
        v1 = 0;

        if (x1 == x2) {
            x4 = x3;
            y4 = y1;
            z4 = z3;
            u1 = 0;
            v1 = 0;
            u0 = (y1 * 10 + y2 * 10) * u;
            v0 = (z1 * 10 + z3 * 10) * v;
        }
    }


    //NE_MaterialUse(white_wall_tile003a);
    //NE_MaterialUse(black_floor_metal_001c);
    //NE_MaterialUse(Debug_Material);
    //NE_MaterialUse(debugempty);

    NE_MaterialUse(Material);
    NE_PolyBegin(GL_QUAD);

        NE_PolyTexCoord(v0, u0);
        NE_PolyVertex(x1 / 100, z1 / 100, y1 / 100);

        NE_PolyTexCoord(v0, u1);
        NE_PolyVertex(x2 / 100, z2 / 100, y2 / 100);

        NE_PolyTexCoord(v1, u1);
        NE_PolyVertex(x3 / 100, z3 / 100, y3 / 100);

        NE_PolyTexCoord(v1, u0);
        NE_PolyVertex(x4 / 100, z4 / 100, y4 / 100);

    NE_PolyEnd();

    //block->Model = NE_ModelCreate(NE_Static);
    //block->Physics = NE_PhysicsCreate(NE_BoundingBox);
    //NE_ModelLoadStaticMesh(block->Model, (u32*)plane_bin);
    //NE_PhysicsSetSize(block->Physics, x1 + x2, -y1 + y2, z2 - z3);    //collision anwenden

    //NE_PhysicsSetModel(block->Physics, // Physics object
    //    (void*)block->Model); // Model assigned to it

    //NE_PhysicsEnable(block->Physics, false);
}