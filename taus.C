#include "path.hpp"

using namespace paths;
using namespace std;

void taus(double s1rinv, double tanl, double phi0, double s2d0, double z0,
          double sxy0, double dsxy,
          int np, double px[], double py[], double pz[])
{
  // Calculate np points along a helix defined by the ALEPH/D0 parameters.
  // Return the coordinates in arrays px,py,pz.
  // The purpose of this function is to provides the points for a TPolyLine3D.
  //
  helix h(s1rinv, tanl, phi0, s2d0, z0);
  for (int i=0; i<np; i++)
  {
    double sxy = sxy0 +i*dsxy;
    point p = h.step(sxy);
    px[i] = p._x;
    py[i] = p._y;
    pz[i] = p._z;
  }
}

void liner(double origin[], double dirn[], double length,
            double px[], double py[], double pz[])
{
  // Same for a line, but we only need two points to draw it.
  //
  px[0] = origin[0];
  py[0] = origin[1];
  pz[0] = origin[2];
  line l(origin, dirn);
  point p = l.step(length);
  px[1] = p._x;
  py[1] = p._y;
  pz[1] = p._z;
}
