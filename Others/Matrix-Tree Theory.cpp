
 Matrix-Tree定理 (Kirchhoff矩阵-树定理) 
 G的度数矩阵D[G] 是一个n*n的矩阵 当i≠j时,D[i][j]=0；当i=j时，D[i][j]等于i的度数。 
 G的邻接矩阵A[G] 是一个n*n的矩阵 如果i,j之间有x条边直接相连，则A[i][j] = x ,否则为0。 
 G的Kirchhoff矩阵(也称为拉普拉斯算子)C[G]为C[G]=D[G]-A[G]
 G的所有不同的生成树的个数等于其Kirchhoff矩阵C[G]任何一个n-1阶主子式的行列式的绝对值。
 所谓n-1阶主子式，就是对于r(1≤r≤n)，将C[G]的第r行、第r列同时去掉后得到的新矩阵，用Cr[G]表示。
  
