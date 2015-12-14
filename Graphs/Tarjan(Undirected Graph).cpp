
int TIME;

int dfn[MAXN],low[MAXN];

void tarjan(int now ,int p) // p 父亲边 
{
  dfn[now] = low[now] = ++TIME;
  
  for (int i=g[now];i;i=next[i])
    if (i != (p^1) )
    {
      if (!dfn[num[i]])
      {
        tarjan(num[i],i);
        
        if (low[num[i]] > dfn[ now] ) {} //割边 
        if (low[num[i]] >= dfn[now] ) {} //当now不为树根 且满足此条件时为割点 
        low[now] = min( low[num[i]] ,low[now]);
      }
      else low[now] = min( low[now], dfn[num[i]]);
    }

}

//若树根有多于一棵子树也为割点 

//边双连通分量：删除所有桥 其余联通的点和边属于一个边双联通分量

//点双连通分量: 建立一个栈，存储当前双连通分量，每找到一条树枝边或后向边，就把这条边加入
//栈中如果遇到割点dfn(u)<=low(v)，同时把边从栈顶一个个取出，直到遇到边(u,v)，取出的边
//及其关联的点组成一个点双连通分量。割点可以属于多个点双连通分量，其余点和每条边只属于
//且属于一个点双连通分量。 
