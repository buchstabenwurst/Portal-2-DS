#include <NEMain.h>
#include <stdio.h>
#include <math.h>
#include <nds/arm9/trig_lut.h>
#include "main.h"
#include "draw3d.h"
#include "load.h"
#include "physics.h"


NE_Camera* Camara;

//move the Camera on the Global axis
void CameraMoveGlobal(NE_Camera *cam, PLAYER player) {
    float tmpTo[3];
    tmpTo[0] = player.position.x / (1 << 12 - LEVEL_RENDER_SIZE) + fixedToFloat(sinLerp(floatToFixed(player.rotation.y / 45, 12)) / 3 * fixedToFloat(cosLerp(floatToFixed(player.rotation.z / 45, 12)), 12), 12);
    tmpTo[1] = player.position.z / (1 << 12 - LEVEL_RENDER_SIZE) + fixedToFloat(sinLerp(floatToFixed(player.rotation.z / 45, 12)), 21) * 180;
    tmpTo[2] = player.position.y / (1 << 12 - LEVEL_RENDER_SIZE) + fixedToFloat(cosLerp(floatToFixed(player.rotation.y / 45, 12)) / 3 * fixedToFloat(cosLerp(floatToFixed(player.rotation.z / 45, 12)), 12), 12);

    NE_AssertPointer(cam, "NULL pointer");

    cam->matrix_is_updated = false;

    cam->from[0] = floatToFixed(player.position.x, LEVEL_RENDER_SIZE);
    cam->from[1] = floatToFixed(player.position.z, LEVEL_RENDER_SIZE);
    cam->from[2] = floatToFixed(player.position.y, LEVEL_RENDER_SIZE);

    cam->to[0] = floattof32(tmpTo[0]);
    cam->to[1] = floattof32(tmpTo[1]); //up and down
    cam->to[2] = floattof32(tmpTo[2]); //left and right

    localPlayer.lookVector.x = tmpTo[0] - player.position.x / (1 << 12 - LEVEL_RENDER_SIZE);
    localPlayer.lookVector.z = tmpTo[1] - player.position.z / (1 << 12 - LEVEL_RENDER_SIZE);
    localPlayer.lookVector.y = tmpTo[2] - player.position.y / (1 << 12 - LEVEL_RENDER_SIZE);
    
    localPlayer.lookVector = Normalize(localPlayer.lookVector);

    //portal gun
    NE_ModelSetRot(w_portalgun_model, 0,
                                        player.rotation.y / DERGEESTO511,
                                        0);
    NE_ModelSetCoord(w_portalgun_model, localPlayer.position.x / (1 << 12 - LEVEL_RENDER_SIZE) + fixedToFloat(sinLerp(floatToFixed(player.rotation.y / 45 - 50, 12)), 12) / 20,
                                        localPlayer.position.z / (1 << 12 - LEVEL_RENDER_SIZE) - 0.1 * LEVEL_SIZE,
                                        localPlayer.position.y / (1 << 12 - LEVEL_RENDER_SIZE) + fixedToFloat(cosLerp(floatToFixed(player.rotation.y / 45 - 50, 12)), 12) / 20);
    NE_ModelDraw(w_portalgun_model);

    //print position and rotation
    if (debugText) {
        printf("\x1b[3;1HPos: x:%.2f y:%.2f z:%.2f\x1b[4;1HRot: x:%.2f y:%.2f z:%.2f\n0:%f 1:%f 2:%f", 
        player.position.x, player.position.y, player.position.z, player.rotation.x, player.rotation.y, player.rotation.z, player.lookVector.x, player.lookVector.y, player.lookVector.z);
    }
    if (debugVision) {
        NE_ModelRotate(debug_vision_model, 1, 2, 3);
        NE_ModelSetCoord(debug_vision_model, tmpTo[0], tmpTo[1], tmpTo[2]);
        NE_ModelDraw(debug_vision_model);
    }
}

void renderPortals(void){
    for(int i = 0; i < 2; i++){
        NE_PolyFormat(31, 1, NE_LIGHT_0, NE_CULL_NONE, 0);

        NE_ModelSetCoord(i ? portal_blue_model : portal_orange_model, level.portal[i].position.x / (1 << 12 - LEVEL_RENDER_SIZE), level.portal[i].position.z / (1 << 12 - LEVEL_RENDER_SIZE), level.portal[i].position.y / (1 << 12 - LEVEL_RENDER_SIZE));
        NE_ModelSetRot(i ? portal_blue_model : portal_orange_model, 0, level.portal[i].rotation.y / DERGEESTO511, level.portal[i].rotation.z / DERGEESTO511);
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

    NE_PolyFormat(0, 1, NE_LIGHT_0, NE_CULL_NONE, 0);
    for (int i = 0; i < level.currentHitbox; i++) {
        NE_PolyBegin(GL_QUAD);
        // top and bottom
        for (int j = 0; j < 8; j++) {
            NE_PolyVertexI(floatToFixed(level.allHitboxes[i].vertex[j].x, LEVEL_RENDER_SIZE), floatToFixed(level.allHitboxes[i].vertex[j].z, LEVEL_RENDER_SIZE), floatToFixed(level.allHitboxes[i].vertex[j].y, LEVEL_RENDER_SIZE));
        }
        // sides
        for (int j = 0; j < 8; j += 6) {
            NE_PolyVertexI(floatToFixed(level.allHitboxes[i].vertex[j].x, LEVEL_RENDER_SIZE), floatToFixed(level.allHitboxes[i].vertex[j].z, LEVEL_RENDER_SIZE), floatToFixed(level.allHitboxes[i].vertex[j].y, LEVEL_RENDER_SIZE));
            NE_PolyVertexI(floatToFixed(level.allHitboxes[i].vertex[j + 1].x, LEVEL_RENDER_SIZE), floatToFixed(level.allHitboxes[i].vertex[j + 1].z, LEVEL_RENDER_SIZE), floatToFixed(level.allHitboxes[i].vertex[j + 1].y, LEVEL_RENDER_SIZE));
        }
        for (int j = 2; j < 6; j += 2) {
            NE_PolyVertexI(floatToFixed(level.allHitboxes[i].vertex[j].x, LEVEL_RENDER_SIZE), floatToFixed(level.allHitboxes[i].vertex[j].z, LEVEL_RENDER_SIZE), floatToFixed(level.allHitboxes[i].vertex[j].y, LEVEL_RENDER_SIZE));
            NE_PolyVertexI(floatToFixed(level.allHitboxes[i].vertex[j + 1].x, LEVEL_RENDER_SIZE), floatToFixed(level.allHitboxes[i].vertex[j + 1].z, LEVEL_RENDER_SIZE), floatToFixed(level.allHitboxes[i].vertex[j + 1].y, LEVEL_RENDER_SIZE));
        }
    }
}