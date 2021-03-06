// Jakins, Christopher
// cfj2309
// 2019-11-20
//----------------------------------------------------------
#include <stdio.h>

#include "cull.h"
#include "line.h"
#include "projection.h"
#include "triangle.h"
#include "vertex.h"

View *_view = NULL;

//----------------------------------------------------------
void cullProjectDumpTriangle( View *view, Projection *projection, Vertex *v1, Vertex *v2, Vertex *v3 )
{
  // TODO: If culling is active and the triangle should be culled,
  //       do nothing.  Otherwise project the vertices and dump
  //       the triangle.
  Vertex cam;
  cam.x = 0;
  cam.y = 0;
  cam.z = view->m_cameraDistance;

  // copy vertices
  Vertex tempList[3];
  tempList[0] = *v1;
  tempList[1] = *v2;
  tempList[2] = *v3;

  if ((view->m_cull && cull(v1, v2, v3, &cam)) || !view->m_cull) {
    projectVertexList(projection, tempList, 3);
    dumpTriangle(&tempList[0], &tempList[1], &tempList[2]);
  }
}

//----------------------------------------------------------
void dumpTriangle( Vertex *v1, Vertex *v2, Vertex *v3 )
{
  Line l;

  l.p1X = v1->x;
  l.p1Y = v1->y;
  l.p2X = v2->x;
  l.p2Y = v2->y;

  if ( clipLine( _view, &l ) ) {
    dumpLine( &l );
  }

  l.p1X = v2->x;
  l.p1Y = v2->y;
  l.p2X = v3->x;
  l.p2Y = v3->y;

  if ( clipLine( _view, &l ) ) {
    dumpLine( &l );
  }

  l.p1X = v3->x;
  l.p1Y = v3->y;
  l.p2X = v1->x;
  l.p2Y = v1->y;

  if ( clipLine( _view, &l ) ) {
    dumpLine( &l );
  }
}

//----------------------------------------------------------
void setPortal( View *v )
{
  _view = v;
}

//----------------------------------------------------------

