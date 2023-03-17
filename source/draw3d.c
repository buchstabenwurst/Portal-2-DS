#include <NEMain.h>
#include "main.h"


NE_Camera* Camara;


//Render all Planes in the level
void RenderPlanes(Level level) {
    int i;
    for (i = 0; i < MAX_PLANES; i++)
    {
        // Render a plane
        NE_PolyFormat(31, 1, NE_LIGHT_0, NE_CULL_BACK, 0);

        NE_MaterialUse(level.Plane[i].material);

        NE_PolyBegin(GL_QUAD);
        //NE_PolyNormal(level.Plane[i].nx / 100, level.Plane[i].nz / 100, level.Plane[i].ny / 100);

        NE_PolyTexCoord(level.Plane[i].y0, level.Plane[i].x0);
        NE_PolyVertex(level.Plane[i].vertex4.y / 1000, level.Plane[i].vertex4.z / 1000, level.Plane[i].vertex4.x / 1000);

        NE_PolyTexCoord(level.Plane[i].y1, level.Plane[i].x0);
        NE_PolyVertex(level.Plane[i].vertex3.y / 1000, level.Plane[i].vertex3.z / 1000, level.Plane[i].vertex3.x / 1000);

        NE_PolyTexCoord(level.Plane[i].y1, level.Plane[i].x1);
        NE_PolyVertex(level.Plane[i].vertex2.y / 1000, level.Plane[i].vertex2.z / 1000, level.Plane[i].vertex2.x / 1000);

        NE_PolyTexCoord(level.Plane[i].y0, level.Plane[i].x1);
        NE_PolyVertex(level.Plane[i].vertex1.y / 1000, level.Plane[i].vertex1.z / 1000, level.Plane[i].vertex1.x / 1000);

        NE_PolyEnd();
    }
}

void Draw3DScene(void)
{
    NE_CameraUse(Camara);

    //The first 3 boxes will be affected by one light and 3 last boxes by
    //another one
   //NE_PolyFormat(31, 0, NE_LIGHT_0,NE_CULL_BACK, 0);
   //for (int i = 0; i < 3; i++)
   //    NE_ModelDraw(Model[i]);


    RenderPlanes(level);



   //void RenderPlanesManual(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, double u, double v, NE_Material * Material, int Zone, int id);
   //CreateBlockSideManual(-256, -320, 64, 128, -320, 64, 128, -320, 320, 0.25, 0.25, white_wall_tile003a, 0, 11); //wall
   //CreateBlockSideManual(320, -128, 64, 320, 256, 64, 320, 256, 320, 0.25, 0.25, white_wall_tile003a, 0, 50); //wall
   //CreateBlockSideManual(128, -320, 64, 320, -320, 64, 320, -320, 320, 0.25, 0.25, black_wall_metal_002c, 0, 74); //wall
   //CreateBlockSideManual(320, -320, 64, 320, -128, 64, 320, -128, 320, 0.25, 0.25, black_wall_metal_002a, 0, 86); //wall
   //CreateBlockSideManual(320, 256, 64, -256, 256, 64, -256, 256, 320, 0.25, 0.25, white_wall_tile003a, 0, 104); //wall
   //CreateBlockSideManual(-256, 256, 64, -256, -320, 64, -256, -320, 320, 0.25, 0.25, white_wall_tile003a, 0, 110); //wall
   //CreateBlockSideManual(128, -320, 64, 128, -128, 64, 320, -128, 64, 0.25, 0.25, black_floor_metal_001c, 0, 13); //floor
   //CreateBlockSideManual(-256, -320, 64, -256, -128, 64, 128, -128, 64, 0.25, 0.25, white_floor_tile002a, 0, 42); //floor
   //CreateBlockSideManual(-256, -128, 64, -256, 256, 64, 320, 256, 64, 0.25, 0.25, white_floor_tile002a, 0, 66); //floor
   //CreateBlockSideManual(320, -128, 320, 128, -128, 320, 128, -320, 320, 0.25, 0.25, black_wall_metal_002b, 0, 138); //ceiling
   //CreateBlockSideManual(128, 256, 320, -256, 256, 320, -256, -320, 320, 0.25, 0.25, white_ceiling_tile002a, 0, 144); //ceiling
   //CreateBlockSideManual(320, 256, 320, 128, 256, 320, 128, -128, 320, 0.25, 0.25, white_ceiling_tile002a, 0, 150); //ceiling
}