
/* 求环形最大路径 且至少为4格 */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
  
const int MOD=69997,MAX=15;
int n,m,tot; 
int p[20],c[20],t[2],use[20],pre=1,now=0; 
int q[2][1000010][2],ans=-100000000,pa[20];
int g[70000],next[1000010];
 
int change(int state,int a,int b,int pos)
{
  for (int i=0;i<=m;++i) c[i]=(state>>p[i]) & 7;
  memset(use,0,sizeof(use));int tot=0;
  for (int i=0;i<=m;++i)
  {
    if (!c[i]) continue;
    if (c[i]==a || c[i]==b) {if (!use[a] && !use[b]) use[a]=use[b]=++tot;}
    else if (!use[c[i]]) use[c[i]]=++tot;
    c[i]=use[c[i]];
  }
  c[pos]=c[pos-1]=0;
  state=0;
  for (int i=m;i>=0;--i)state=(state<<3)+c[i];
  return state;
}
 
void add(int state,int cnt)
{
  int NOW=state%MOD;
  for (int i=g[NOW];i;i=next[i])
    if(q[now][i][0]==state)
    {
      q[now][i][1]=max(q[now][i][1],cnt);
      return; 
    }
  ++t[now];
  q[now][t[now]][0]=state;
  q[now][t[now]][1]=cnt;
  next[t[now]]=g[NOW];
  g[NOW]=t[now];
}
 
int main(void) 
{
  scanf("%d%d",&n,&m);
  pa[0]=1;
  for (int i=1;i<20;++i) p[i]=i*3,pa[i]=pa[i-1]*8;
  q[0][1][0]=0; q[0][1][1]=0; t[0]=1;
  for (int i=1;i<=n;++i)
  {
    for (int x,j=1;j<=m;++j)
    {
      tot=t[now];swap(pre,now);t[now]=0;
      scanf("%d",&x);
      memset(g,0,sizeof(g));
      for (int k=1;k<=tot;++k)
      {
        int state=q[pre][k][0];
        int ma=0,cnt=q[pre][k][1],le=(state>>p[j-1])&7,up=(state>>p[j])&7;
        for (int ll=0;ll<=m;++ll) ma=max((state >> p[ll]) & 7,ma);
        if (le && up)
        {
          if (le==up){ if (ma==1) ans=max(ans,cnt+x);} else add(change(state,le,up,j),cnt+x);
        }
        else if (!le && !up) 
        {
          if (j<m && i<n) add(change(state+7*pa[j-1]+7*pa[j],-1,-1,MAX),cnt+x);
          add(state,cnt);
        }
        else if (!le && up)
        {
          if (i<n)add(change(state-up*pa[j]+up*pa[j-1],-1,-1,MAX),cnt+x);
          if (j<m)add(state,cnt+x);
        }
        else
        {
          if (j<m)add(change(state-le*pa[j-1]+le*pa[j],-1,-1,MAX),cnt+x);
          if (i<n)add(state,cnt+x);
        }
      }
    }
    for (int j=1;j<=t[now];++j) q[now][j][0]<<=3;
  }
  printf("%d\n",ans);
  return 0; 
} 

