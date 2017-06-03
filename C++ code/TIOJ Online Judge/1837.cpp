#include<cstdio>
#include<cmath>
int W,H;
struct Rgb
{
	int r,g,b;
}BMP[1000][1000];
int abs(int a,int b){return a>b?a-b:b-a;}
int dif(Rgb a,Rgb b)
{
	return abs(a.r,b.r)+abs(a.g,b.g)+abs(a.b,b.b);
}
bool read_data(char *filename)
{
	freopen(filename,"r",stdin);
	if(scanf("%d%d",&H,&W)!=2)return false;
	double differ=0;
	for(int i=0;i<H;i++)
	{
		for(int j=0;j<W;j++)
		{
			Rgb &b=BMP[i][j];
			scanf("%d%d%d",&b.r,&b.g,&b.b);
		}
	}
	double differ1=0,differ2=0,differ3=0,differ4=0;
	for(int i=H/4;i+1<H*3/4;i++)
	{
		for(int j=W/4;j+1<W*3/4;j++)
		{
			int dif1=dif(BMP[i][j],BMP[i][j+1]);
			int dif2=dif(BMP[i][j],BMP[i+1][j]);
			differ1+=pow(dif1,1);
			differ2+=pow(dif2,1);
			if(dif1>128)differ3+=1000;
			if(dif1>64)differ4+=1000;
		}
	}
	differ1*=4,differ2*=4;
	differ1/=H*W;
	differ2/=H*W;
	differ3/=H*W;
	differ4/=H*W;
	if(differ3<1&&differ3/differ4<0.5)printf("4\n");
	else if(differ1<20&&differ2<20)printf("1\n");
	else if(differ1<50&&differ2<50)printf("2\n");
	else printf("3\n");
	printf("%10.5lf\t%10.5lf\t%10.5lf\t%10.5lf\n",differ1,differ2,differ3,differ4);
	return true;
}
int main()
{
	char filename[]="1837-test data\\style-1-0.in";
	for(int i=1;i<=4;i++)
	{
		for(int j=0;j<=7;j++)
		{
			printf("style %d data %d\n",i,j);
			filename[21]='0'+i;
			filename[23]='0'+j;
			read_data(filename);
		}
	}
	
	return 0;
}
