int flow = 0;

void sap(int s, int sink, int cs)
{
	low[s]=cs;
	int now=s,i;
	while (dist[s]<lim) //lim是点数 
	{
		for (i=cur[now];i!=0;i=next[i])	if (c[i]>0 && dist[num[i]]+1==dist[now]) break;
		if (i)
		{
			cur[now]=pre[num[i]]=i;
			low[num[i]]=min(c[i],low[now]);
			now=num[i];
			if (now==sink)
			  for ( flow+=low[sink];now!=s;now=num[pre[now]^1])
			  {
			    c[pre[now]]-=low[sink];
          c[pre[now]^1]+=low[sink];
        } 
		}
		else
		{
			if (--h[dist[now]]==0) return ;
			dist[now] = lim ;  // lim是点数 
			for (i=g[now];i!=0;i=next[i])
				if (c[i]>0 && dist[num[i]]+1<dist[now])
					dist[now]=dist[num[i]]+1,cur[now]=i;
			++h[dist[now]];
			if (now!=s) now=num[pre[now]^1];
		}
	}
	return ;
}
