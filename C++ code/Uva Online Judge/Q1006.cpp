#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int N,M,V1[500],V2[50],ASIGN[50][10],MAT[500][50],TO[50],T1[500],T2[50];
int MEM[10];
void getmin(int &a,int b){if(b<a)a=b;}
void set_runtime(int *asign,int m,int t)
{
	if(m<MEM[0])return;
	int l=0,r=M-1;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(MEM[mid]<m)r=mid+1;
		else l=mid;
	}
	getmin(asign[l],t);
}
bool check_paired(int u)
{
	T1[u]=1;
	for(int i=0;i<N;i++)
	{
		if(MAT[u][i]==(1<<30)||T2[i])continue;
		if(V1[u]+V2[i]==MAT[u][i])
		{
			T2[i]=1;
			if(TO[i]==-1||check_paired(TO[i]))
			{
				TO[i]=u;
				return true;
			}
		}
	}
	return false;
}
void update()
{
	int low=(1<<30);
	for(int i=0;i<N*M;i++)
	{
		if(!T1[i])continue;
		for(int j=0;j<N;j++)
		{
			if(MAT[i][j]==(1<<30)||T2[j])continue;
			getmin(low,V1[i]+V2[j]-MAT[i][j]);
		}
	}
	for(int i=0;i<N*M;i++)
	{
		if(T1[i])V1[i]+=low;
	}
	for(int i=0;i<N;i++)
	{
		if(T2[i])V2[i]-=low;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d%d",&M,&N)==2&&(N||M))
	{
		for(int i=0;i<M;i++)
		{
			scanf("%d",&MEM[i]);
		}
		for(int i=0;i<N;i++)
		{
			int a,j;scanf("%d",&a);
			for(int j=0;j<M;j++)ASIGN[i][j]=(1<<30);
			for(j=0;j<a;j++)
			{
				int s,t;scanf("%d%d",&s,&t);
				set_runtime(ASIGN[i],s,t);
			}
			for(j=0;j<M;j++)//segment
			{
				for(int k=0;k<N;k++)//times
				{
					MAT[j*N+k][i]=ASIGN[i][j]*(k+1);
				}
			}
		}
		for(int i=0;i<N*M;i++)
		{
			V1[i]=-(1<<30);
		}
		for(int i=0;i<N;i++)
		{
			V2[i]=0;
			TO[i]=-1;
		}
		for(int i=0;i<N*M;i++)
		{
			if(ASIGN[i/M][i%M]==(1<<30))continue;
			for(;;)
			{
				for(int i=0;i<N*M;i++)T1[i]=0;
				for(int i=0;i<N;i++)T2[i]=0;
				if(check_paired(i))break;
				else update();
			}
		}
		int ans=0;
		for(int i=0;i<N;i++)
		{
			ans+=MAT[TO[i]][i];
		}
		printf("Case %d\n",kase++);
		printf("Average turnaround time = %.2lf\n",(double)ans/N);
		for(int i=0;i<M;i++)V1[i]=0;
		for(int i=0;i<N;i++)
		{
			int &k=TO[i];
			printf("Program %d runs in region %d from 0 to 4\n",i+1,k/N,V1[k/N],V1[k/N]+=ASIGN[k%N][k/N]);
		}
		printf("\n");
	}
	return 0;
}
