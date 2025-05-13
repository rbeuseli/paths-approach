// Example code to find the closest approach of a helix to a line from the
// origin.
//
#include "path.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <tuple>

using namespace paths;
using namespace std;

std::ostream& operator<<(std::ostream& out, point p)
{
  out << "( " << p._x << " , " << p._y << " , " << p._z << " )";
  return out;
}

int main(int argc, char *argv[])
{
  // take range from input arguments as a precursor to figuring out an iteration
  // scheme
  double hlo, hhi, llo, lhi;
  if (argc != 5)
  {
    throw invalid_argument("4 calling arguments needed: lo/hi length ranges");
  }
  else
  {
    hlo = stod(argv[1]);
    hhi = stod(argv[2]);
    llo = stod(argv[3]);
    lhi = stod(argv[4]);
  }
  // helix h(s1rinv, tanl, phi0, s2d0, z0);
  helix h(0.1, 0.3, 2.0, 0.05, 4.0);  // a tau?
  double origin[] = {0., 0., 0.};
  double dirn[] = {-1., 1., 1.};
  line l(origin, dirn);                // a thrust axis?
  // In this example I'm taking a range of -20 to +20 in length for both curves
  // as the start point is not necessarily at d0 and z0.
  // test closest_approach
  double sa[] = {hlo, hhi};
  double sb[] = {llo, lhi};
  auto result = closest_approach(h, l, sa, sb, 0.01);
  double dmin = get<0>(result);
  point ph = get<1>(result);
  point pl = get<2>(result);
  int iterations = get<3>(result);
  cout << "closest approach: " << dmin << " after "
       << iterations << " iterations" << endl;
  cout << "point ph" << ph << endl;
  cout << "point pl" << pl << endl;
  return 0;
}
