inline bool inCircle(const pnt &a, const Circle &cir)
{
    return sgn( cir.r - (a - cir.c).len() ) > 0;
}
