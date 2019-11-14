// Jakins, Christopher
// cfj2309
// 2019-11-11
//----------------------------------------------------------
#include <stdio.h>

#include "line.h"
#include "triangle.h"

View *_view = NULL;

//----------------------------------------------------------
void dumpTriangle( Vertex *v1, Vertex *v2, Vertex *v3 )
{
  // TODO:  Draw the three lines that are made from v1, v2, and
  //        v3.  Be sure you use clipLine() first to see if the
  //        line needs to be drawn.  Use dumpLine() to generate
  //        the actual line.
  Line temp;
  temp.p1X = v1->x;
  temp.p2X = v2->x;
  temp.p1Y = v1->y;
  temp.p2Y = v2->y;
  if (clipLine(_view, &temp)) {
    dumpLine(&temp);
  }

  temp.p1X = v2->x;
  temp.p2X = v3->x;
  temp.p1Y = v2->y;
  temp.p2Y = v3->y;
  if (clipLine(_view, &temp)) {
    dumpLine(&temp);
  }

  temp.p1X = v3->x;
  temp.p2X = v1->x;
  temp.p1Y = v3->y;
  temp.p2Y = v1->y;
  if (clipLine(_view, &temp)) {
    dumpLine(&temp);
  }
}

//----------------------------------------------------------
void setPortal( View *v )
{
  // TODO:  Remember the view so it can be clipped against when
  //        triangles are drawn later.
  _view = v;
}

//----------------------------------------------------------

