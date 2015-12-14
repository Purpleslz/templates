 
void calcsuff(char *s,int len)
{
  suff[0] = len;
  
  int p = -1,k = 1,L;
  
  for (int i = 1;i<len;++i)
  {
    L = suff[i - k];
    if (i+L<=p) suff[i] = L;
    else
    {
      int j = p - i + 1;
      if (j<0) j = 0;
      while (i+j<len && s[j] == s[i+j]) ++j;
      suff[i] = j; k = i; 
      p = k + suff[k] - 1;
    }
  }
}   

int main()
{
scanf("%s",a);
  scanf("%s",b);
  
  calcsuff(b,M);
  
  int p = -1,k = 0,L;
  for (int i=0;i<N;++i)
  {
    L = suff[i-k];
    
    if (i+L<=p) extend[i] = L;
    else
    {
      int j = p - i + 1;
      if (j<0) j = 0;
      while ( i+j<N && j<M && a[i+j] == b[j])  ++j;
      extend[i] = j;  k = i; p = k + extend[k] -1;
    }
  }
}

