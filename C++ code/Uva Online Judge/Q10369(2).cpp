#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const double EPS=1e-5;
int T,S,P;
double X[500],Y[500];
int DJ[500];
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
struct Edge
{
	int a,b;
	double cost;
	Edge(){}
	Edge(int a,int b,double cost):a(a),b(b),cost(cost){}
	bool operator<(const Edge &e)const{return cost<e.cost;}
}EDGE[500*500];
double Hypot(double a,double b){return sqrt(a*a+b*b);}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&S,&P);
			for(int i=0;i<P;i++)
			{
				DJ[i]=i;
				scanf("%lf%lf",&X[i],&Y[i]);
			}
			int e=0;
			for(int i=0;i<P;i++)
			{
				for(int j=i+1;j<P;j++)
				{
					EDGE[e++]=Edge(i,j,Hypot(X[i]-X[j],Y[i]-Y[j]));
				}
			}
			sort(EDGE,EDGE+e);
			int i,cnt=P;
			for(i=0;i<e;i++)
			{
				int &a=EDGE[i].a,&b=EDGE[i].b;
				double &cost=EDGE[i].cost;
				if(FindDJ(a)==FindDJ(b))continue;
				DJ[FindDJ(a)]=FindDJ(b);
				cnt--;
				if(cnt==S)break;
			}
			printf("%.2f\n",EDGE[i].cost);
		}
	}
	return 0;
}
