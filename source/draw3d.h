#ifndef DRAW3D_H
#define DRAW3D_H

#define DERGEESTO511 0.704500978473582

extern NE_Camera* Camara;
void Draw3DScene(void);

// Render a quad
void RenderQuad(Vector3 vertex1, Vector3 vertex2, Vector3 vertex3, Vector3 vertex4, NE_Material* material, Vector2 texCoord0, Vector2 texCoord1);

#endif