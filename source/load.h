#include <NEMain.h>


#include "cube_bin.h"
#include "debug_plane_bin.h"
#include "tile_clean16_pal_bin.h"
#include "white_ceiling_tile002a_tex_bin.h"
#include "white_ceiling_tile002a_pal_bin.h"
#include "white_floor_tile002a_tex_bin.h"
#include "white_floor_tile002a_pal_bin.h"
#include "white_floor_tile002a_hd_tex_bin.h"
#include "white_floor_tile002a_hd_pal_bin.h"
#include "white_wall_tile003a_tex_bin.h"
#include "white_wall_tile003a_pal_bin.h"
#include "white_wall_tile003a_hd_tex_bin.h"
#include "white_wall_tile003a_hd_pal_bin.h"
#include "white_wall_tile003c_tex_bin.h"
#include "white_wall_tile003c_pal_bin.h"
#include "white_wall_tile003c_hd_tex_bin.h"
#include "white_wall_tile003c_hd_pal_bin.h"
#include "white_wall_tile003f_tex_bin.h"
#include "white_wall_tile003f_pal_bin.h"
#include "white_wall_tile003f_hd_tex_bin.h"
#include "white_wall_tile003f_hd_pal_bin.h"
#include "metal_clean16_pal_bin.h"
#include "black_floor_metal_001c_tex_bin.h"
#include "black_floor_metal_001c_pal_bin.h"
#include "black_floor_metal_001c_hd_tex_bin.h"
#include "black_floor_metal_001c_hd_pal_bin.h"
#include "black_wall_metal_002a_tex_bin.h"
#include "black_wall_metal_002a_pal_bin.h"
#include "black_wall_metal_002a_hd_tex_bin.h"
#include "black_wall_metal_002a_hd_pal_bin.h"
#include "black_wall_metal_002b_tex_bin.h"
#include "black_wall_metal_002b_pal_bin.h"
#include "black_wall_metal_002b_hd_tex_bin.h"
#include "black_wall_metal_002b_hd_pal_bin.h"
#include "black_wall_metal_002c_tex_bin.h"
#include "black_wall_metal_002c_pal_bin.h"
#include "black_wall_metal_002c_hd_tex_bin.h"
#include "black_wall_metal_002c_hd_pal_bin.h"
#include "Debug_tex_bin.h"
#include "debugempty_tex_bin.h"

extern NE_Material* white_ceiling_tile002a, * white_floor_tile002a, * white_floor_tile002a_hd, * white_wall_tile003a, * white_wall_tile003a_hd, * white_wall_tile003c, * white_wall_tile003c_hd, * white_wall_tile003f, * white_wall_tile003f_hd, * black_floor_metal_001c, * black_floor_metal_001c_hd, * black_wall_metal_002a, * black_wall_metal_002a_hd, * black_wall_metal_002b, * black_wall_metal_002b_hd, * black_wall_metal_002c, * black_wall_metal_002c_hd, * Debug_Material, * debugempty;
extern NE_Palette* white_ceiling_tile002aPal, * white_floor_tile002aPal, * white_floor_tile002a_hdPal, * white_wall_tile003aPal, * white_wall_tile003a_hdPal, * white_wall_tile003cPal, * white_wall_tile003c_hdPal, * white_wall_tile003fPal, * white_wall_tile003f_hdPal, * black_floor_metal_001cPal, * black_floor_metal_001c_hdPal, * black_wall_metal_002aPal, * black_wall_metal_002a_hdPal, * black_wall_metal_002bPal, * black_wall_metal_002b_hdPal, * black_wall_metal_002cPal, * black_wall_metal_002c_hdPal;




void LoadTextures(int textureMode);

int loadLevel();

//i split blocks to sides for using the nodraw texture
// @param x1,y1,z1 vertex 1 position
// @param x2,y2,z2 vertex 2 position
// @param x3,y3,z3 vertex 3 position
// @param id is id
void RenderPlanes(Level level);
void RenderPlanesManual(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, double u, double v, NE_Material *Material, int Zone, int id);
