
void calcsuff(char *s,int len)
{
  suff[1] = len;
  
  int p = 0,k = 2,L;
  
  for (int i = 2;i<=len;++i)
  {
    L = suff[i - k + 1];
    if (i+L<=p) suff[i] = L;
    else
    {
      int j = p - i + 1;
      if (j<1) j = 0;
      while (i+j<=len && s[j+1] == s[i+j]) ++j;
      suff[i] = j; k = i; 
      p = k + suff[k] - 1;
    }
  }
}   

int main()
{
  scanf("%s",a+1);
  scanf("%s",b+1);
  
  calcsuff(b,M);
  
  int p = 0,k = 1,L;
  for (int i=1;i<=N;++i)
  {
    L = suff[i-k+1];
    
    if (i+L<=p) extend[i] = L;
    else
    {
      int j = p - i + 1;
      if (j<1) j = 0;
      while ( i+j<=N && j+1<=M && a[i+j] == b[j+1])  ++j;
      extend[i] = j;  k = i; p = k + extend[k] -1;
    }
  }
  
}
