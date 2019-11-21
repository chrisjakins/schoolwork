// Jakins, Christopher
// cfj2309
// 2019-11-20

//----------------------------------------------------------
#include <math.h>
#include <stdio.h>

#include "cull.h"
#include "vertex.h"

//----------------------------------------------------------
int cull( Vertex *v1, Vertex *v2, Vertex *v3, Vertex *cameraPosition )
{
  // TODO: Compute the toTriangle vector.  Compute the triangle
  //       normal vector.  Compute the dot product of these two
  //       vectors.  Return an indication of whether this triangle
  //       should be culled.
  //4. Ensure you compute the cross product of the triangle side
  //   vectors to get the normal vector in the correct order.  If
  //   you don't, all of your normal vectors will be reversed.
  double toTriangleX = v1->x;
  double toTriangleY = v1->y;
  double toTriangleZ = v1->z - HUGE_VAL;
  if (cameraPosition->z != 0) {
    toTriangleZ = v1->z - cameraPosition->z;
  }

  double aX = v2->x - v1->x;
  double aY = v2->y - v1->y;
  double aZ = v2->z - v1->z;

  double bX = v3->x - v1->x;
  double bY = v3->y - v1->y;
  double bZ = v3->z - v1->z;

  double normalX = aY * bZ - aZ * bY;
  double normalY = -1 * (aX * bZ - aZ * bX);
  double normalZ = aX * bY - aY * bX;

  double dot = toTriangleX * normalX + toTriangleY * normalY + toTriangleZ * normalZ;

  return dot < 0 ? 0 : 1;
}

//----------------------------------------------------------
