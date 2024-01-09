#include <NEMain.h>
#include <math.h>
#include "physics.h"
#include "main.h"
#include "load.h"

float dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

//https://gamedev.stackexchange.com/questions/25397/obb-vs-obb-collision-detection
Vector2 SATtest(Vector3 vector, hitbox box)
{
    Vector2 along;
    along.x = 100000, along.y = -100000;
    for (int i = 0; i < 8; i++)
    {
        // just dot it to get the min/max along this axis.
        float dotVal = dot(vector, box.vertex[i]);
        if (dotVal < along.x)  along.x = dotVal;
        if (dotVal > along.y)  along.y = dotVal;
    }
    //printf("\x1b[10;2H%f,%f",along.x,along.y);
    return along;
}


inline bool isBetweenOrdered(float val, float lowerBound, float upperBound) {
    return lowerBound <= val && val <= upperBound;
}

bool overlaps(float min1, float max1, float min2, float max2)
{
    return isBetweenOrdered(min2, min1, max1) || isBetweenOrdered(min1, min2, max2);
}

Vector3 getVectorNormalized(hitbox box) {
    //get direction vector
    box.vector[0].x = box.vertex[0].x - box.vertex[2].x;
    box.vector[0].y = box.vertex[0].y - box.vertex[2].y;
    box.vector[0].z = box.vertex[0].z - box.vertex[2].z; //not tested yet

    //Normalize
    float len_v = fixedToFloat(sqrtf32(floatToFixed(box.vector[0].x * box.vector[0].x + box.vector[0].y * box.vector[0].y + box.vector[0].z * box.vector[0].z, 12)), 12);
    box.vector[0].x /= len_v;
    box.vector[0].y /= len_v;
    box.vector[0].z /= len_v;

    printf("\x1b[6;2H%f", len_v);
    return box.vector[0];
}
                                                 
// Shape1 and Shape2 must be CONVEX HULLS and not too small
bool intersects(hitbox box1, hitbox box2)
{
    box1.vector[0] = getVectorNormalized(box1);
    box2.vector[0] = getVectorNormalized(box2);

    box1.vector[1].x = box1.vector[0].y;
    box1.vector[1].y = -box1.vector[0].x;
    box1.vector[1].z = -box1.vector[0].z; 

    box1.vector[2].x = -box1.vector[0].z;
    box1.vector[2].y = -box1.vector[0].y;
    box1.vector[2].z = box1.vector[0].x;


    box2.vector[1].x = box2.vector[0].y;
    box2.vector[1].y = -box2.vector[0].x;
    box2.vector[1].z = box2.vector[0].z;

    box2.vector[2].x = -box2.vector[0].z;
    box2.vector[2].y = -box2.vector[0].y;
    box2.vector[2].z = box2.vector[0].x;
    //printf("\x1b[7;2H%f,%f,%f", box1.vector[0].x, box1.vector[0].y, box1.vector[0].z);
    //printf("\x1b[8;2H%f,%f,%f", box1.vector[1].x, box1.vector[1].y, box1.vector[1].z);

    
    // Get the normals for one of the shapes,
    for (int i = 0; i < 3 ; i++)
    {
        //float shape1Min, shape1Max, shape2Min, shape2Max;
        Vector2 shape1, shape2;
        shape1 = SATtest(box1.vector[i], box1);
        shape2 = SATtest(box1.vector[i], box2);
        if (!overlaps(shape1.x, shape1.y, shape2.x, shape2.y))
        {
            //printf("\x1b[15;2Hlol");
            return 0; // NO INTERSECTION
        }
    }

    // TEST SHAPE2.normals as well
    for (int i = 0; i < 2; i++)
    {
        // otherwise, go on with the next test
        Vector2 shape1, shape2;
        shape1 = SATtest(box2.vector[i], box1);
        shape2 = SATtest(box2.vector[i], box2);
        if (!overlaps(shape1.x, shape1.y, shape2.x, shape2.y))
        {
            //printf("\x1b[15;7Hlmao");
            return 0; // NO INTERSECTION
        }
    }

    // if overlap occurred in ALL AXES, then they do intersect
    return 1;
}

