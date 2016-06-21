struct HASH_TABLE
{
  map<long long,int> h;
  HASH_TABLE() { h.clear(); }
  void clear() { h.clear(); }
  void insert(long long x,int y) { h[x] = y; }
  int get(long long x)
  {
    if (h.find(x) == h.end()) return -1; else return h[x];
  }
}htable;

/*
const int pr = 100003;

struct HASH_TABLE
{
  int g[pr],next[MAXN],tot;
  long long num[MAXN],id[MAXN];
  void clear() { memset(g,0,sizeof(g)); tot=0;}
  void insert(long long x,int y)
  {
    for (int i=g[x%pr];i;i=next[i])
      if (num[i]==x)
      {
        id[i]=min(id[i],(long long)y);
        return ;
      }
    ++tot; num[tot]=x; id[tot]=y; next[tot]=g[x%pr]; g[x%pr]=tot;
  }
  int get(long long x)
  {
    for (int i=g[x%pr];i;i=next[i]) if (num[i]==x) return id[i];
    return -1;
  }
}htable;
*/

int ext_bsgs(long long a,long long b,long long c)
{
  for (int i=0;i<64;++i) if (pow(a,i,c) == b) return i;

  long long d,D=1,cnt = 0;
  while ( (d = gcd(a,c)) != 1 )
  {
    if (b % d) return -1;
    b/=d; c/=d;
    D = D*a/d%c;  
    ++cnt;
  } 
  
  int size = (int) sqrt(c) + 2;
  
  htable.clear();
  
  long long base = 1,_base = 1;
  long long tmp = solve_mod_linear(a,1,c);
  for (int i=0;i<size;++i) 
  {
    htable.insert(b*base%c,i);
    base = base * tmp % c;
    _base = _base * a % c;
  }
  
  for (int i=0;i<size;++i)
  {
    int tmp;
    if ((tmp = htable.get(D)) != -1) return i*size + tmp + cnt;
    D = D * _base % c;
  }
  
  return -1;
}
