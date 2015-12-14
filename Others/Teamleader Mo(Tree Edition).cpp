
/* 根据DFS序分块 */
/* 需要修改时 把时间当做第三维 暴力修改 */ 

  sort(Q+1,Q+M+1,cmp);
  
  int L = root,R = root;
  
  for (int i=1,LCA;i<=M;++i)
  {
    int a = Q[i].x, b = Q[i].y;
    
    //cout << a << " " << b << " " << Q[i].a << " " << Q[i].b << " " << Q[i].id << endl;
    
    LCA = getlca(a,L);
    
    for (int tmp = L; tmp != LCA; tmp = fa[tmp][0]) change( tmp );
    for (int tmp = a; tmp != LCA; tmp = fa[tmp][0]) change( tmp );
    
    LCA = getlca(b,R);
    
    for (int tmp = R; tmp != LCA; tmp = fa[tmp][0]) change( tmp );
    for (int tmp = b; tmp != LCA; tmp = fa[tmp][0]) change( tmp );
    
    LCA = getlca(a,b);
    
    change( LCA );
  
    //更新答案 
    
    L = a; R = b;
    change( LCA );
  }
