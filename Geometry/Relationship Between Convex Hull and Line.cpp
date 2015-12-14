
  total=0;
  for (int i=0;i<N;++i) total+=p[i]*p[(i+1)%N];
  
  if (sgn(total)<0)  //凸包定向 
  {
    total=-total;
    reverse(p,p+N);
  } 

  for (int i=N;i<=2*N-1;++i) p[i]=p[i-N];

  for (int i=0;i<N;++i)
  {
    tmp=p[(i+1)%N]-p[i];
    agl[i]=make_pair(atan2(tmp.y,tmp.x),i);
  }

  sort(agl,agl+N); //边按斜率排序 

  for (int i=1;i<=2*N-1;++i) sum[i]=sum[i-1]+p[i-1]*p[i];
  
  double solve(pnt lp1,pnt lp2)
  {
    int A,B,l,r,pl,pr;
    tmp=lp2-lp1;
    A=lower_bound(agl,agl+N,make_pair(atan2(tmp.y,tmp.x),-1))-agl;
    tmp=lp1-lp2;
    B=lower_bound(agl,agl+N,make_pair(atan2(tmp.y,tmp.x),-1))-agl;  //寻找斜率最相近的边 
    A=agl[A].second,B=agl[B].second;
    
    if (A==N) A=0;
    if (B==N) B=0; 
  
    if ( sgn( ((p[A]-lp1)*(lp2-lp1))*((p[B]-lp1)*(lp2-lp1)) )>=0 ) return 0; //与凸包无公共点 
  
    if (sgn(((p[A]-lp1)*(lp2-lp1)))<0) swap(A,B);
  
    l=A,r=B; if (l>r) r=r+N; --r;
    
    while (l<=r)  //二分求交点 
    {
      int mid=(l+r)/2;
      if ( sgn( (p[mid]-lp1)*(lp2-lp1) ) >=0 ) pl=mid,l=mid+1; else r=mid-1;
    }
  
    l=B,r=A; if (l>r) r=r+N; --r;
    while (l<=r)
    {
      int mid=(l+r)/2;
      if ( sgn( (p[mid]-lp1)*(lp2-lp1) ) <=0 ) pr=mid,l=mid+1; else r=mid-1;
    }
  
    pl%=N; pr%=N;
    if (pr<pl) pr+=N;
    area=sum[pr]-sum[pl];
  
    pA=get_intersection(p[pl],p[(pl+1)%(2*N)],lp1,lp2);  //交点 
    pB=get_intersection(p[pr],p[(pr+1)%(2*N)],lp1,lp2);
  
    area=area+pA*p[pl]+p[pr]*pB+pB*pA;
    
  //   面积为area/2和(total-area)/2 
    return min(area,total-area)/2;
  }
