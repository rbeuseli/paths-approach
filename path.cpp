#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <tuple>
#include "path.hpp"

using std::cos;
using std::sin;
using std::sqrt;
using std::tie;
using std::tuple;
using std::make_tuple;
using std::min_element;

const double PIBY2 = 0.5*acos(-1.);

namespace paths
{

  // NB: this virtual destructor must NOT be defined as an inline function
  // in the class definition or we get undefined vtable errors in the
  // link step.  It took me a long time to debug that!
  path::~path() {}

  double point::dsq(const point& p)
  {
    // square of distance from p
    double d;
    double s2 = 0.0;
    d = _x - p._x; s2 += d*d;
    d = _y - p._y; s2 += d*d;
    d = _z - p._z; s2 += d*d;
    return s2;
  }

  helix::helix(double s1rinv, double tanl, double phi0, double s2d0, double z0)
  {
    _s1rinv = s1rinv;
    _tanl = tanl;
    _phi0 = phi0;
    _s2d0 = s2d0;
    _z0 = z0;
    if (s1rinv)
    {
      int s1 = (s1rinv > 0.0) ? 1 : -1;
      _rad = 1.0/fabs(s1rinv);
      _alpha0 = _phi0 - s1*PIBY2;
      double rd0 = s1*s2d0 - _rad;
      _xc = rd0*cos(_alpha0);
      _yc = rd0*sin(_alpha0);
    }
    else
    {
      throw std::invalid_argument("Cannot define a helix with zero curvature");
    }
  }

  point helix::step(double sxy)
  {
    // Calculate the point on the curve corresponding to the arc distance sxy
    // travelled from the d0 point in the x,y plane.
    //
    double psi = sxy*_s1rinv;         // angle turned in x,y
    double phi = _alpha0 + psi;       // angle of track at this point
    double xp = _xc + _rad*cos(phi);  // coordinates of track at this point
    double yp = _yc + _rad*sin(phi);
    double zp = _z0 + sxy*_tanl;
    point p(xp, yp, zp);
    return p;
  }

  line::line(double start[3], double dirn[3])
  {
    _x = start[0]; _y = start[1]; _z = start[2];
    _dx = dirn[0]; _dy = dirn[1]; _dz = dirn[2];
    double norm = sqrt(_dx*_dx + _dy*_dy + _dz*_dz);
    _dx = _dx/norm;
    _dy = _dy/norm;
    _dz = _dz/norm;
  }
  
  point line::step(double length)
  {
    return point(_x+length*_dx, _y+length*_dy, _z+length*_dz);
  }

  tuple<double, point, point, int>
  closest_approach(path& A, path& B, double sa[2], double sb[2], double eps)
  {
    // Find the closest approach between two paths.
    // Arguments:
    // A, B   : the paths
    // sa, sb : the lo and hi step limits of A and B on input,
    //        : overwritten with the converged limits on output.
    // eps    : the tolerance to be reached for the step ranges.
    //
    // Return values:
    // double : closest distance
    // point  : closest point on A
    // point  : closest point on B
    // int    : number of iterations to find solution
    // ----------------------------------------------------------
    int best = -1;  // index of closest corners.
    int iterations = 0;
    double d2best = -1.;
    double dbest = -1.;
    point bestA, bestB;
    while (abs(sa[1]-sa[0]) > eps || abs(sb[1]-sb[0]) > eps)
    {
      ++iterations;
      point alo = A.step(sa[0]);
      point ahi = A.step(sa[1]);
      point blo = B.step(sb[0]);
      point bhi = B.step(sb[1]);
      double dsq[] = { alo.dsq(blo), alo.dsq(bhi), ahi.dsq(blo), ahi.dsq(bhi) };
      double* least = min_element(dsq, dsq+4);
      best = least - dsq;
      d2best = dsq[best];
      // halve the range, keeping the pairing in place.
      switch (best)
      {
        case 0: // alo, blo is best
          sa[1] = sa[0] + 0.5*(sa[1]-sa[0]);
          sb[1] = sb[0] + 0.5*(sb[1]-sb[0]);
          bestA = alo;
          bestB = blo;
          break;
        case 1: // alo, bhi is best
          sa[1] = sa[0] + 0.5*(sa[1]-sa[0]);
          sb[0] = sb[1] - 0.5*(sb[1]-sb[0]);
          bestA = alo;
          bestB = bhi;
          break;
        case 2: // ahi, blo is best
          sa[0] = sa[1] - 0.5*(sa[1]-sa[0]);
          sb[1] = sb[0] + 0.5*(sb[1]-sb[0]);
          bestA = ahi;
          bestB = blo;
          break;
        case 3: // ahi, bhi is best
          sa[0] = sa[1] - 0.5*(sa[1]-sa[0]);
          sb[0] = sb[1] - 0.5*(sb[1]-sb[0]);
          bestA = ahi;
          bestB = bhi;
          break;
      }
    }
    dbest = sqrt(d2best);
    auto result = make_tuple(dbest, bestA, bestB, iterations);
    return result;
  }

} //paths
