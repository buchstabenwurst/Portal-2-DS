
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

void CreateBlockSide(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, double u, double v, NE_Material *Material, int Zone, int id) {
    int u0;
    int v0;
    int u1;
    int v1;
    float nx;
    float ny;
    float nz;
    float x4;
    float y4;
    float z4;

    if (z1 == z3) {  //look if side is floor or cieling and create vertex x4/y4/z4
        x4 = x3;
        y4 = y1;
        z4 = z2;

        u0 = 0;
        v0 = 0;
        u1 = 2 * (y2 - y1) * u * 4; //auflösung ergänzen
        v1 = 2 * (x3 - x2) * v * 4;

        if (x2 == x3) {
            x4 = x1;
            y4 = y3;
            z4 = z2;

            u0 = 0;
            v0 = 0;
            u1 = 2 * (x1 - x2) * u * 4;
            v1 = 2 * (y2 - y3) * v * 4;
        }
    }

    else if(y1 == y2){  //look if side is y aligned wall and create vertex x4/y4/z4
        x4 = x1;
        y4 = y3;
        z4 = z3;

        u0 = 0;
        v0 = 0;
        u1 = 2 * (x2 - x1) * u * 4;
        v1 = 2 * (z3 - z1) * v * 4;

        nx = x2 + 1;
        ny = y2;
        nz = z2 - z3;

    }
    else if(x2 == x3){  //else side is x aligned wall, create vertex x4
        x4 = x3;
        y4 = y1;
        z4 = z3;
        u0 = 0;
        v0 = 0;
        u1 = 2 * (y2 - y1) * u * 4;
        v1 = 2 * (z3 - z1) * v * 4;
    }

    //NE_MaterialUse(white_wall_tile003a);
    //NE_MaterialUse(black_floor_metal_001c);
    //NE_MaterialUse(Debug_Material);
    //NE_MaterialUse(debugempty);

    NE_PolyFormat(31, 1, NE_LIGHT_0 ,NE_CULL_BACK , 0);

    NE_MaterialUse(Material);

    NE_PolyBegin(GL_QUAD);
        //NE_PolyNormal(nx / 100, nz / 100, ny / 100);

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