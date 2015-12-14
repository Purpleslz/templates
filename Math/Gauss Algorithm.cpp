
void gauss(int n)
{
  for (int i=1;i<=n;++i)
  {
    for (int id=i+1;id<=n;++id)
      if (fabs(f[id][i])>fabs(f[i][i]))   //找绝对值最大主元 
        for (int k=i;k<=n+1;++k)
          swap(f[id][k],f[i][k]);
          
    for (int j=i+1;j<=n;++j)
    {
      double tmp=f[j][i]/f[i][i];       //若i行全为0有多解  若i行系数为0 无解 
      for (int k=i;k<=n+1;++k)
        f[j][k]-=f[i][k]*tmp;
    }
  }
  for (int i=n;i;--i)
  {
    ans[i]=f[i][n+1];
    for (int j=i+1;j<=n;++j) ans[i]-=ans[j]*f[i][j];
    ans[i]/=f[i][i];
  }
}

