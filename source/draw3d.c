#include <NEMain.h>
#include <stdio.h>
#include <math.h>
#include <nds/arm9/trig_lut.h>
#include "main.h"
#include "draw3d.h"
#include "load.h"


NE_Camera* Camara;

//move the Camera on the Global axis
void CameraMoveGlobal(NE_Camera *cam, PLAYER player) {
    float tmpTo[3];
    tmpTo[0] = player.position.x + (fixedToFloat(0.0001 * sinLerp(player.rotation.y * 32790), 2) * (player.rotation.z * player.rotation.z - 1));
    tmpTo[1] = player.position.z + (fixedToFloat(50 * sinLerp(player.rotation.z * 9000 ) +1, 21));
    tmpTo[2] = player.position.y + (fixedToFloat(0.0001 * cosLerp(player.rotation.y * 32790), 2) * (player.rotation.z * player.rotation.z - 1));

    NE_AssertPointer(cam, "NULL pointer");

    cam->matrix_is_updated = false;

    cam->from[0] = floattof32(player.position.x);
    cam->from[1] = floattof32(player.position.z);
    cam->from[2] = floattof32(player.position.y);

    cam->to[0] = floattof32(tmpTo[0]);
    cam->to[1] = floattof32(tmpTo[1]); //up and down
    cam->to[2] = floattof32(tmpTo[2]); //left and right

    //print position and rotation
    if (debugText) {
        printf("\x1b[3;1HPos: x:%.2f y:%.2f z:%.2f\x1b[4;1HRot: x:%.2f y:%.2f z:%.2f\n0:%f 1:%f 2:%f", 
        player.position.x, player.position.y, player.position.z, player.rotation.x, player.rotation.y, player.rotation.z, tmpTo[0], tmpTo[1], tmpTo[2]);
    }
    if (debugVision) {
        NE_ModelRotate(debug_vision_model, 1, 2, 3);
        NE_ModelSetCoord(debug_vision_model, tmpTo[0], tmpTo[1], tmpTo[2]);
        NE_ModelDraw(debug_vision_model);
    }
}

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

        NE_PolyTexCoord(level.Plane[i].y0, level.Plane[i].x1);
        NE_PolyVertex(level.Plane[i].vertex1.x, level.Plane[i].vertex1.z, level.Plane[i].vertex1.y);

        NE_PolyTexCoord(level.Plane[i].y1, level.Plane[i].x1);
        NE_PolyVertex(level.Plane[i].vertex2.x, level.Plane[i].vertex2.z, level.Plane[i].vertex2.y);

        NE_PolyTexCoord(level.Plane[i].y1, level.Plane[i].x0);
        NE_PolyVertex(level.Plane[i].vertex3.x, level.Plane[i].vertex3.z, level.Plane[i].vertex3.y);

        NE_PolyTexCoord(level.Plane[i].y0, level.Plane[i].x0);
        NE_PolyVertex(level.Plane[i].vertex4.x, level.Plane[i].vertex4.z, level.Plane[i].vertex4.y);

        NE_PolyEnd();
    }
}

void Draw3DScene(void)
{
    NE_CameraUse(Camara);

    CameraMoveGlobal(Camara, localPlayer);
    RenderPlanes(level);
}