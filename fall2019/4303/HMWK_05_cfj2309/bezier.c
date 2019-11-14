// Jakins, Christopher
// cfj2309
// 2019-11-11
//----------------------------------------------------------
#include <stdio.h>

#include "bezier.h"
#include "model.h"
#include "triangle.h"
#include "vertex.h"

void _computeCoefficients( double u, double v, double *c );

//----------------------------------------------------------
void generateBezierPoints( Model *model, int resolution )
{
  // TODO: Iterate through each patch, each value of u, and each
  //       value of v (so three nested loops in that order).
  //       Compute the 16 coefficients for the specific values of
  //       u and v.
  //       Iterate through the 16 coefficients multiplying each by
  //       the corresponding control point and accumulating the
  //       result in the current Bézier surface point.
  //       This is done for that point's x, y, and z coordinates.
  int res2 = resolution * resolution;
  for (int patch = 0; patch < model->m_numPatches; ++patch) {
    //printf("patch # %d\n", patch);
    for (int i = 0; i < resolution; ++i) {
      double u = 1.0 / (resolution - 1) * i;

      for (int j = 0; j < resolution; ++j) {
        double v = 1.0 / (resolution - 1) * j;
        double coeff[16] = {0};
        _computeCoefficients(u, v, coeff);

        double x = 0.0;
        double y = 0.0;
        double z = 0.0;

        for (int c = 0; c < 16; ++c) {
            x += coeff[c] * model->m_vertex[model->m_patch[patch][c]].x;
            y += coeff[c] * model->m_vertex[model->m_patch[patch][c]].y;
            z += coeff[c] * model->m_vertex[model->m_patch[patch][c]].z;
        }

        //TODO: what if numPatches > 1?
        // 2 patches, resolution = 4
        //p0 0 0 0 0 0 0 0 0 0  0  0  0  0  0  0  1  1
        //i0 0 0 0 1 1 1 1 2 2  2  2  3  3  3  3
        //j0 1 2 3 0 1 2 3 0 1  2  3  0  1  2  3
        // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
        model->m_patchVertex[res2 * patch + resolution * i + j].x = x;
        model->m_patchVertex[res2 * patch + resolution * i + j].y = y;
        model->m_patchVertex[res2 * patch + resolution * i + j].z = z;
        //printf("%f -- %f -- %f -- %f -- %f\n", u, v, x, y, z);
      }
    }
  }
}

//----------------------------------------------------------
void generateBezierTriangles( Model *model, int resolution )
{
  // TODO: Iterate through each patch, each row of that patch, and
  //       and each column of that patch (so three nested loops in
  //       that order).
  //       Dump the two triangles that correspond to the row and
  //       column positions using the dumpTriangle() routine.
  //       Remember that you have to consider only the first
  //       through the penultimate row and the first through the
  //       penultimate column when generating a patch's triangles.
  //       Ensure that you generate the triangles in the correct
  //       order and use the vertices in the correct order.
  int res2 = resolution * resolution;
  for (int patch = 0; patch < model->m_numPatches; ++patch) {
    for (int row = 0; row < resolution - 1; ++row) {
      for (int col = 0; col < resolution - 1; ++col) {
        dumpTriangle(&model->m_patchVertex[res2 * patch + row * resolution + col]
                     , &model->m_patchVertex[res2 * patch + row * resolution + col + resolution]
                     , & model->m_patchVertex[res2 * patch + row * resolution + col + resolution + 1]);
        dumpTriangle(&model->m_patchVertex[res2 * patch + row * resolution + col + resolution + 1]
                     , &model->m_patchVertex[res2 * patch + row * resolution + col + 1]
                     , & model->m_patchVertex[res2 * patch + row * resolution + col]);
      }
    }
  }
}

//----------------------------------------------------------
void _computeCoefficients( double u, double v, double *coefficients )
{
  // TODO: For the given u and v values, generate the 16 Bernstein
  //       coefficients.  Ensure that you compute and store them
  //       in the proper order: c00, c01, c02, c03, c10, c11, c12,
  //       c13, c20, c21, c22, c23, c30, c31, c31, c32, c33.
  double u2 = u * u;
  double u3 = u2 * u;
  double v2 = v * v;
  double v3 = v2 * v;

  double oU = 1 - u;
  double oV = 1 - v;

  double oU2 = oU * oU;
  double oU3 = oU2 * oU;
  double oV2 = oV * oV;
  double oV3 = oV2 * oV;

  // c[0,0] - c[0,3]
  coefficients[0] = oU3 * oV3;
  coefficients[1] = 3 * v * oU3 * oV2;
  coefficients[2] = 3 * v2 * oU3 * oV;
  coefficients[3] = v3 * oU3;

  // c[1,0] - c[1,3]
  coefficients[4] = 3 * u * oU2 * oV3;
  coefficients[5] = 9 * u * v * oU2 * oV2;
  coefficients[6] = 9 * u * v2 * oU2 * oV;
  coefficients[7] = 3 * u * v3 * oU2;

  // c[2,0] - c[2,3]
  coefficients[8] = 3 * u2 * oU * oV3;
  coefficients[9] = 9 * u2 * v * oU * oV2;
  coefficients[10] = 9 * u2 * v2 * oU * oV;
  coefficients[11] = 3 * u2 * v3 * oU;

  // c[3,0] - c[3,3]
  coefficients[12] = u3 * oV3;
  coefficients[13] = 3 * u3 * v * oV2;
  coefficients[14] = 3 * u3 * v2 * oV;
  coefficients[15] = u3 * v3;
}

//----------------------------------------------------------

