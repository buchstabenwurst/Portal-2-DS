#ifndef PHYSICS_H
#define PHYSICS_H

//friction value 0.1 to 1 is least to most
#define FRICTION 0.85
#define AIR_FRICTION 0.996
//gravity in coordinate-units/frame²
#define GRAVITY 0.04

void shootPortal(bool Portal);
void doPhysics(void);

#endif