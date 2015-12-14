bool PntInSeg(const pnt &p, const pnt &a, const pnt &b) 
{
    if ( a == b) return p == a;
     
   //if ( sgn(( p - a ) * ( p)) == 0)
        if ( sgn(( a - p ) ^ ( b - p )) <= 0) 
             return 1;
        else 
             return 0; 
   /* else 
        return 0;*/
}

pnt get_perpendicular(const pnt &p, const pnt &a, const pnt &b)
{
    double d = (p - a) * (b - a) / (a - b).len();
    return p + ( b - a ).rotate_left().trunc(d);
}

