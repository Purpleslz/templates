//性质1：满足堆的性质
//性质2：左子节点的距离不小于右子节点的距离
//性质3: i的左右子树也是左偏树 
//距离：i到i子树中最近的没有2个非空子节点的节点路径长度

int merge(int a,int b)
{
  if (a==0 || b==0) return a+b;
  if (tree[a].key < tree[b].key) swap(a,b);
  tree[a].rch = merge(tree[a].rch,b);
  if (tree[ tree[a].lch ].dist < tree[ tree[a].rch ].dist) swap(tree[a].lch,tree[a].rch); //斜堆删掉这句话 
  tree[a].dist = tree[ tree[a].rch ].dist + 1;//斜堆删掉这句话
  
  //斜堆每次都交换左右子树以保证复杂度
  //swap(tree[a].lch,tree[a].rch); 
  return a;
}
