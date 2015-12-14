
int getfather(int u){//并查集找根  
    if(fa[u] == u) return u;  
    return find(fa[u]);  
}  

void set_union(int u,int v,int e)
{
    u = getfather(u), v = getfather(v);
    if(u == v) return ;
    if(size[u] < size[v]) swap(u,v);
    size[u] += size[v];                //合并两个并查集，并且记录操作的内容，以及加入的边
    fa[v] = u;
    stack[top] = v;                    //记录合并操作的点 
    ans[top++] = e;
}

void live_apart(int u) //分开两个并查集
{
    int f = fa[u];
    size[f] -= size[u];
    fa[u] = u;
}
