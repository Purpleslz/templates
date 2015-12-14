void calcprefix(char *s,int len)
{
  prefix[1] = 0;
  
  for (int i=2,j=0;i<=len;++i)
  {
    while(j && s[j+1]!=s[i]) j = prefix[j];
    if (s[j+1] == s[i])  ++j;
    prefix[i] = j; 
  } 
}
