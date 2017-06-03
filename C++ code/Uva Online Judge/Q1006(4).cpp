#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=(1<<30);
int M,N,MEM[10],EDGE[50][500];
void get_max(int &a,int b){if(b>a)a=b;}
void get_min(int &a,int b){if(b<a)a=b;}
bool input_all()
{
	if(scanf("%d%d",&M,&N)!=2||(N==0&&M==0))return false;
	for(int i=0;i<M;i++)
	{
		scanf("%d",&MEM[i]);
	}
	//sort(MEM,MEM+M);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N*M;j++)
		{
			EDGE[i][j]=-INF;
		}
	}
	for(int i=0;i<N;i++)
	{
		int a;scanf("%d",&a);
		while(a--)
		{
			int m,t;scanf("%d%d",&m,&t);
			//printf("memory require %d\n",m);
			for(int j=0;j<M;j++)
			{
				if(MEM[j]>=m)
				{
					//printf("from %d find memory region %d\n",i,j);
					for(int tick=0;tick<N;tick++)
					{
						EDGE[i][j*N+tick]=(-t)*(tick+1);
					}
				}
			}
		}
	}
	return true;
}
int T1[50],T2[500],V1[50],V2[500],TO[500];
bool check_paired(int u)
{
	T1[u]=1;
	for(int i=0;i<N*M;i++)
	{
		if(T2[i])continue;
		if(V1[u]+V2[i]==EDGE[u][i])
		{
			T2[i]=1;
			if(TO[i]==-1||check_paired(TO[i]))
			{
				//printf("change TO[%d] to %d , used time : %d\n",i,u,EDGE[u][i]);
				TO[i]=u;
				return true;
			}
		}
		else if(V1[u]+V2[i]<EDGE[u][i])
		{
			printf("error\n");
		}
	}
	return false;
}
void update_KM()
{
	int low=INF;
	for(int i=0;i<N;i++)
	{
		if(!T1[i])continue;
		for(int j=0;j<N*M;j++)
		{
			if(T2[j])continue;
			get_min(low,V1[i]+V2[j]-EDGE[i][j]);
		}
	}
	//printf("low=%d\n",low);
	for(int i=0;i<N;i++)
	{
		if(T1[i])
		{
			V1[i]-=low;
		}
	}
	for(int i=0;i<N*M;i++)
	{
		if(T2[i])
		{
			V2[i]+=low;
		}
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=0;
	while(input_all())
	{
		for(int i=0;i<N;i++)
		{
			V1[i]=-INF;
			for(int j=0;j<N*M;j++)
			{
				get_max(V1[i],EDGE[i][j]);
			}
			//printf("initial V1[%d]=%d\n",i,V1[i]);
		}
		for(int i=0;i<N*M;i++)
		{
			V2[i]=0;
			TO[i]=-1;
		}
		for(int i=0;i<N;i++)
		{
			for(;;)
			{
				for(int j=0;j<N;j++)T1[j]=0;
				for(int j=0;j<N*M;j++)T2[j]=0;
				if(check_paired(i))break;
				else update_KM();
			}
		}
		for(int i=0;i<M;i++)MEM[i]=0;
		for(int i=0;i<N;i++)V1[i]=T1[i]=T2[i]=-1;//memory segment, run period
		int turn_around_time=0;
		for(int tick=N-1;tick>=0;tick--)
		{
			for(int m=0;m<M;m++)
			{
				int &i=TO[m*N+tick];
				if(i!=-1)
				{
					//printf("from %d to %d : %d-th , time=%d\n",i,m,tick,EDGE[i][m*N+tick]);
					if(V1[i]!=-1)printf("error\n");
					V1[i]=m;
					T1[i]=MEM[m];
					MEM[m]-=EDGE[i][m*N];
					T2[i]=MEM[m];
					turn_around_time+=T2[i];
				}
			}
		}
		if(kase++)printf("\n");
		printf("Case %d\n",kase);
		printf("Average turnaround time = %.2lf\n",(double)turn_around_time/N);
		for(int i=0;i<N;i++)
		{
			printf("Program %d runs in region %d from %d to %d\n",i+1,V1[i]+1,T1[i],T2[i]);
		}
	}
	return 0;
}
