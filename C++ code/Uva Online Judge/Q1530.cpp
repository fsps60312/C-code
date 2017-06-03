#include<cstdio>
#include<cmath>
char S[17];
int main()
{
//	freopen("in.txt","r",stdin);
	puts("Program 6 by team X");
	while(scanf("%s",S)==1)
	{
		bool found=false;
		for(int i=1;i<16;i++)if(S[i]=='1'){found=true;break;}
		if(!found){puts(" 0.000000e+000");continue;}
		printf("%c",S[0]=='1'?'-':' ');
		double a=1.0,b=1.0;
		for(int i=8;i<16;i++)
		{
			b*=0.5;
			if(S[i]=='1')a+=b;
		}
		double c=-63.0,d=64.0;
		for(int i=1;i<8;i++)
		{
			if(S[i]=='1')c+=d;
			d*=0.5;
		}
		a*=pow(2.0,c);
		b=log10(a);
		c=floor(b);b-=c;
		printf("%.6fe",pow(10.0,b));
		int e=c+1000.5;e-=1000;
		if(e>=0)printf("+%03d\n",e);
		else printf("-%03d\n",-e);
	}
	puts("End of program 6 by team X");
	return 0;
}
