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
    tmpTo[0] = player.position.x / (1 << 12 - LEVEL_RENDER_SIZE) + (fixedToFloat(0.0001 * sinLerp(player.rotation.y * SINMULTIPLIER), 2) * (player.rotation.z * player.rotation.z - 1));
    tmpTo[1] = player.position.z / (1 << 12 - LEVEL_RENDER_SIZE) + (fixedToFloat(50 * sinLerp(player.rotation.z * 9000 ) +1, 21));
    tmpTo[2] = player.position.y / (1 << 12 - LEVEL_RENDER_SIZE) + (fixedToFloat(0.0001 * cosLerp(player.rotation.y * SINMULTIPLIER), 2) * (player.rotation.z * player.rotation.z - 1));

    NE_AssertPointer(cam, "NULL pointer");

    cam->matrix_is_updated = false;

    cam->from[0] = floatToFixed(player.position.x, LEVEL_RENDER_SIZE);
    cam->from[1] = floatToFixed(player.position.z, LEVEL_RENDER_SIZE);
    cam->from[2] = floatToFixed(player.position.y, LEVEL_RENDER_SIZE);

    cam->to[0] = floattof32(tmpTo[0]);
    cam->to[1] = floattof32(tmpTo[1]); //up and down
    cam->to[2] = floattof32(tmpTo[2]); //left and right

    //portal gun
    NE_ModelSetRot(w_portalgun_model, (localPlayer.rotation.z * 100) * fixedToFloat(0.001 * cosLerp(player.rotation.y * SINMULTIPLIER), 2), localPlayer.rotation.y * 512 + 248, (localPlayer.rotation.z * 100) * fixedToFloat(0.001 * sinLerp(player.rotation.y * SINMULTIPLIER), 2));
    NE_ModelSetCoord(w_portalgun_model, localPlayer.position.x / (1 << 12 - LEVEL_RENDER_SIZE) + fixedToFloat(0.00005 * cosLerp(player.rotation.y * SINMULTIPLIER), 2), localPlayer.position.z / (1 << 12 - LEVEL_RENDER_SIZE) - 0.1 * LEVEL_SIZE, localPlayer.position.y / (1 << 12 - LEVEL_RENDER_SIZE) - fixedToFloat(0.00005 * sinLerp(player.rotation.y * SINMULTIPLIER), 2));
    NE_ModelDraw(w_portalgun_model);

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

void renderPortals(void){
    for(int i = 0; i < 2; i++){

        NE_ModelSetCoord(i ? portal_blue_model : portal_orange_model, level.portal[i].position.x / (1 << 12 - LEVEL_RENDER_SIZE), level.portal[i].position.z / (1 << 12 - LEVEL_RENDER_SIZE), level.portal[i].position.y / (1 << 12 - LEVEL_RENDER_SIZE));
        NE_ModelSetRot(i ? portal_blue_model : portal_orange_model, 0, level.portal[i].rotation.y, level.portal[i].rotation.z);
        NE_ModelDraw(i ? portal_blue_model : portal_orange_model);
        
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
        NE_PolyVertexI(floatToFixed(level.Plane[i].vertex1.x, LEVEL_RENDER_SIZE), floatToFixed(level.Plane[i].vertex1.z, LEVEL_RENDER_SIZE), floatToFixed(level.Plane[i].vertex1.y, LEVEL_RENDER_SIZE));

        NE_PolyTexCoord(level.Plane[i].y1, level.Plane[i].x1);
        NE_PolyVertexI(floatToFixed(level.Plane[i].vertex2.x, LEVEL_RENDER_SIZE), floatToFixed(level.Plane[i].vertex2.z, LEVEL_RENDER_SIZE), floatToFixed(level.Plane[i].vertex2.y, LEVEL_RENDER_SIZE));

        NE_PolyTexCoord(level.Plane[i].y1, level.Plane[i].x0);
        NE_PolyVertexI(floatToFixed(level.Plane[i].vertex3.x, LEVEL_RENDER_SIZE), floatToFixed(level.Plane[i].vertex3.z, LEVEL_RENDER_SIZE), floatToFixed(level.Plane[i].vertex3.y, LEVEL_RENDER_SIZE));

        NE_PolyTexCoord(level.Plane[i].y0, level.Plane[i].x0);
        NE_PolyVertexI(floatToFixed(level.Plane[i].vertex4.x, LEVEL_RENDER_SIZE), floatToFixed(level.Plane[i].vertex4.z, LEVEL_RENDER_SIZE), floatToFixed(level.Plane[i].vertex4.y, LEVEL_RENDER_SIZE));

        NE_PolyEnd();
    }
}

void Draw3DScene(void)
{
    NE_CameraUse(Camara);

    CameraMoveGlobal(Camara, localPlayer);
    renderPortals();
    RenderPlanes(level);

    NE_PolyFormat(31, 1, NE_LIGHT_0, NE_CULL_NONE, 0);
    NE_PolyBegin(GL_QUAD);
    NE_PolyVertexI(floatToFixed(testBox.vertex[0].x, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[0].z, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[0].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox.vertex[1].x, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[1].z, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[1].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox.vertex[2].x, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[2].z, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[2].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox.vertex[3].x, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[3].z, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[3].y, LEVEL_RENDER_SIZE));
    NE_PolyBegin(GL_QUAD);                                                    
    NE_PolyVertexI(floatToFixed(testBox.vertex[4].x, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[4].z, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[4].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox.vertex[5].x, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[5].z, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[5].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox.vertex[6].x, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[6].z, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[6].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox.vertex[7].x, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[7].z, LEVEL_RENDER_SIZE), floatToFixed(testBox.vertex[7].y, LEVEL_RENDER_SIZE));

    NE_PolyFormat(31, 1, NE_LIGHT_0, NE_CULL_NONE, 0);
    NE_PolyBegin(GL_QUAD);
    NE_PolyVertexI(floatToFixed(testBox2.vertex[0].x, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[0].z, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[0].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox2.vertex[1].x, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[1].z, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[1].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox2.vertex[2].x, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[2].z, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[2].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox2.vertex[3].x, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[3].z, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[3].y, LEVEL_RENDER_SIZE));
    NE_PolyBegin(GL_QUAD);
    NE_PolyVertexI(floatToFixed(testBox2.vertex[4].x, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[4].z, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[4].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox2.vertex[5].x, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[5].z, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[5].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox2.vertex[6].x, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[6].z, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[6].y, LEVEL_RENDER_SIZE));
    NE_PolyVertexI(floatToFixed(testBox2.vertex[7].x, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[7].z, LEVEL_RENDER_SIZE), floatToFixed(testBox2.vertex[7].y, LEVEL_RENDER_SIZE));

}