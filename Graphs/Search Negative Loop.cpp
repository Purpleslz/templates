

//若存在负环 则存在一个点 使得经过的边权和一直非正 
//本质是栈spfa 

void dfs(int now)
{
  v[now] = 1;
  for (int i=g[now];i;i=next[i])
    if (dist[num[i]]>dist[now] + cost[i])
    {
      if (v[num[i]]) { flag = 0; return ;}
      dist[num[i]] = dist[now] + cost[i];
      dfs(num[i]);
      if (!flag) return ;
    }
  v[now] = 0;
}

bool work()
{
  memset(dist,0,sizeof(dist)); //距离全部设置为0 
  memset(v,0,sizeof(v));       //标记数组 
  for (int i=1;i<=N;++i) if (flag) dfs(i);
  return flag;
}
