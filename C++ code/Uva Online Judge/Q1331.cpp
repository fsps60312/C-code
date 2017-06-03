#include<cstdio>
#include<cmath>
int T,N;
struct Vtx
{
	double x,y;
};
Vtx VTX[50];
int mod(int a){return a%N;}
double pow(double a){return a*a;}
double get_dis(int a,int b){return sqrt(pow(VTX[a].x-VTX[b].x)+pow(VTX[a].y-VTX[b].y));}
double get_area(int va,int vb,int vc)
{
	double a=get_dis(vb,vc),b=get_dis(va,vc),c=get_dis(va,vb),s=(a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}
double BEST[50][50];
double max(double a,double b,double c){if(b>a)a=b;if(c>a)a=c;return a;}
void getmin(double &a,double b){if(b<a)a=b;}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lf%lf",&VTX[i].x,&VTX[i].y);
		for(int i=0;i<N;i++)
		{
			//printf("%d:%.5lf\n",i,get_dis(i,mod(i+1)));
			BEST[i][mod(i+1)]=0;
		}
		for(int span=2;span<=N;span++)
		{
			for(int sp=0;sp<N;sp++)
			{
				int ep=mod(sp+span);
				BEST[sp][ep]=1e100;
				for(int mp=mod(sp+1);mp!=ep;mp=mod(mp+1))
				{
					getmin(BEST[sp][ep],max(BEST[sp][mp],BEST[mp][ep],get_area(sp,mp,ep)));
				}
				//printf("BEST[%d][%d]=%.5lf\n",sp,ep,BEST[sp][ep]);
			}
		}
		double ans=1e100;//printf("%lf\n",ans);
		for(int i=0;i<N;i++)getmin(ans,BEST[i][i]);
		printf("%.1lf\n",ans);
	}
	return 0;
}
