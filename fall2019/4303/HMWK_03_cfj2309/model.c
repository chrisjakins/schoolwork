// Jakins, Christopher
// cfj2309
// 2019-10-23
//----------------------------------------------------------
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "model.h"

#define min(a,b) ({ __typeof__(a) _a = (a);  __typeof__(b) _b = (b); _a < _b ? _a : _b; })
#define max(a,b) ({ __typeof__(a) _a = (a);  __typeof__(b) _b = (b); _a > _b ? _a : _b; })

//----------------------------------------------------------
Model *allocModel( int numVertices, int numFaces )
{
  Model *model;

  model = (Model *) calloc( 1, sizeof( Model ) );
  if ( model == NULL ) {
    fprintf( stderr, "allocModel: Unable to allocate Model.\n" );
    exit( 1 );
  }

  if ( numVertices > 0 ) {
    model->m_numVertices = numVertices;
    model->m_vertex = (Vertex *) calloc( numVertices, sizeof( Vertex ) );
    if ( model->m_vertex == NULL ) {
      fprintf( stderr, "allocModel: Unable to allocate %d Vert%s.\n",
        numVertices, (numVertices == 1) ? "ex" : "ices" );
    }
  }

  if ( numFaces > 0 ) {
    model->m_numFaces = numFaces;
    model->m_face = (Face *) calloc( numFaces, sizeof( Face ) );
    if ( model->m_face == NULL ) {
      fprintf( stderr, "allocModel: Unable to allocate %d Face%s.\n",
        numFaces, (numFaces == 1) ? "" : "s" );
    }
  }

  return model;
}

//----------------------------------------------------------
void dumpModel( Model *model )
{
  printf( "#- Model parameters --------------------\n" );
  printf( "Vertex count : %5d\n", model->m_numVertices );
  printf( "Face count   : %5d\n", model->m_numFaces );
  printf( "Center       : ( %13.6f, %13.6f, %13.6f )\n",
    model->m_center.x, model->m_center.y, model->m_center.z );

  printf( "\n#- Vertex list -------------------------\n" );
  for ( int i=0; i<model->m_numVertices; i++ ) {
    printf( "  [%5d]  ", i );
    dumpVertex( &model->m_vertex[i] );
    putc( '\n', stdout );
  }

  printf( "\n#- Face list ---------------------------\n" );
  for ( int i=0; i<model->m_numFaces; i++ ) {
    printf( "  [%5d]  ", i );
    dumpFace( &model->m_face[i] );
    putc( '\n', stdout );
  }

  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------
void dumpFace( Face *face )
{
  printf( "%5d, %5d, %5d", face->v1, face->v2, face->v3 );
}

//----------------------------------------------------------
void freeModel( Model *model )
{
  if ( model->m_vertex != NULL ) {
    free( model->m_vertex );
  }

  if ( model->m_face != NULL ) {
    free( model->m_face );
  }

  free( model );
}

//----------------------------------------------------------
Model *loadModel( char *fName )
{
  FILE *fp = fopen( fName, "r" );
  if ( fp == NULL ) {
    fprintf( stderr, "loadModel: Unable to open '%s' for read.\n", fName );
    exit( 1 );
  }

  //--------------------------------------
  int     numVertices = 0;
  int     numFaces    = 0;
  char   *line        = NULL;
  size_t  len         = 0;
  size_t  read;

  // TODO: Declare variables to hold the mins and maxes for
  //       x, y, and z.  Initialize them properly.
  double xMin = 1000.0, xMax = 0.0;
  double yMin = 1000.0, yMax = 0.0;
  double zMin = 1000.0, zMax = 0.0;

  while ( ( read = getline( &line, &len, fp ) ) != -1 ) {
    char *ptr = line;

    while ( *ptr && isspace( *ptr ) ) ptr++;
    if ( *ptr == 'v' ) ++numVertices;
    if ( *ptr == 'f' ) ++numFaces;
  }

  rewind( fp );

  //--------------------------------------
  Model *model = allocModel( numVertices, numFaces );

  Vertex *vertex  = model->m_vertex;
  Face   *face    = model->m_face;
  int     lineNum = 0;

  while ( ( read = getline( &line, &len, fp ) ) != -1 ) {
    lineNum++;

    char *ptr = line;

    while ( *ptr && isspace( *ptr ) ) ptr++;

    if ( *ptr == 'v' ) {
      int conv = sscanf( ptr+1, "%lf %lf %lf",
        &vertex->x, &vertex->y, &vertex->z );

      if ( conv != 3 ) {
        fprintf( stderr, "loadModel: Unable to load vertex at line %d.", lineNum );
      }

      // TODO: Keeping running values for mins and maxes
      //       for x, y, z.  (Use the min, max functions
      //       declared above.)
      xMin = min(xMin, vertex->x);
      xMax = max(xMax, vertex->x);
      yMin = min(yMin, vertex->y);
      yMax = max(yMax, vertex->y);
      zMin = min(zMin, vertex->z);
      zMax = max(zMax, vertex->z);

      vertex++;
      continue;
    }

    if ( *ptr == 'f' ) {
      int conv = sscanf( ptr+1, "%d %d %d",
        &face->v1, &face->v2, &face->v3 );

      face->v1--;
      face->v2--;
      face->v3--;

      if ( conv != 3 ) {
        fprintf( stderr, "loadModel: Unable to load face at line %d.", lineNum );
      }

      face++;
      continue;
    }
  }

  // TODO: Using the tracked mins and maxes for x, y, and z
  //       compute the center of the model and store its x,
  //       y, z coordinates in model->m_center.
  model->m_center.x = xMin + (xMax - xMin) / 2;
  model->m_center.y = yMin + (yMax - yMin) / 2;
  model->m_center.z = zMin + (zMax - zMin) / 2;

  //--------------------------------------
  if ( line != NULL ) {
    free( line );
  }

  fclose( fp );

  //--------------------------------------
  return model;
}

//----------------------------------------------------------

