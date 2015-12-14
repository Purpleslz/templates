inline int line_relationship(pnt a1, pnt a2, pnt b1, pnt b2, pnt &c)
{
  if ( sgn( (a2-a1) * (b2 - b1) ) == 0 ) //parallel
  {
    if ( sgn( cross(a1, b1, b2) ) == 0 ) return 2;
    return 0; 
  }
  
  c = gt_itsec_pnt(a1, a2, b1, b2);
  
  if ( (sgn((a1-c) ^ (a2 - c)) <= 0) && (sgn((b1-c) ^ (b2 - c)) <= 0) ) return 1;
  return 0;
}
