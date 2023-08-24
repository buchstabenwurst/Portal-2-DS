#ifndef LOAD_H
#define LOAD_H

#include <NEMain.h>


extern NE_Model* debug_vision_model;

extern NE_Model *w_portalgun_model;

extern NE_Animation *w_portalgun_fire1_animation;

extern NE_Material *w_portalgun_tex;
extern NE_Palette *w_portalgun_pal;

extern NE_Material* white_ceiling_tile002a, * white_floor_tile002a, * white_floor_tile002a_hd, * white_wall_tile003a, * white_wall_tile003a_hd, * white_wall_tile003c, * white_wall_tile003c_hd, * white_wall_tile003f, * white_wall_tile003f_hd, * black_floor_metal_001c, * black_floor_metal_001c_hd, * black_wall_metal_002a, * black_wall_metal_002a_hd, * black_wall_metal_002b, * black_wall_metal_002b_hd, * black_wall_metal_002c, * black_wall_metal_002c_hd, * Debug_Material, * debugempty;
extern NE_Palette* white_ceiling_tile002aPal, * white_floor_tile002aPal, * white_floor_tile002a_hdPal, * white_wall_tile003aPal, * white_wall_tile003a_hdPal, * white_wall_tile003cPal, * white_wall_tile003c_hdPal, * white_wall_tile003fPal, * white_wall_tile003f_hdPal, * black_floor_metal_001cPal, * black_floor_metal_001c_hdPal, * black_wall_metal_002aPal, * black_wall_metal_002a_hdPal, * black_wall_metal_002bPal, * black_wall_metal_002b_hdPal, * black_wall_metal_002cPal, * black_wall_metal_002c_hdPal;




void LoadTextures();

int loadLevel();

void LoadMisc(void);
//i split blocks to sides for using the nodraw texture
// @param x1,y1,z1 vertex 1 position
// @param x2,y2,z2 vertex 2 position
// @param x3,y3,z3 vertex 3 position
// @param id is id
void RenderPlanes(Level level);
#endif