void addHitbox(hitboxCollision Collision, Vector3 initialPosition, bool isDynamic) {
    for(int i = 0; i < 8; i++){
        level.allHitboxes[level.currentHitbox].vertex[i] = Collision.vertex[i];
    }
    level.allHitboxes[level.currentHitbox].isDynamic = isDynamic;
}//todo

void doCollisions(void) {
    for (int i = 0; i < level.currentHitbox; i++) {
        //if is dynamic
        if (level.allHitboxes[i].isDynamic) {
            for (int j = 0; j < level.currentHitbox; j++) {
                if (i != j)
                    if (intersects(level.allHitboxes[i], level.allHitboxes[j])) {
                        printf("amogus");
                    }

            }

        }
    }
}

PLAYER playerPhysics(PLAYER player){
    bool alreadyCollidedX = false;
    bool alreadyCollidedY = false;
    bool alreadyCollidedZ = false;

        //if walking through portal
        for(int j = 0; j < 2; j++){
            if (level.portal[j].onFloor){
                if (player.position.y + PLAYER_WIDTH * 1.6 > level.portal[j].position.y && player.position.y - PLAYER_WIDTH * 1.6 < level.portal[j].position.y && // if player is close enough to the plane
                    player.position.x - PLAYER_WIDTH * 1.6 < level.portal[j].position.x && player.position.x + PLAYER_WIDTH * 1.6 > level.portal[j].position.x && // if player is within the plane
                    player.position.z - 0.5 < level.portal[j].position.z && player.position.z + 0.5 > level.portal[j].position.z)
                {
                    alreadyCollidedZ = true;
                    player.physics.isGrounded = false;
                }
                
            }
            else{
                if (player.position.y + PLAYER_WIDTH * 1.6 > level.portal[j].position.y && player.position.y - PLAYER_WIDTH * 1.6 < level.portal[j].position.y && // if player is close enough to the plane
                    player.position.x - PLAYER_WIDTH * 1.6 < level.portal[j].position.x && player.position.x + PLAYER_WIDTH * 1.6 > level.portal[j].position.x && // if player is within the plane
                    player.position.z - PLAYER_HIGHT_TOP < level.portal[j].position.z && player.position.z + PLAYER_HIGHT > level.portal[j].position.z)
                {
                    alreadyCollidedY = true;
                    alreadyCollidedX = true;
                }
            }
        }

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
                player.position.x + PLAYER_WIDTH > (level.Plane[i].vertex3.x) && player.position.x - PLAYER_WIDTH < (level.Plane[i].vertex2.x) &&
                player.position.z > (level.Plane[i].vertex1.z - PLAYER_HIGHT_TOP) && player.position.z < (level.Plane[i].vertex1.z + PLAYER_HIGHT)) // if player is enough above the plane
                {
                    player.physics.velocity.z = 0;
                    player.position.z = level.Plane[i].vertex1.z - PLAYER_HIGHT_TOP - 0.001;
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

bool portalPlaneHitDetection(Vector3 subject, float width, bool portal){
    for (int i = 0; i < level.planeCount; i++){
        if (level.Plane[i].vertex1.z == level.Plane[i].vertex3.z){
            //floor
            if (subject.y + width > (level.Plane[i].vertex1.y) && subject.y - width < (level.Plane[i].vertex2.y) && // if localPlayer is within the plane
            subject.x - width < (level.Plane[i].vertex3.x) && subject.x + width > (level.Plane[i].vertex2.x) &&
            subject.z + width > (level.Plane[i].vertex1.z) && subject.z - width < (level.Plane[i].vertex1.z)) // if localPlayer is enough above the plane
            {
                level.portal[portal].onFloor = true;
                level.portal[portal].rotation.y = 512 * localPlayer.rotation.y + 128;
                level.portal[portal].rotation.z = -128;

                return true;
            }
            //cieling
            if (subject.y + width > (level.Plane[i].vertex1.y) && subject.y - width < (level.Plane[i].vertex2.y) && // if localPlayer is within the plane
            subject.x + width > (level.Plane[i].vertex3.x) && subject.x - width < (level.Plane[i].vertex2.x) &&
            subject.z + width > (level.Plane[i].vertex1.z) && subject.z - width < (level.Plane[i].vertex1.z)) // if localPlayer is enough above the plane
            {
                level.portal[portal].onFloor = true;
                level.portal[portal].rotation.y = 512 * localPlayer.rotation.y + 128;
                level.portal[portal].rotation.z = 128;
                return true;
            }
        }
        //if y aligned wall
        if (level.Plane[i].vertex1.y == level.Plane[i].vertex2.y && level.Plane[i].vertex1.y == level.Plane[i].vertex3.y){ //if it even is a y aligned wall
            if (subject.y + width > (level.Plane[i].vertex1.y) && subject.y - width < (level.Plane[i].vertex1.y)){ // if localPlayer is close enough to the plane
                if (subject.x - width * 0.9 < (level.Plane[i].vertex1.x) && subject.x + width * 0.9 > (level.Plane[i].vertex2.x) && // if localPlayer is within the plane
                subject.z < (level.Plane[i].vertex3.z + width - 0.01) && subject.z > (level.Plane[i].vertex2.z - width))
                {
                    level.portal[portal].rotation.y = -128;
                    return true;
                }
                //if y aligned flipped wall
                if (subject.x + width * 0.9 > (level.Plane[i].vertex1.x) && subject.x - width * 0.9 < (level.Plane[i].vertex2.x) && // if localPlayer is within the plane
                subject.z < (level.Plane[i].vertex3.z + width - 0.01) && subject.z > (level.Plane[i].vertex2.z - width))
                {
                    level.portal[portal].rotation.y = 128;
                    return true;
                }
            }
        }
        //if x aligned wall
        if (level.Plane[i].vertex1.x == level.Plane[i].vertex2.x && level.Plane[i].vertex1.x == level.Plane[i].vertex3.x){
            if (subject.x + width > (level.Plane[i].vertex1.x) && subject.x - width < (level.Plane[i].vertex1.x)){ // if localPlayer is close enough to the plane
                if (subject.y - width * 0.9 < (level.Plane[i].vertex1.y) && subject.y + width * 0.9 > (level.Plane[i].vertex2.y) && // if localPlayer is within the plane
                subject.z < (level.Plane[i].vertex3.z + width - 0.01) && subject.z > (level.Plane[i].vertex2.z - width))
                {
                    level.portal[portal].rotation.y = 0;
                    return true;
                }
                //if x aligned flipped wall
                if (subject.y + width * 0.9 > (level.Plane[i].vertex1.y) && subject.y - width * 0.9 < (level.Plane[i].vertex2.y) && // if localPlayer is within the plane
                subject.z < (level.Plane[i].vertex3.z + width - 0.01) && subject.z > (level.Plane[i].vertex2.z - width))
                {
                    level.portal[portal].rotation.y = 0;
                    return true;
                }
            }
        }
    }
    return false;
}

void shootPortal(bool portal){
    bool hit = false;
    int interations = 0;
    Vector3 pos;
                //start behind the camera
    pos.x = localPlayer.position.x - 0.5 * (fixedToFloat(0.0001 * sinLerp(localPlayer.rotation.y * SINMULTIPLIER), 2) * (localPlayer.rotation.z * localPlayer.rotation.z - 1));
    pos.y = localPlayer.position.y - 0.5 * (fixedToFloat(0.0001 * cosLerp(localPlayer.rotation.y * SINMULTIPLIER), 2) * (localPlayer.rotation.z * localPlayer.rotation.z - 1));
    pos.z = localPlayer.position.z - 0.5 * (fixedToFloat(50 * sinLerp(localPlayer.rotation.z * 9000 ) +1, 21));
    while(!hit){
            hit = portalPlaneHitDetection(pos, PORTAL_PROJECTILE_WIDTH * 20, portal);

            pos.x += 0.5 * (fixedToFloat(0.0001 * sinLerp(localPlayer.rotation.y * SINMULTIPLIER), 2) * (localPlayer.rotation.z * localPlayer.rotation.z - 1));
            pos.z += 0.5 * (fixedToFloat(50 * sinLerp(localPlayer.rotation.z * 9000 ) +1, 21));
            pos.y += 0.5 * (fixedToFloat(0.0001 * cosLerp(localPlayer.rotation.y * SINMULTIPLIER), 2) * (localPlayer.rotation.z * localPlayer.rotation.z - 1));
        interations++;
        if(interations > 100)
            break;
    }
    if(hit){
        hit = false;
        while(!hit){
                hit = portalPlaneHitDetection(pos, PORTAL_PROJECTILE_WIDTH * 10, portal);

                pos.x += 0.1 * (fixedToFloat(0.0001 * sinLerp(localPlayer.rotation.y * SINMULTIPLIER), 2) * (localPlayer.rotation.z * localPlayer.rotation.z - 1));
                pos.z += 0.1 * (fixedToFloat(50 * sinLerp(localPlayer.rotation.z * 9000 ) +1, 21));
                pos.y += 0.1 * (fixedToFloat(0.0001 * cosLerp(localPlayer.rotation.y * SINMULTIPLIER), 2) * (localPlayer.rotation.z * localPlayer.rotation.z - 1));
            interations++;
            if(interations > 200)
                break;
        }
    }
    if(hit){
        hit = false;
        while(!hit){
                hit = portalPlaneHitDetection(pos, PORTAL_PROJECTILE_WIDTH * 5, portal);
    
                pos.x += 0.05 * (fixedToFloat(0.0001 * sinLerp(localPlayer.rotation.y * SINMULTIPLIER), 2) * (localPlayer.rotation.z * localPlayer.rotation.z - 1));
                pos.z += 0.05 * (fixedToFloat(50 * sinLerp(localPlayer.rotation.z * 9000 ) +1, 21));
                pos.y += 0.05 * (fixedToFloat(0.0001 * cosLerp(localPlayer.rotation.y * SINMULTIPLIER), 2) * (localPlayer.rotation.z * localPlayer.rotation.z - 1));
            interations++;
            if(interations > 400)
                break;
        }
    }

    level.portal[portal].onFloor = false;
    level.portal[portal].rotation.x = 0;
    level.portal[portal].rotation.y = 0;
    level.portal[portal].rotation.z = 0;

    if(hit){
        hit = false;
        while(!hit){
                hit = portalPlaneHitDetection(pos, PORTAL_PROJECTILE_WIDTH, portal);

                pos.x += PORTAL_PROJECTILE_WIDTH * (fixedToFloat(0.0001 * sinLerp(localPlayer.rotation.y * SINMULTIPLIER), 2) * (localPlayer.rotation.z * localPlayer.rotation.z - 1));
                pos.z += PORTAL_PROJECTILE_WIDTH * (fixedToFloat(50 * sinLerp(localPlayer.rotation.z * 9000 ) +1, 21));
                pos.y += PORTAL_PROJECTILE_WIDTH * (fixedToFloat(0.0001 * cosLerp(localPlayer.rotation.y * SINMULTIPLIER), 2) * (localPlayer.rotation.z * localPlayer.rotation.z - 1));
            interations++;
            if(interations > 500)
                break;
        }
    }
    if(hit)
        level.portal[portal].position = pos;
}

void doPhysics (void){
    localPlayer = playerPhysics(localPlayer);
    doCollisions();
}