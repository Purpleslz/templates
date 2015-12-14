
const int MAXN=100010;

int N,M,color[MAXN],id[MAXN],root[MAXN],pos[MAXN],size[MAXN],head[MAXN];
int g[MAXN],next[MAXN*2],num[MAXN*2],edge_num,root_num,TOT;
int leaf[MAXN],leaf_num,father[MAXN],a[MAXN],depth[MAXN],X,Y,Z;
int L[MAXN*2],R[MAXN*2],lch[MAXN*2],rch[MAXN*2],cnt[MAXN*2],lazy[MAXN*2],lc[MAXN*2],rc[MAXN*2];
bool heavy[MAXN];
char str[20];

inline void read(int &x)
{
  char ch;
  while (ch=getchar(),ch<'0' || ch>'9');
  x=ch-48;
  while (ch=getchar(),ch>='0' && ch<='9') x=x*10+ch-48;
}

inline void addedge(int A,int B) { ++edge_num; num[edge_num]=B; next[edge_num]=g[A]; g[A]=edge_num; }

void dfs(int now)
{
  ++size[now];
  int id=0,MAX=0;
  for (int i=g[now];i;i=next[i])
    if (num[i]!=father[now])
    {
      father[num[i]]=now;
      depth[num[i]]=depth[now]+1;
      dfs(num[i]);
      size[now]+=size[num[i]];
      if (size[num[i]]>MAX) MAX=size[id=num[i]];
    }

  if (size[now]==1) leaf[++leaf_num]=now; else heavy[id]=1;
}

inline void update(int now)
{
  cnt[now]=cnt[lch[now]]+cnt[rch[now]]-(rc[lch[now]]==lc[rch[now]]);
  lc[now]=lc[lch[now]]; rc[now]=rc[rch[now]];
}

void make(int A,int B)
{
  int now=++TOT;
  L[now]=A; R[now]=B; lazy[now]=-1;
  if (A==B)
  {
    cnt[now]=1;
    lc[now]=rc[now]=color[a[A]];
  }
  else
  {
    lch[now]=TOT+1;
    make(A,(A+B)>>1);
    rch[now]=TOT+1;
    make(((A+B)>>1)+1,B);
    update(now);
  }
}

void init()
{
  for (int i=1;i<=leaf_num;++i)
  {
    int tot=0,now;
    for (now=leaf[i];heavy[now];now=father[now]) a[++tot]=now;
    a[++tot]=now;
    //for (int j=1;(j<<1)<=tot;++j) swap(a[j],a[tot-j+1]);
    reverse(a+1,a+tot+1); 
    ++root_num;
    for (int j=1;j<=tot;++j) id[a[j]]=root_num,pos[a[j]]=j;     //id为所属线段树编号 pos为在序列中的位置 
    head[root_num]=a[1];                                        //head为线段树第一节点的编号 
    root[root_num]=TOT+1;
    make(1,tot);
  }
}

inline void push(int now)
{
  lazy[lch[now]]=lazy[rch[now]]=lc[lch[now]]=rc[lch[now]]=lc[rch[now]]=rc[rch[now]]=lazy[now];
  cnt[lch[now]]=cnt[rch[now]]=1;
  lazy[now]=-1;
}

void modify(int now,int A,int B,int C)
{
  if (A<=L[now] && R[now]<=B)
  {
    lazy[now]=rc[now]=lc[now]=C;
    cnt[now]=1;
  }
  else
  {
    if (lazy[now]!=-1) push(now);
    if (A<L[rch[now]]) modify(lch[now],A,B,C);
    if (B>R[lch[now]]) modify(rch[now],A,B,C);
    update(now);
  }
}

void change(int A,int B,int C)
{
  while (id[A]!=id[B])                                    //更改深度较深的线段树 
  {
    if (depth[head[id[A]]]<depth[head[id[B]]]) swap(A,B);
    modify(root[id[A]],1,pos[A],C);
    A=father[head[id[A]]];
  }

  if (pos[A]>pos[B]) swap(A,B);                           //同一线段树内的更改 
  modify(root[id[A]],pos[A],pos[B],C);
}

int query(int now,int A,int B,int &t1,int &t2) //t1 t2为特定题目 
{
  if (A<=L[now] && R[now]<=B)
  {
    t2=rc[now];
    if (t1==-1) t1=lc[now];
    return cnt[now];
  }
  else
  {
    if (lazy[now]!=-1) push(now);
    int ans=0;
    if (A<L[rch[now]]) ans+=query(lch[now],A,B,t1,t2);
    if (B>R[lch[now]]) ans+=query(rch[now],A,B,t1,t2);
    if (A<L[rch[now]] && B>R[lch[now]] && rc[lch[now]]==lc[rch[now]]) --ans;
    return ans;
  }
}

void ask(int A,int B)
{
  /*int LC1=-1,LC2=-1,tmp1=-1,tmp2=-1,ans=0;*/ 

  //LC tmp 为特定题目的 

  while (id[A]!=id[B])
  {
    //tmp1=tmp2=-1;
    if (depth[head[id[A]]]<depth[head[id[B]]]) { swap(A,B); swap(LC1,LC2); }  //查询深度较深的线段树 
    ans+=query(root[id[A]],1,pos[A],tmp1,tmp2);
    //if (LC1==tmp2) --ans;
    //LC1=tmp1;
    A=father[head[id[A]]];
  }

  tmp1=tmp2=-1;
  if (pos[A]>pos[B]) { swap(A,B); /*swap(LC1,LC2);*/ }
  ans+=query(root[id[A]],pos[A],pos[B],tmp1,tmp2);
  /*if (LC2==tmp2) --ans;
  if (LC1==tmp1) --ans;*/ 
  printf("%d\n",ans);
}

int main(void)
{
  read(N); read(M);
  for (int i=1;i<=N;++i) read(color[i]);
  for (int i=1;i<N;++i)
  {
    read(X); read(Y);
    addedge(X,Y); addedge(Y,X);
  }

  depth[1]=1;
  dfs(1); //记录父亲 子树大小 重边 深度 叶子编号 

  init();

  while (M--)
  {
    scanf("%s",str);
    if (str[0]=='C')
    {
      read(X); read(Y); read(Z);
      change(X,Y,Z);
    }
    else
    {
      read(X); read(Y);
      ask(X,Y);
    }
  }

  return 0;
}

