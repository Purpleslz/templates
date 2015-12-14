/*   1 + 1/2 + 1/3 + 1/4 + .... + 1/n = ln(n+1) + r
     r 是欧拉常数 约为0.57721556649
     
     用的时候建议暴力算欧拉常数                      */
     
   double sum = 0;
   for (int i = 1;i <= 1000000; ++i) sum += 1.0/(double)i;
  
   double r = sum - ln(n+1);  

