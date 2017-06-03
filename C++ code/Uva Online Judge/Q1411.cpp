int N,TO[100];
struct Point{int x,y;};
Point S1[100],S2[100];
double DIS[100][100];//ant to apple
double V1[100],V2[100];
#include<cmath>
double dis(Point a,Point b){return hypot(a.x-b.x,a.y-b.y);}
#include<cstdio>
void getmin(double &a,double b){if(b<a)a=b;}
void getmax(double &a,double b){if(b>a)a=b;}
bool T1[100],T2[100];
bool zero(double a){double exp=1e-5;return a>=-exp&&a<=exp;}
bool same(double a,double b){return zero(a-b);}
bool check_paired(int u)
{
	//printf("u=%d\n",u);
	T1[u]=1;
	for(int i=0;i<N;i++)
	{
		if(T2[i])continue;
		if(same(V1[u]+V2[i],DIS[u][i]))//find V1[a]+V2[b]=DIS[a][b]
		{
			T2[i]=1;
			if(TO[i]==-1||check_paired(TO[i]))
			{
				TO[i]=u;
				return true;
			}
		}
	}
	//T1[u]=0;
	return false;
}
void update()
{
	double low=1e100;
	for(int i=0;i<N;i++)
	{
		if(!T1[i])continue;
		for(int j=0;j<N;j++)
		{
			if(T2[j])continue;
			getmin(low,V1[i]+V2[j]-DIS[i][j]);
		}
	}
	for(int i=0;i<N;i++)
	{
		if(T1[i])V1[i]-=low;
		if(T2[i])V2[i]+=low;
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			scanf("%d%d",&S1[i].x,&S1[i].y);
		}
		for(int al=0;al<N;al++)
		{
			scanf("%d%d",&S2[al].x,&S2[al].y);
			for(int i=0;i<N;i++)DIS[i][al]=-dis(S1[i],S2[al]);
		}
		for(int i=0;i<N;i++)
		{
			TO[i]=-1;
			V1[i]=-1e100;
			V2[i]=0;
		}
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				getmax(V1[i],DIS[i][j]);
			}
		}
		for(int i=0;i<N;i++)
		{
			for(;;)
			{
				for(int j=0;j<N;j++)T1[j]=T2[j]=0;
				if(check_paired(i))break;
				else update();
			}
		}
		/*for(int i=0;i<N;i++)
		{
			printf("%.3lf\t%.3lf\n",V1[i],V2[i]);
			for(int j=0;j<N;j++)printf("\t%.3lf",DIS[i][j]);printf("\n");
		}*/
		int ans[N];
		for(int i=0;i<N;i++)
		{
			ans[TO[i]]=i;
		}
		for(int i=0;i<N;i++)
		{
			printf("%d\n",ans[i]+1);
		}
	}
	return 0;
}
