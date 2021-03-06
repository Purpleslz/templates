
令h(0)=1,h(1)=1，catalan数满足递推式[1]  ：
h(n)= h(0)*h(n-1)+h(1)*h(n-2) + ... + h(n-1)h(0) (n>=2)
例如：h(2)=h(0)*h(1)+h(1)*h(0)=1*1+1*1=2
h(3)=h(0)*h(2)+h(1)*h(1)+h(2)*h(0)=1*2+1*1+2*1=5
另类递推式[2]  ：
h(n)=h(n-1)*(4*n-2)/(n+1);
递推关系的解为：
h(n)=C(2n,n)/(n+1) (n=0,1,2,...)
递推关系的另类解为：
h(n)=c(2n,n)-c(2n,n-1)(n=0,1,2,...)

（1）括号化

矩阵连乘： P=a1×a2×a3×……×an，依据乘法结合律，不改变其顺序，只用括号表示成对的乘积，试问有几种括号化的方案？(h(n-1)种)[3] 

（2）凸多边形三角划分

在一个凸多边形中，通过若干条互不相交的对角线，把这个多边形划分成了若干个三角形。
任务是键盘上输入凸多边形的边数n，求不同划分的方案数f（n）。比如当n=6时，f（6）=14。[6]  


（3）给定节点组成二叉树

给定N个节点，能构成多少种不同的二叉树？[7] 
（能构成h（N）个）
（这个公式的下标是从h(0)=1开始的）

（4）
出栈次序

一个栈(无穷大)的进栈序列为1，2，3，…，n，有多少个不同的出栈序列?[4-5]  

（5）问题1的描述：有n个1和m个-1（n>m），共n+m个数排成一列，满足对所有0<=k<=n+m的前k个数的部分和Sk > 0的排列数。
 问题等价为在一个格点阵列中，从（0，0）点走到（n，m）点且不经过对角线x==y的方法数（x > y）。
考虑情况I：第一步走到（0，1），这样从（0，1）走到（n，m）无论如何也要经过x==y的点，这样的方法数为(( n+m-1,m-1 ));
考虑情况II：第一步走到（1，0），又有两种可能：
a . 不经过x==y的点；（所要求的情况）
b . 经过x==y的点，我们构造情况II.b和情况I的一一映射，说明II.b和I的方法数是一样的。
设第一次经过x==y的点是（x1，y1），将（0，0）到（x1，y1）的路径沿对角线翻折，于是唯一对应情况I的一种路径；
对于情况I的一条路径，假设其与对角线的第一个焦点是（x2，y2），将（0，0）和（x2，y2）之间的路径沿对角线翻折，唯一对应情况II.b的一条路径。
问题的解就是总的路径数 ((n+m, m)) - 情况I的路径数 - 情况II.b的路径数。
((n+m , m)) - 2*((n+m-1, m-1))
或：((n+m-1 , m)) - ((n+m-1 , m-1))
问题2的描述：有n个1和m个-1（n>=m），共n+m个数排成一列，满足对所有0<=k<=n+m的前k个数的部分和Sk >= 0的排列数。
（和问题1不同之处在于此处部分和可以为0，这也是更常见的情况） 
问题等价为在一个格点阵列中，从（0，0）点走到（n，m）点且不穿过对角线x==y的方法数（可以走到x==y的点）。
把（n，m）点变换到（n+1，m）点，问题变成了问题1。
方法数为：
((n+m+1, m)) - 2*((n+m+1-1, m-1))
或：((n+m+1-1, m)) - ((n+m+1-1, m-1))


