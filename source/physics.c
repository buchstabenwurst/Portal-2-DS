#include <NEMain.h>
#include "physics.h"
#include "main.h"

PLAYER playerPhysics(PLAYER player){
    bool alreadyCollidedX = false;
    bool alreadyCollidedY = false;
    bool alreadyCollidedZ = false;

    for (int i = 0; i < level.planeCount; i++){
        if (!alreadyCollidedZ){ //if not already collided this frame
            if (level.Plane[i].vertex1.z == level.Plane[i].vertex3.z){
                //floor
                if (player.position.y + PLAYER_WIDTH > (level.Plane[i].vertex1.y) && player.position.y - PLAYER_WIDTH < (level.Plane[i].vertex2.y) && // if player is within the plane
                player.position.x - PLAYER_WIDTH < (level.Plane[i].vertex3.x) && player.position.x + PLAYER_WIDTH > (level.Plane[i].vertex2.x) &&
                player.position.z > (level.Plane[i].vertex1.z - PLAYER_HIGHT_TOP) && player.position.z < (level.Plane[i].vertex1.z + PLAYER_HIGHT)) // if player is enough above the plane
                {
                    player.physics.isGrounded = true;
                    player.position.z = level.Plane[i].vertex1.z + PLAYER_HIGHT - 0.001;
                    alreadyCollidedZ = true;
                }
                else {
                    player.physics.isGrounded = false;
                }
                //cieling
                if (player.position.y + PLAYER_WIDTH > (level.Plane[i].vertex1.y) && player.position.y - PLAYER_WIDTH < (level.Plane[i].vertex2.y) && // if player is within the plane
                player.position.x < (level.Plane[i].vertex1.x) && player.position.x > (level.Plane[i].vertex2.x) &&
                player.position.z > (level.Plane[i].vertex3.z - PLAYER_HIGHT_TOP) && player.position.z < (level.Plane[i].vertex1.z + PLAYER_HIGHT)) // if player is close enough above the plane
                {
                    player.physics.velocity.z = 0;
                    player.position.z = level.Plane[i].vertex1.z - PLAYER_HIGHT - 0.001;
                }
            }
        }
        if (!alreadyCollidedY){ //if not already collided this frame
            //if y aligned wall
            if (level.Plane[i].vertex1.y == level.Plane[i].vertex2.y && level.Plane[i].vertex1.y == level.Plane[i].vertex3.y){ //if it even is a y aligned wall
                if (player.position.y + PLAYER_WIDTH > (level.Plane[i].vertex1.y) && player.position.y - PLAYER_WIDTH < (level.Plane[i].vertex1.y)){ // if player is close enough to the plane
                    if (player.position.x - PLAYER_WIDTH * 0.9 < (level.Plane[i].vertex1.x) && player.position.x + PLAYER_WIDTH * 0.9 > (level.Plane[i].vertex2.x) && // if player is within the plane
                    player.position.z < (level.Plane[i].vertex3.z + PLAYER_HIGHT - 0.01) && player.position.z > (level.Plane[i].vertex2.z - PLAYER_HIGHT_TOP))
                    {
                        player.physics.velocity.y = 0;
                        player.position.y = level.Plane[i].vertex1.y - PLAYER_WIDTH - 0.000001;
                        alreadyCollidedY = true;
                    }
                    //if y aligned flipped wall
                    if (player.position.x + PLAYER_WIDTH * 0.9 > (level.Plane[i].vertex1.x) && player.position.x - PLAYER_WIDTH * 0.9 < (level.Plane[i].vertex2.x) && // if player is within the plane
                    player.position.z < (level.Plane[i].vertex3.z + PLAYER_HIGHT - 0.01) && player.position.z > (level.Plane[i].vertex2.z - PLAYER_HIGHT_TOP))
                    {
                        player.physics.velocity.y = 0;
                        player.position.y = level.Plane[i].vertex1.y + PLAYER_WIDTH + 0.000001;
                        alreadyCollidedY = true;
                    }
                }
            }
        }
        if (!alreadyCollidedX){ //if not already collided this frame
            //if x aligned wall
            if (level.Plane[i].vertex1.x == level.Plane[i].vertex2.x && level.Plane[i].vertex1.x == level.Plane[i].vertex3.x){
                if (player.position.x + PLAYER_WIDTH > (level.Plane[i].vertex1.x) && player.position.x - PLAYER_WIDTH < (level.Plane[i].vertex1.x)){ // if player is close enough to the plane
                    if (player.position.y - PLAYER_WIDTH * 0.9 < (level.Plane[i].vertex1.y) && player.position.y + PLAYER_WIDTH * 0.9 > (level.Plane[i].vertex2.y) && // if player is within the plane
                    player.position.z < (level.Plane[i].vertex3.z + PLAYER_HIGHT - 0.01) && player.position.z > (level.Plane[i].vertex2.z - PLAYER_HIGHT_TOP))
                    {
                        player.physics.velocity.x = 0;
                        player.position.x = level.Plane[i].vertex1.x + PLAYER_WIDTH + 0.000001;
                        alreadyCollidedX = true;
                    }
                    //if x aligned flipped wall
                    if (player.position.y + PLAYER_WIDTH * 0.9 > (level.Plane[i].vertex1.y) && player.position.y - PLAYER_WIDTH * 0.9 < (level.Plane[i].vertex2.y) && // if player is within the plane
                    player.position.z < (level.Plane[i].vertex3.z + PLAYER_HIGHT - 0.01) && player.position.z > (level.Plane[i].vertex2.z - PLAYER_HIGHT_TOP))
                    {
                        player.physics.velocity.x = 0;
                        player.position.x = level.Plane[i].vertex1.x - PLAYER_WIDTH - 0.000001;
                        alreadyCollidedX = true;
                    }
                }
            }
        }
    }

    if (player.physics.isGrounded){
        if (player.isJumping){
            player.isJumping = false;
        } 
        else {
            player.physics.velocity.z = 0;
        }
    }
    else {
        //add gravity
        player.physics.velocity.z -= GRAVITY;
    }

    //add velocity influence
    player.position.x += player.physics.velocity.x;
    player.position.y += player.physics.velocity.y;
    player.position.z += player.physics.velocity.z;
    //reduce velocity
    player.physics.velocity.x *= FRICTION;
    player.physics.velocity.y *= FRICTION;
    player.physics.velocity.z *= AIR_FRICTION;

        return player;
}

void doPhysics (void){
    localPlayer = playerPhysics(localPlayer);
}