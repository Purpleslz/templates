const double eps=1e-7;

//符号 
inline int sgn(double x) { if (fabs(x)<eps) return 0; else if (x>eps) return 1; else return -1; }
//符号 end 

double trim(double d, double l = 1.0) {
 return d > l ? l : (d < -l ? -l : d);
}
