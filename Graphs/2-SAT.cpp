/*
 * Author:  vawait
 * Created Time:  2014年07月21日 星期一 14时03分38秒
 * File Name:URAL 1382 Game with Cards
 */
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define red(i, a, b) for (int i = (a); i >= (b); --i)
#define clr( x , y ) memset(x,y,sizeof(x))
#define sqr(x) ((x) * (x))
#define mp make_pair
#define pb push_back
#define db pop_back
typedef long long lint;
int n , t , A[1100] , B[1100] , C[1100] , f[1100];
int s , a[1100][3] , q[1100];
 
struct nodd
{
    int y , b , n;
} b[4000010];
 
void add(int x,int b1,int y,int b2)
{
    b[++t].y = y; b[t].b = b2;
    b[t].n = a[x][b1]; a[x][b1] = t;
}
 
void init()
{
    t = 0;
    rep(i,1,n) {
        scanf("%d%d%d",&A[i],&B[i],&C[i]);
        a[i][1] = a[i][2] = 0;
        f[i] = 0;
    }
    rep(i,1,n)
        rep(j,1+i,n) {
            if ( A[j] == A[i] ) {
                add( i , 1 , j , 1 );
                add( j , 1 , i , 1 );
            }
            if ( ( B[j] == i ) != ( C[j] == A[i] ) ) {
                add( i , 1 , j , 2 );
                add( j , 2 , i , 1 );
            }
            if ( ( B[i] == j ) != ( C[i] == A[j] ) ) {
                add( i , 2 , j , 1 );
                add( j , 1 , i , 2 );
            }
            if ( ( B[j] == B[i] ) != ( C[j] == C[i] ) ) {
                add( i , 2 , j , 2 );
                add( j , 2 , i , 2 );
            }
        }
}
 
bool dfs(int x,int v)
{
    q[++s] = x;
    f[x] = v;
    for (int p = a[x][v]; p; p = b[p].n ) {
        int y = b[p].y;
        if ( !f[y] && !dfs( y , 3 - b[p].b ) ) return 0;
        if ( f[y] == b[p].b ) return 0;
    }
    return 1;
}
 
bool ok(int x,int v)
{
    s = 0;
    if ( dfs( x , v ) ) return 1;
    while ( s ) f[q[s--]] = 0;
    return 0;
}
 
void work()
{
    rep(i,1,n) if ( !f[i] ) {
        if ( !ok( i , 1 ) ) ok( i , 2 );
    }
    rep(i,1,n-1) printf("%d ",f[i]);
    printf("%d\n",f[n]);
}
 
int main()
{
    while ( cin >> n ) {
        init();
        work();
        return 0;
    }
}
