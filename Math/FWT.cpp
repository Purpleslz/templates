#include<bits/stdc++.h>
using namespace std;
typedef long long Int;
const int M=1e9+7,rev2=(M+1)>>1;
int n,m;
int a[2050];
inline void upd(int &x,int y){x+=y;if(x>=M)x-=M;}
int powmod(int x,int y)
{
	int ret=1;
	while(y)
	{
		if(y&1)ret=ret*(Int)x%M;
		x=x*(Int)x%M;
		y>>=1;
	}return ret;
}
void fwt(int *a,int N,int flag=1)
{
	for(int len=1;len<N;len<<=1)
		for(int i=0;i<N;i+=len<<1)
		{
			for(int j=i;j<i+len;j++)
			{
				int u=a[j]-a[j+len],v=a[j]+a[j+len];
				if(flag<0)a[j]=v*(Int)rev2%M,a[j+len]=u*(Int)rev2%M;
				else a[j]=u%M,a[j+len]=v%M;
			}
		}
}
int solve(int L,int R)
{
	int N=2048;
	for(int i=0;i<N;i++)a[i]=i>=L&&i<=R;
	fwt(a,N);
	for(int i=0;i<N;i++)a[i]=powmod(a[i],n);
	fwt(a,N,-1);
	if(a[0]<0)a[0]+=M;
	return a[0];  //取值在[L,R]中的n个数异或得0方案数 
}
int main()
{
	int l,r;
	while(scanf("%d%d%d%d",&n,&m,&l,&r)!=EOF)
	{
		n=n<<1|1;
		int ans=0;
		for(int x=l;x<=r;x++)
		{
			upd(ans,solve(x,x+m));
		}
		printf("%d\n",ans);
	}
}
