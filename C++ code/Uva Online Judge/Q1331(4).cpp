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
double cross(int _o,int _a,int _b)
{
	Vtx &o=VTX[_o],&a=VTX[_a],&b=VTX[_b];
	Vtx v1=(Vtx){a.x-o.x,a.y-o.y},v2=(Vtx){b.x-o.x,b.y-o.y};
	return v1.x*v2.y-v1.y*v2.x;
}
bool betweenangle(int o,int a,int b,int p)
{
	return cross(o,a,p)*cross(o,p,b)>0;
}
double get_area(int va,int vb,int vc)
{
	for(int i=0;i<N;i++)
	{
		if(i==va||i==vb||i==vc)continue;
		if(betweenangle(va,vb,vc,i)&&betweenangle(vb,va,vc,i))return 1e100;
	}
	double a=get_dis(vb,vc),b=get_dis(va,vc),c=get_dis(va,vb),s=(a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}
double BEST[50][50];
double max(double a,double b,double c){if(b>a)a=b;if(c>a)a=c;return a;}
void getmin(double &a,double b){if(b<a)a=b;}
bool isdiagonal(int a,int b)
{
	double &x1=VTX[a].x,&y1=VTX[a].y,&x2=VTX[b].x,&y2=VTX[b].y;
	//(x1-x)/(y1-y)=(x1-x2)/(y1-y2)
	//(y1-y2)x1-(y1-y2)x=(x1-x2)y1-(x1-x2)y
	//(y1-y2)x-(x1-x2)y=(y1-y2)x1-(x1-x2)y1
	double x=y1-y2,y=x1-x2,z=x*x1-y*y1;
	int posi=0,nega=0;
	for(int i=mod(a+1);i!=a;i=(i+1)%N)
	{
		if(i==b)
		{
			if(posi&nega)return false;
			posi=nega=0;
			continue;
		}
		if(x*VTX[i].x-y*VTX[i].y>z)posi|=1;
		else nega|=1;
	}
	return !(posi&nega);
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lf%lf",&VTX[i].x,&VTX[i].y);
		for(int i=1;i<N;i++)
		{
			//printf("%d:%.5lf\n",i,get_dis(i,mod(i+1)));
			BEST[i-1][i]=0;
		}
		for(int span=2;span<N;span++)
		{
			for(int sp=0;sp+span<N;sp++)
			{
				int ep=sp+span;
				BEST[sp][ep]=1e100;
				//if(!isdiagonal(sp,ep))continue;
				for(int mp=sp+1;mp<ep;mp++)
				{
					getmin(BEST[sp][ep],max(BEST[sp][mp],BEST[mp][ep],get_area(sp,mp,ep)));
				}
				//printf("BEST[%d][%d]=%.5lf\n",sp,ep,BEST[sp][ep]);
			}
		}
		printf("%.1lf\n",BEST[0][N-1]);
	}
	return 0;
}
