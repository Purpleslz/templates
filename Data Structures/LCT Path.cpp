
struct LCT
{
  int child[2],fa,v,rev,size,sum,MIN,id;
  
#define lch(x) SPLAY[x].child[0]
#define rch(x) SPLAY[x].child[1]
#define f(x) SPLAY[x].fa
#define id(x) SPLAY[x].id
#define v(x) SPLAY[x].v
#define rev(x) SPLAY[x].rev
#define MIN(x) SPLAY[x].MIN
#define siz(x) SPLAY[x].size

}SPLAY[2*N + 10];

inline bool isroot(int x) { return (lch(f(x))!=x) && (rch(f(x))!=x);  } //是否为根

inline void update(int x)                                         //更新节点信息 
{
  if (x)
  {
    siz(x)=siz(lch(x))+siz(rch(x))+1;
    MIN(x) = x;
    if ( v( MIN( lch(x) ) ) < v( MIN(x) ) ) MIN(x) = MIN( lch(x) );
    if ( v( MIN( rch(x) ) ) < v( MIN(x) ) ) MIN(x) = MIN( rch(x) );
  }
} 

inline void setc(int x,int y,int k) { SPLAY[f(y)=x].child[k]=y; }  //设定儿子 k=0为左 k=1为右 

inline void reverser(int now) { swap(lch(now),rch(now)); rev(now)^=1; }

inline void push(int x)
{
  if (rev(x))
  {
    if (lch(x)) reverser(lch(x));
    if (rch(x)) reverser(rch(x));
    rev(x)=0;
  }
}

void rotate(int x)
{
  push(f(x));push(x);
  int y=f(x),p=rch(y)==x;
  if (isroot(y)) f(x)=f(y); else setc(f(y),x,rch(f(y))==y);
  setc(y,SPLAY[x].child[p^1],p); setc(x,y,p^1);
  update(y);
}

void splay(int x)
{
  push(x);
  for (;!isroot(x);rotate(x))
    if (!isroot(f(x)))
      if ((lch(f(x))==x) ^ (lch(f(f(x)))==f(x))) rotate(x); else rotate(f(x));
  update(x);
}

void access(int x)
{
  for (int tmp=0,y=x;y;y=f(y))
  {
    splay(y);
    setc(y,tmp,1);
    //rch(y) = tmp;                                          ....if.... 
    update(tmp=y);
  }
}

inline void evert(int x) { access(x); splay(x);reverser(x); }

void LINK(int x,int y) { evert(x); f(x)=y; }

void CUT(int x,int y) { evert(x); access(y); splay(y); f(x)=lch(y)=0; update(y); }

int query(int x,int y)
{
  evert(x);
  access(y);
  splay(x);
  
  return MIN(x);
}

int findroot(int x)
{
  access(x); splay(x); 
  for (push(x);lch(x);push(x)) x = lch(x);
  return x;
}

//应初始化各节点信息 以及0节点信息 


