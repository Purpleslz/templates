struct pnt
{
  double x,y;
  pnt () { };
  pnt (double a,double b) { x=a; y=b; }
  pnt operator + (const pnt &A) { return pnt(x+A.x,y+A.y); }
  pnt operator - (const pnt &A) { return pnt(x-A.x,y-A.y); }
  double operator ^ (const pnt &A) { return x*A.x+y*A.y; }   // 重载^点积
  pnt operator / (const double &A) { return pnt(x/A,y/A); }
  double operator * (const pnt &A) { return x*A.y-A.x*y; }  //重载*叉积

  bool operator== (const pnt & a) const { return ( sgn(x - a.x) == 0 ) && ( sgn(y - a.y) == 0 ); }

  bool operator< (const pnt & a) const { return ( sgn(x - a.x) == 0 ) ? ( sgn( y - a.y ) < 0 ) : (x < a.x); }

  double len() const { return sqrt(x*x + y*y); }

  double sqrlen() const { return x*x + y*y; }

  pnt trunc(double l) const
  {
    double r = l/len();
    return pnt(x*r,y*r);
  }


  //left anti-clockwise
  //right clockwise

  pnt rotate_left() const { return pnt(-y,x); }

  pnt rotate_left(double ang) const
  {
    double c = cos(ang), s = sin(ang);
    return pnt(x*c - y*s, y*c + x*s);
  }

  pnt rotate_left(double c,double s) const { return pnt(x*c - y*s, y*c + x*s); }

  pnt rotate_right() const { return pnt(y,-x); }

  pnt rotate_right(double ang) const
  {
    double c = cos(ang), s = sin(ang);
    return pnt(x*c + y*s, y*c - x*s);
  }

  pnt rotate_right(double c,double s) const { return pnt(x*c + y*s, y*c - x*s); }
};
