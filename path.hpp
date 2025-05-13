#ifndef _path_hpp_
#define _path_hpp_
#include <tuple>
// base class for propagation along a path
//
namespace paths
{
  // ---------------- point ---------------
  struct point
  {
    point() { _x = _y = _z = 0.; }

    point( double x, double y, double z )
    {
      _x = x;
      _y = y;
      _z = z;
    }
    double dsq(const point& p); // square of distance from p

    double _x, _y, _z;
  };

  // ---------------- path ---------------
  class path
  {
    public:
      path() {}
      virtual ~path();
      virtual point step(double length) =0; // return coordinates along path
  };

  // ---------------- helix ---------------
  class helix: public path
  {
    public:
      helix() {}
      helix(double s1rinv, double tanl, double phi0, double s2d0, double z0);
      ~helix() {}
      point step(double sxy);
    private:
      // helix parameters, Aleph convention.
      double _s1rinv;
      double _tanl;
      double _phi0;
      double _s2d0;
      double _z0;
      // values needed for every step calculation
      // set in constructor
      double _rad;    // helix radius.
      double _alpha0; // angle from centre to d0.
      double _xc;     // x coord of helix centre.
      double _yc;     // y coord of helix centre.
  };

  // ---------------- line ---------------
  class line: public path
  {
    public:
      line() {}
      line(double start[3], double dirn[3]);
      ~line() {}
      point step(double length);
    private:
      double _x, _y, _z;    // start point
      double _dx, _dy, _dz; // direction cosines
  };

  // ---------------- non class functions ------------------
  std::tuple<double, point, point, int>
  closest_approach(path& A, path& B, double sa[2], double sb[2], double eps);
} // paths
#endif    /* _path_hpp_ */
