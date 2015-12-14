//O(n)求每个字符最长回文串长度 
//只能求奇数长度的，所以每个字符2边加一个特殊字符 以及 在最开头加一个其他的特殊字符 避免越界
//rad[i]不包括自身 

  scanf("%s",str+1); 
  
  N = strlen(str+1);
  
  n = 1; a[1] = -2;
  
  for (int i=1;i<=N;++i)
  {
    a[++n] = -1;
    a[++n] = str[i];
  }
  a[++n] = -1;
  
  for (int i=1,k;i<=n;i+=k)
  {
    while (a[i - rad[i] - 1] == a[i + rad[i] +1 ]) ++rad[i];
    for (k=1;k<=rad[i];++k)
    {
      rad[i+k] = min(rad[i]-k,rad[i-k]);
      if (rad[i]-k == rad[i-k]) break;
    }
  }
