// Jakins, Christopher
// cfj2309
// 2019-10-29
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "line.h"
#include "model.h"
#include "projection.h"
#include "view.h"

//----------------------------------------------------------
int main( int argc, char *argv[] )
{
  if ( argc != 3 ) {
    fprintf( stderr, "Usage: %s <modelFileName> <viewFileName>\n", argv[0] );
    exit( 1 );
  }

  //--------------------------------------
  // Load the model and view.
  Model *m = loadModel( argv[1] );
  dumpModel( m, 0 );

  View *v = loadView( argv[2] );
  dumpView( v );

  // Print the canvas side for the SDF file.
  printf( "c %4d %4d\n", v->m_width, v->m_height );

  // Rotate the vertices according to the Euler angles
  // specified in the view.
  rotateVertexList( v, m->m_vertex, m->m_numVertices, m->m_center );

  // Compute the projecion according to the parameters given
  // in the view.
  Projection *p = computeProjection( v );
  dumpProjection( p );

  // Project the rotated vertices according to the just-computed
  // projection.
  projectVertexList( p, m->m_vertex, m->m_numVertices );

  //--------------------------------------
  // Draw lines corresponding to the viewport region.
  Line line;

  // TODO: "Draw" the four edges of the portal region as
  //       given in the view structure.  Use a Line
  //       structure and the dumpLine() routine.
  Line left, right, top, bottom;

  left.p1X = v->m_portalXMin;
  left.p1Y = v->m_portalYMin;
  left.p2X = v->m_portalXMin;
  left.p2Y = v->m_portalYMax;

  right.p1X = v->m_portalXMax;
  right.p1Y = v->m_portalYMax;
  right.p2X = v->m_portalXMax;
  right.p2Y = v->m_portalYMin;

  top.p1X = v->m_portalXMax;
  top.p1Y = v->m_portalYMin;
  top.p2X = v->m_portalXMin;
  top.p2Y = v->m_portalYMin;

  bottom.p1X = v->m_portalXMin;
  bottom.p1Y = v->m_portalYMax;
  bottom.p2X = v->m_portalXMax;
  bottom.p2Y = v->m_portalYMax;

  dumpLine( &left );
  dumpLine( &bottom );
  dumpLine( &right );
  dumpLine( &top );

  //--------------------------------------
  // Check each line of each triangle.
  // Display it (in clipped form if necesssary).

  for ( int i=0; i<m->m_numFaces; i++ ) {
    // TODO: Check each line of each face to see if
    //       it should be drawn.  If so, draw it.
    //       Use a Line structure to represent the
    //       the line, the clipLine() routine to
    //       clip it, and the dumpLine() routine to
    //       "draw" it (if necessary).
    Line temp;
    temp.p1X = m->m_vertex[m->m_face[i].v1].x;
    temp.p1Y = m->m_vertex[m->m_face[i].v1].y;
    temp.p2X = m->m_vertex[m->m_face[i].v2].x;
    temp.p2Y = m->m_vertex[m->m_face[i].v2].y;

    int status = clipLine(v, &temp);
    if (status) {
        dumpLine(&temp);
    }

    temp.p1X = m->m_vertex[m->m_face[i].v2].x;
    temp.p1Y = m->m_vertex[m->m_face[i].v2].y;
    temp.p2X = m->m_vertex[m->m_face[i].v3].x;
    temp.p2Y = m->m_vertex[m->m_face[i].v3].y;

    status = clipLine(v, &temp);
    if (status) {
        dumpLine(&temp);
    }

    temp.p1X = m->m_vertex[m->m_face[i].v3].x;
    temp.p1Y = m->m_vertex[m->m_face[i].v3].y;
    temp.p2X = m->m_vertex[m->m_face[i].v1].x;
    temp.p2Y = m->m_vertex[m->m_face[i].v1].y;

    status = clipLine(v, &temp);
    if (status) {
        dumpLine(&temp);
    }
  }

  //--------------------------------------
  // All done!  Free up the allocated strucures.
  freeModel( m );
  freeView( v );
  freeProjection( p );
}

//----------------------------------------------------------

