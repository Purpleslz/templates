
pair<pnt,pnt> circle_intersection(circle c1,circle c2)
{
  pnt a = c1.c;
  pnt b = c2.c;
  double r1 = c1.r;
  double r2 = c2.r;
  
  double d = (b - a).len();
  
  if ( d == r1 + r2) return make_pair( a + (b-a).trunc(r1) , a + (b-a).trunc(r1) );  //可去掉？ 
  double c = (r1 * r1 + d * d - r2 * r2) / ( 2 * r1 * d);
  double s = sqrt( 1.0 - c * c);
  pnt v = (b - a) . trunc(r1);
  return make_pair( a + v.rotate_right(c,s) , a + v.rotate_left(c,s) );
}

