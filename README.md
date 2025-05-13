# README

This package contains example C++ code for calculating the closest approach of
two paths in 3D space.

- The classes are defined in a namespace, **paths**
- The base class is **path**
- The available path derived classes are **helix** and **line**.
- Helices are defined according to the ALEPH and DZERO conventions.
- The function **closest_approach** returns the smallest separation of
  two input paths, together with the closest point (x,y,x) on each path
  and the number of iterations taken to find the minimum within a specified
  tolerance.

taus.cpp is an example program to calculate the closest approach of a helix and
a straight line.

example.C is a ROOT macro to draw the result in a 3D view.
taus.C is a helper macro for example.C which needs to compiled by ROOT due to
limitions of the Cling interpreter.
