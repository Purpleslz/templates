/* 寻找满足 A[i] + B[j] == W[i][j] 的边构成的子图是否存在完备匹配 */
/* 修改顶标以满足 */ 


const int maxn=100;
int W[maxn][maxn],n;
int Lx[maxn],Ly[maxn];
int left[maxn];
bool S[maxn],T[maxn];
bool match(int i)
{
	S[i]=true;
	for (int j=1;j<=n;j++) if (Lx[i]+Ly[j]==W[i][j]&&!T[j])
	{
		T[j]=1;
		if (!left[j]||match(left[j]))
		{
			left[j]=i;
			return true;
		}
	}
	return false;
}
void update()
{
	int a=1<<30;
	for (int i=1;i<=n;i++) if (S[i])
	for (int j=1;j<=n;j++) if (!T[i]) a=min(a,Lx[i]+Ly[j]-W[i][j]);
	for (int i=1;i<=n;i++)
	{
		if (S[i]) Lx[i]-=a;
		if (T[i]) Ly[i]+=a;
	}
}
void KM()
{
	for (int i=1;i<=n;i++)
	{
		left[i]=Lx[i]=Ly[i]=0;
		for (int j=1;j<=n;j++) Lx[i]=max(Lx[i],W[i][j]);
	}
	for (int i=1;i<=n;i++)
	{
		for(;;)
		{
			for(int j=1;j<=n;j++) S[j]=T[j]=0;
			if (match(i)) break; else update();
		}
	}
}

