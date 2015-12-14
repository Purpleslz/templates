
int MinimumRepresentation(int *s, int l)  
{  
	int i=0,j=1;
	for (int k = 0; i<l&&j<l ; k=0)
	{
		while( s[(i+k)%N] == s[(j+k)%N] && k<l ) k++;
		
		if(k==l) break;
		
		if(s[(i+k)%N]>s[(j+k)%N]) i=i+k+1;
		else  j=j+k+1;
		
    if (i==j) j++;
	}
	
	return min(i,j);
}
