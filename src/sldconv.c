#include <stdio.h>
#include <stdlib.h>
#include <math.h>

short chkrng(short n)
{
	if (n <= -32768)
	{
		return -32768;
	} else if (n >= 32767)
	{
		return 32767;
	} else {
		return n;
	};
};

short tableconv2(short n)
{
	if(n >= 16384){
    	return 15;
	}
	else if( n >= 8192)
	{
    	return 14;
	}
	else if( n >= 4096)
	{
    	return 13;
	}
	else if( n >= 2048)
	{
    	return 12;
	}
	else if( n >= 1024)
	{
    	return 11;
	}
	else if( n >=  512)
	{
    	return 10;
	}
	else if( n >=  256)
	{
    	return 9;
	}
	else if( n >= -255)
	{
    	return 8;
	}
	else if( n >= -511)
	{
    	return 7;
	}
	else if( n >= -1023)
	{
    	return 6;
	}
	else if( n >=-2047)
	{
    	return 5;
	}
	else if( n >=-4095)
	{
    	return 4;
	}
	else if( n >=-8191)
	{
    	return 3;
	}
	else if( n >=-16383)
	{
    	return 2;
	}
	else if( n >=-32767)
	{
    	return 1;
	}
	else
	{
    	return 0;
	}
}

short tableconv(short n)
{
	if(n >= 16384){
    	return 16384;
	}
	else if( n >= 8192)
	{
    	return 8192;
	}
	else if( n >= 4096)
	{
    	return 4096;
	}
	else if( n >= 2048)
	{
    	return 2048;
	}
	else if( n >= 1024)
	{
    	return 1024;
	}
	else if( n >=  512)
	{
    	return 512;
	}
	else if( n >=  256)
	{
    	return 256;
	}
	else if( n >= -255)
	{
    	return 0;
	}
	else if( n >= -511)
	{
    	return -256;
	}
	else if( n >= -1023)
	{
    	return -512;
	}
	else if( n >=-2047)
	{
    	return -1024;
	}
	else if( n >=-4095)
	{
    	return -2048;
	}
	else if( n >=-8191)
	{
    	return -4096;
	}
	else if( n >=-16383)
	{
    	return -8192;
	}
	else if( n >=-32767)
	{
    	return -16384;
	}
	else
	{
    	return -32768;
	}
}

main(int argc,char *argv[])
{
	short par,pbr;
	short a,b,d,e,f;
	char c;
	short delta,sigma,in,out;
	FILE *pa,*pb;
	
	delta=9;
	sigma=0;
	
	par=(pa = fopen(argv[1],"rb"));
	pbr=(pb = fopen(argv[2],"wb"));
	
	if(par == NULL)
	{ 
	printf("file open error.\n");
	exit(2); 
	}
	
	while((c=getc(pa)) != EOF)
	{
		in=(c*257);
		delta=in-sigma;
		e=tableconv(delta);
		f=tableconv2(delta);
		sigma=chkrng(sigma+e);
		out=(16*f)+f;
		putc(out,pb);
	}
	
	fclose(pa);
	fclose(pb);
	printf("convert successfully.\n");
}
