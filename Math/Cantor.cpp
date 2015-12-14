
long long Cantor(int *buf)
{
  long long result=0;
  for(int i = 1;i < N; ++i)  
  {
    int counted=0;
    for(int j = i + 1; j <= N; ++j)
      if(buf[i]>buf[j])
        ++counted;
    result = result + counted * fac[N - i];
  }
  return result + 1;
}

