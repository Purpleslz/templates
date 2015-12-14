
for (int i = 1; i <= N ; ++i)
{
  if (!v[i]) prime[ ++tot ] = i; //质数 
  for (int j = 1;j <= tot; ++j)
  {
    if (i * prime[j] > N) break;
    v[ i * prime[j] ] = 1;
    if (i % prime[j] == 0) break;  //其他 
    else {} //square-free number 
  }
}
