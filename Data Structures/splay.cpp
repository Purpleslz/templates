/* SPLAY 维护凸壳 */
/* JSOI 2008 Blue Mary 开公司 */ 
 
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const double eps=1e-9;
const int MAXN=100010,oo=100000000;

#define lch(x) SPLAY[x].CHILD[0]
#define rch(x) SPLAY[x].CHILD[1]
#define f(x) SPLAY[x].FATHER
#define v1(x) SPLAY[x].VAL1
#define v2(x) SPLAY[x].VAL2
#define size(x) SPLAY[x].SIZE

struct SPLAYNODE { int FATHER,SIZE,CHILD[2]; double VAL1,VAL2; } SPLAY[MAXN];

double A,B;
int N,tot,root;
char str[10];

inline int dcmp(double A) { if (fabs(A)<eps) return 0; else if (A<0) return -1; else return 1; }

inline void read(int &x)
{
  char ch;
  while (ch=getchar(),ch>'9' || ch<'0') ;
  x=ch-48;
  while (ch=getchar(),ch<='9' && ch>='0') x=x*10+ch-48;
}

void ins(int &now,int v1,int v2,int father)
{
  if (now==0)
  {
    now=++tot;
    lch(now)=rch(now)=0;
    v1(now)=v1; v2(now)=v2;
    f(now)=father;
  }
  else if (dcmp(v1-v1(now))<0 || (dcmp(v1-v1(now))==0 && dcmp(v2-v2(now))<=0)) ins(lch(now),v1,v2,now);
  else ins(rch(now),v1,v2,now);
}

inline void update(int now) { if (now) size(now)=size(lch(now))+size(rch(now))+1; }

inline int getkth(int now,int K)
{
  while (size(lch(now))+1!=K)
    if (size(lch(now))+1>K) now=lch(now); else { K-=size(lch(now))+1; now=rch(now); }
  return now;
}

inline void rotate(int x)
{
  int y=f(x),p,q;
  if (lch(f(y))==y) lch(f(y))=x; else rch(f(y))=x;
  p=rch(y)==x; q=1-p;
  f(x)=f(y); f(y)=x; f(SPLAY[x].CHILD[q])=y;
  SPLAY[y].CHILD[p]=SPLAY[x].CHILD[q]; SPLAY[x].CHILD[q]=y;
  update(y);
}

void splay(int now,int spd,int &root)
{
  for (;f(now)!=spd;rotate(now))
    if (f(f(now))!=spd)
      if ((lch(f(now))==now) ^ (lch(f(f(now)))==f(now))) rotate(now); else rotate(f(now));
  update(now);
  if (!spd) root=now;
}

int pred(int now)
{
  if (now==0) return 0;
  if (lch(now))
  {
    for (now=lch(now);rch(now);now=rch(now));
    return now;
  }
  else for (;f(now);now=f(now)) if (now==rch(f(now))) return f(now);
  return 0;
}

int succ(int now)
{
  if (now==0) return 0;
  if (rch(now))
  {
    for (now=rch(now);lch(now);now=lch(now));
    return now;
  }
  else for (;f(now);now=f(now)) if (now==lch(f(now))) return f(now);
  return 0;
}

inline void del(int now)
{
//  cout << "deleted " << now << endl;
  splay(now,0,root);
  if (lch(now))
  {
    splay(getkth(lch(now),size(lch(now))),now,root);
    root=lch(now);
    f(root)=0;
    rch(root)=rch(now);
    if (rch(now)) f(rch(now))=root;
    update(root);
  }
  else if (rch(now)) { root=rch(now); f(root)=0; }
  else root=0;
}

inline int cross(int A,int B,int C) { return dcmp((v1(B)-v1(A)) * (v2(C) - v2(A)) - (v1(C)-v1(A)) * (v2(B)-v2(A))); }

void insert_node(int A,int B)
{
  ins(root,B,A,0);
  splay(tot,0,root);
  
  int now=tot,X,Y;

  X=pred(now);
  if (X && v1(X)==v1(now)) del(X);
  X=succ(now);
  if (X && v1(X)==v1(now)) { del(now); return ;}

  X=pred(now); Y=succ(now);
  if (X && Y && cross(X,now,Y)>0)
  {
    del(now);
    return ;
  }
  
  X = pred(now);
  for (Y=pred(X);Y;X=Y,Y=pred(Y)) if (cross(Y,X,now)>=0) del(X); else break;
  X = succ(now);
  for (Y=succ(X);Y;X=Y,Y=succ(Y)) if (cross(now,X,Y)>=0) del(X); else break;
}

inline int ask(int V)
{
  int now=root,ans=0;
  while (now)
  {
    //cout << now << endl;
    int X=pred(now);
    if (!X) { ans=now; now=rch(now); }
    else
      if ( -(v2(now)-v2(X))/(v1(now)-v1(X))<=V )
      {
        ans=now;
        now=rch(now);
      } else now=lch(now);
  }
  double res=v1(ans)*V+v2(ans);
  return (int)(res/100);
}

int main(void)
{
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  insert_node(0,0);
  read(N);
  while (N--)
  {
    scanf("%s",str);
    if (str[0]=='Q')
    {
      int A;
      read(A);
      printf("%d\n",ask(A-1));
    }
    else
    {
      scanf("%lf%lf",&A,&B);
      insert_node(A,B);
    }
  }
  return 0;
}
