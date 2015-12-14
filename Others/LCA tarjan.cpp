/*
 *算法引入:
 *树上两点的最近公共祖先;
 *对于有根树的两个结点u,v,最近公共祖先LCA(T,u,v)表示一个结点x,满足x是u,v的祖先且x的深度尽可能大;
 *对于x来说,从u到v的路径一定经过点x;
 *
 *算法思想:
 *Tarjan_LCA离线算法;
 *Tarjan算法基于dfs的框架,对于新搜到的一个结点,首先创建由这个结点构成的集合,再对当前结点的每个子树进行搜索;
 *每搜索完一棵子树,则可确定子树内的LCA询问都已解决,其他的LCA询问的结果必然在这个子树之外;
 *这时把子树所形成的集合与当前结点的集合合并,并将当前结点设为这个集合的祖先;
 *之后继续搜索下一棵子树,直到当前结点的所有子树搜完;
 *
 *这时把当前结点也设为已被检查过的,同时可以处理有关当前结点的LCA询问;
 *如果有一个从当前结点到结点v的询问,且v已经被检查过;
 *则由于进行的是dfs,当前结点与v的最近公共祖先一定还没有被检查;
 *而这个最近公共祖先的包含v的子树一定已经搜索过了,那么这个最近公共祖先一定是v所在集合的祖先;
 *
 *算法步骤:
 *对于每一个结点:
 *(1)建立以u为代表元素的集合;
 *(2)遍历与u相连的结点v,如果没有被访问过,对于v使用Tarjan_LCA算法,结束后将v的集合并入u的集合;
 *(3)对于与u有关的询问(u,v),如果v被访问过,则结果就是v所在集合的代表元素;
 *
 *算法示例:
 *HDU2586(How far away?)
 *
 *题目大意:
 *求树上任两点间的距离;
 *
 *算法思想:
 *先dfs一遍,求出到根节点的dis;
 *对于某个询问,求u和v的lca,然后res[i]=d[u]+d[v]-2*d[lca(u,v)];
 *
**/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int N=40004;
const int M=202;

typedef long long LL;

int p[N];
int head[N*2];
int qhead[N];//询问
bool visit[N];

LL d[N];
LL res[M];

struct node
{
    int to;
    int w;
    int next;
    int lca;
};

node edge[N*2];
node qedge[M];//询问边

int n,m;
int cnt1,cnt2;

inline void Addedge(int u,int v,int w)
{
    edge[cnt1].w=w;
    edge[cnt1].to=v;
    edge[cnt1].next=head[u];
    head[u]=cnt1;
    cnt1++;

    edge[cnt1].w=w;
    edge[cnt1].to=u;
    edge[cnt1].next=head[v];
    head[v]=cnt1;
    cnt1++;
}

inline void Addqedge(int u,int v)
{
    qedge[cnt2].to=v;
    qedge[cnt2].next=qhead[u];
    qhead[u]=cnt2;
    cnt2++;

    /*qedge[cnt2].to=u;
    qedge[cnt2].next=qhead[v];
    qhead[v]=cnt2;
    cnt2++;*/
}

void dfs(int u,int f,LL w)
{
    d[u]=w;
    for(int i=head[u]; i!=-1; i=edge[i].next)
    {
        int v=edge[i].to;
        if(v==f)
            continue;
        dfs(v,u,w+edge[i].w);
    }
}

int Find(int x)
{
    if(p[x]!=x)
        p[x]=Find(p[x]);
    return p[x];
}

void Tarjan_LCA(int u)//离线LCA算法
{
    p[u]=u;
    visit[u]=1;
    for(int i=head[u]; i!=-1; i=edge[i].next)
    {
        if(!visit[edge[i].to])
        {
            Tarjan_LCA(edge[i].to);
            p[edge[i].to]=u;
        }
    }

    for(int i=qhead[u]; i!=-1; i=qedge[i].next)
    {
        if(visit[qedge[i].to])
        {
            qedge[i].lca=Find(qedge[i].to);
            //printf("%d和%d的最近公共祖先为: %d\n",u,qedge[i].to,qedge[i].lca);
            res[i]=d[u]+d[qedge[i].to]-2*d[qedge[i].lca];
           // qedge[i+1].lca=qedge[i].lca;
        }
    }
}

void Solve()
{
    for(int i=0; i<=n; i++)
        p[i]=i;
    memset(head,-1,sizeof(head));
    memset(qhead,-1,sizeof(qhead));
    memset(visit,0,sizeof(visit));
    cnt1=cnt2=0;
    int u,v,w;
    for(int i=1; i<n; i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        Addedge(u,v,w);
    }

    for(int i=0; i<m; i++)
    {
        scanf("%d%d",&u,&v);
        Addqedge(u,v);
    }

    dfs(1,0,0);
    Tarjan_LCA(1);
}

int main()
{
    //freopen("C:\\Users\\Administrator\\Desktop\\kd.txt","r",stdin);
    int tcase;
    scanf("%d",&tcase);
    while(tcase--)
    {
        scanf("%d%d",&n,&m);
        Solve();
        for(int i=0; i<m; i++)
            printf("%lld\n",res[i]);
    }
    return 0;
}

