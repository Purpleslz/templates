pnt gt_itsec_pnt(pnt A,pnt B,pnt C,pnt D)          
{
  double t1=cross(A,C,B),t2=cross(A,B,D);
  return (C+(D-C)/(1/(t1/(t1+t2))));
}
