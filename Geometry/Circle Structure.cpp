struct Circle
{
  pnt c;
  double r;
  Circle () {}
  
  Circle (const pnt & _c, double _r) { c = _c; r = _r; } {}
  
  double area() const { return pi * r * r; } 
};
