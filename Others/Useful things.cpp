1. 在树上一点i， 有相同的几率走相同的任何一条边。求从s走到t的期望长度。
   假设t是根。
   f(s) = f( parent(s) ) + 2 * size(s) - 1
  
2. |x1 - x2| + |y1 - y2| = max( | (x1 + y1) - (x2 + y2) |, | (x1 - y1) - (x2 - y2) |)


3. [ f(l) + 4 * f(mid) + f(r) ] * (r - l) / 6

4. 补集转化

5. 数论 积性函数 2个积性函数的狄利克雷卷积也是积性函数 积性函数的幂有可能也是积性函数
