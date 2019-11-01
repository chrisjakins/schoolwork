// Jakins, Christopher
// cfj2309
// 2019-10-29
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "line.h"

//----------------------------------------------------------
#define INSIDE (0)
#define LEFT   (1)
#define RIGHT  (2)
#define BELOW  (4)
#define ABOVE  (8)

#define EPSILON (1e-13)

int _regionCode( double x, double y, View *v );
void _updateLine(int code, Line *l, View *v, int point);

//----------------------------------------------------------
/*
typedef struct _Line {
  double p1X, p1Y;
  double p2X, p2Y;
} Line;
*/

int clipLine( View *v, Line *l )
{
  // TODO: Clip the line l against the portal limits
  //       in the view using the Cohen-Sutherland
  //       method as described in class.
  //       If p1 or p2 of the line is updated, ensure
  //       that you change it in the Line structure.
  //       Return whether the line should be drawn
  //       at all (0 for no, 1 for yes).
  int p1code = 1;
  int p2code = 1;

  while (1) {
      p1code = _regionCode(l->p1X, l->p1Y, v);
      p2code = _regionCode(l->p2X, l->p2Y, v);
      if (p1code & p2code) {
        return 0;
      }
      else if (p1code == 0 && p2code == 0) {
        return 1;
      }
      // update
      p1code == INSIDE ? _updateLine(p2code, l, v, 2) : _updateLine(p1code, l, v, 1);
  }
  return 0;
}

void _updateLine(int code, Line *l, View *v, int point) {
  double x = 0, y = 0;
  if (code & ABOVE) {
    x = l->p1X + (l->p2X - l->p1X) * (v->m_portalYMax - l->p1Y) / (l->p2Y - l->p1Y);
    y = v->m_portalYMax;
  }
  else if (code & BELOW) {
    x = l->p1X + (l->p2X - l->p1X) * (v->m_portalYMin - l->p1Y) / (l->p2Y - l->p1Y);
    y = v->m_portalYMin;
  }
  else if (code & RIGHT) {
    x = v->m_portalXMax;
    y = l->p1Y + (l->p2Y - l->p1Y) * (v->m_portalXMax - l->p1X) / (l->p2X - l->p1X);
  }
  else if (code & LEFT) {
    x = v->m_portalXMin;
    y = l->p1Y + (l->p2Y - l->p1Y) * (v->m_portalXMin - l->p1X) / (l->p2X - l->p1X);
  }

  if (point == 1) {
    l->p1X = x;
    l->p1Y = y;
  }
  else if (point == 2) {
    l->p2X = x;
    l->p2Y = y;
  }
}

//----------------------------------------------------------
void dumpLine( Line *l )
{
  printf( "l %8.1f %8.1f %8.1f %8.1f\n",
    l->p1X, l->p1Y, l->p2X, l->p2Y );
}

//----------------------------------------------------------
int _regionCode( double x, double y, View *v )
{
  // TODO: Compute the region code for the point x, y
  //       by comparing against the portal limits in
  //       the view.  (Don't forget to use EPSILON
  //       comparisons!)
  //       Return the computed code.
  int CODE = INSIDE;

  if (v->m_portalXMin - x > EPSILON) {
    CODE |= LEFT;
  }
  else if (x - v->m_portalXMax > EPSILON) {
    CODE |= RIGHT;
  }

  if (v->m_portalYMin - y > EPSILON) {
    CODE |= BELOW;
  }
  else if (y - v->m_portalYMax > EPSILON) {
    CODE |= ABOVE;
  }

  return CODE;
}

//----------------------------------------------------------

