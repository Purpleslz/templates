pnt get_rad_mid(const pnt &a, const pnt &b, const Circle & cir)
{
            double cos_alpha = ( (a - cir.c) ^ (b - cir.c) ) / ( cir.r * cir.r );
            double sin_alpha = ( (a - cir.c) * (b - cir.c) ) / ( cir.r * cir.r ); 
                    
            double alpha = atan2( sin_alpha, cos_alpha );
                    
            if ( sgn(alpha) < 0) alpha += 2.0 * pi;
            
            return cir.c + ( a - cir.c).rotate_left(alpha / 2);
}

double get_angle(const pnt &a, const pnt &b, const Circle & cir)
{
            double cos_alpha = ( (a - cir.c) ^ (b - cir.c) ) / ( cir.r * cir.r );
            double sin_alpha = ( (a - cir.c) * (b - cir.c) ) / ( cir.r * cir.r ); 
                    
            double alpha = atan2( sin_alpha, cos_alpha );
                    
            if ( sgn(alpha) < 0) alpha += 2.0 * pi;
            
            return alpha;
}
