//pn 原来的多边形 vp 新的多边形 A-B直线 
void calc(pnt A,pnt B)
{
  for (int i=0;i<N;++i)
  {
    int j=(i+1)%N;
    if (sgn(cross(A,B,pn[i]))*sgn(cross(A,B,pn[j]))<0)
    {
      pnt tmp=gt_itsec_pnt(pn[i],pn[j],A,B);
      vp[i].push_back(gt_itsec_pnt(pn[i],pn[j],A,B));
    }
  }
}