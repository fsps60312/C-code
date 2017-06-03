#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int INF=(1<<27);
struct Point
{
	int x,y;
	bool operator<(Point a)const{return x<a.x;}
}MEM[10];
int M,N,ASIGN[50][10];
void getmin(int &a,int b){if(b<a)a=b;}
void getmax(int &a,int b){if(b>a)a=b;}
void set_asign(int *asign,int m,int t)
{
	int l=0,r=M-1;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(MEM[mid].x>=m)r=mid;
		else l=mid+1;
	}
	getmin(asign[r],t);
}
void gather_info()
{
	for(int i=0;i<M;i++)
	{
		scanf("%d",&MEM[i].x);
		MEM[i].y=i+1;
	}
	sort(MEM,MEM+M);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)ASIGN[i][j]=INF;
		int a;scanf("%d",&a);
		for(int j=0;j<a;j++)
		{
			int s,t;scanf("%d%d",&s,&t);
			//printf("s=%d t=%d\n",s,t);
			set_asign(ASIGN[i],s,t);
		}
		int now=ASIGN[i][0];
		for(int j=0;j<M;j++)
		{
			if(ASIGN[i][j]!=INF)now=ASIGN[i][j];
			ASIGN[i][j]=now;
		}
	}
}
int MAT[50][500];
void build_MAT()
{
	for(int i=0;i<N;i++)
	{
		//int an=ASIGN[i][0];
		for(int j=0;j<M;j++)
		{
			//if(ASIGN[i][j]!=INF)an=ASIGN[i][j];
			int &an=ASIGN[i][j];
			for(int k=0;k<N;k++)
			{
				int &m=MAT[i][j*N+k];
				m=INF;
				//if(an==INF)continue;
				m=an*(k+1);
				//printf("(%d,%d) m=%d\n",i,j*N+k,m);
			}
		}
	}
}
int V1[50],V2[500],TO[500];
void init_KM()
{
	for(int i=0;i<N;i++)V1[i]=INF;
	for(int i=0;i<N*M;i++)V2[i]=0;
	for(int i=0;i<N*M;i++)TO[i]=-1;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N*M;j++)
		{
			if(MAT[i][j]==INF)continue;
			getmin(V1[i],MAT[i][j]);
		}
	}
}
int T1[50],T2[500],FROM[50];
bool check_paired(int u)
{
	//printf("u=%d\n",u);
	T1[u]=1;
	for(int i=0;i<N*M;i++)
	{
		if(MAT[u][i]==INF||T2[i])continue;
		if(V1[u]+V2[i]==MAT[u][i])
		{
			T2[i]=1;
			if(TO[i]==-1||check_paired(TO[i]))
			{
				//printf("	TO[%d]= %d -> %d\n",i,TO[i],u);
				TO[i]=u;
				FROM[u]=i;
				return true;
			}
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
			if(MAT[i][j]==INF||T2[j])continue;
			getmin(low,MAT[i][j]-V1[i]-V2[j]);
		}
	}
	//printf("%d\n",low);
	for(int i=0;i<N;i++)
	{
		//printf(" %d",V1[i]);
		if(!T1[i])continue;
		//printf("T");
		V1[i]+=low;
	}//printf("\n");
	for(int i=0;i<N*M;i++)
	{
		//printf(" %d",V2[i]);
		if(!T2[i])continue;
		//printf("T");
		V2[i]-=low;
	}//printf("\n");
}
void build_KM()
{
	for(int i=0;i<N;i++)
	{
		int t=0;
		for(;;)
		{
			for(int j=0;j<N;j++)T1[j]=0;
			for(int j=0;j<N*M;j++)T2[j]=0;
			//printf("i=%d\n",i);
			if(check_paired(i))break;
			else update_KM();
			if(t++>5)return;
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int kase=1;
	while(scanf("%d%d",&M,&N)==2&&(M||N))
	{
		gather_info();
		build_MAT();
		init_KM();
		build_KM();
		int ans=0;
		for(int i=0;i<N;i++)ans+=MAT[i][FROM[i]];
		printf("Case %d\n",kase++);
		printf("Average turnaround time = %.2lf\n",(double)ans/N);
		for(int i=0;i<M;i++)T1[i]=0;
		for(int i=N*M-1;i>=0;i--)
		{
			//int i=(ti/M)+(ti%M)*N;
			//i%N is time, i/N is memory segment
			if(TO[i]!=-1)
			{
				V1[TO[i]]=T1[i/N];
				T1[i/N]+=ASIGN[TO[i]][i/N];
				V2[TO[i]]=T1[i/N];
			}
		}
		for(int i=0;i<N;i++)
		{
			int &k=FROM[i];
			int m=k/N;
			printf("Program %d runs in region %d from %d to %d\n",i+1,MEM[m].y,V1[i],V2[i]);
		}
		printf("\n");
	}
	return 0;
}
