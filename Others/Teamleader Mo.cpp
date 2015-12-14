
/* 要求离线 分块 按照询问区间 左端点为第一关键字 右端点为第二关键字 排序 
 * 一次只修改一个点 复杂度 O(n * sqrt(n) * 单次修改复杂度 ) */
 
const int LEN = 200; //块大小 尽量为sqrt(N) 

struct SEG { int x,y,id,Kx,Ky; }seg[MAXN];
 
inline bool cmp(const SEG &A,const SEG &B) { if (A.Kx!=B.Kx) return A.Kx<B.Kx; else return A.y<B.y;  } 


int main()
{
  for (int i=1;i<=m;++i)
  {
    scanf("%d%d",&seg[i].x,&seg[i].y);
    seg[i].Kx=seg[i].x/LEN;
    seg[i].Ky=seg[i].y/LEN;
    seg[i].id=i;
  }
  
  for (int i=seg[1].x;i<=seg[1].y;++i) ; //手做第一个询问 并计算答案 
  
  L = seg[1].x; R = seg[1].y;
  
  for (int now=2;now<=m;++now)
  {
    for (int tmp=L;tmp<seg[now].x;++tmp) del(tmp); 
    for (int tmp=L-1;tmp>=seg[now].x;--tmp) add(tmp);
    for (int tmp=R;tmp>seg[now].y;--tmp) del(tmp);
    for (int tmp=R+1;tmp<=seg[now].y;++tmp) add(tmp);
    L=seg[now].x; R=seg[now].y;
    //统计答案 
  }

} 

