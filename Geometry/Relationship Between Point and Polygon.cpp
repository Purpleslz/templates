
int get_position(const pnt &p, const pnt *pol, int n) {  
  double ang = 0;
  for (int i = 0; i < n; ++i) {
    if (pol[i] == p) return 0; 
    point p1 = pol[i] - p, p2 = pol[(i + 1) % n] - p;
    double c = trim((p1 ^ p2) / (p1.len() * p2.len()));
    ang += sgn(p1 * p2) * acos(c);
  }
  ang = abs(ang);
  return ang < 0.5 * pi ? -1 : (ang < 1.5 * pi ? 0 : 1);  //1在多边形内 -1 在多边形外 0 在多边形上 
}
