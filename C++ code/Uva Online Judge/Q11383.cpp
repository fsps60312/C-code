#include<cstdio>
#include<cstdlib>
int ASIGN[500][500],N;
int V1[500],V2[500],TO[500],SLACK[500],T1[500],T2[500];
void getmin(int &a,int b){if(b<a)a=b;}
void getmax(int &a,int b){if(b>a)a=b;}
bool check_paired(int u)
{
	T1[u]=1;
	for(int i=0;i<N;i++)
	{
		if(T2[i])continue;
		if(V1[u]+V2[i]==ASIGN[u][i])
		{
			T2[i]=1;
			if(TO[i]==-1||check_paired(TO[i]))
			{
				TO[i]=u;
				return true;
			}
		}
		else getmin(SLACK[i],V1[u]+V2[i]-ASIGN[u][i]);
	}
	return false;
}
void update()
{
	int slack=(1<<30);
	for(int i=0;i<N;i++)
	{
		if(T2[i])continue;
		getmin(slack,SLACK[i]);
	}
	for(int i=0;i<N;i++)
	{
		if(T1[i])V1[i]-=slack;
		if(T2[i])V2[i]+=slack;
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int r=0;r<N;r++)
		{
			for(int c=0;c<N;c++)
			{
				scanf("%d",&ASIGN[r][c]);
			}
		}
		for(int i=0;i<N;i++)
		{
			V1[i]=V2[i]=0;
			TO[i]=-1;
		}
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				getmax(V1[i],ASIGN[i][j]);
			}
		}
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)SLACK[j]=(1<<30);
			for(;;)
			{
				for(int j=0;j<N;j++)T1[j]=T2[j]=0;
				if(check_paired(i))break;
				else update();
			}
		}
		int ans=V1[0]+V2[0];
		printf("%d",V1[0]);
		for(int i=1;i<N;i++)
		{
			printf(" %d",V1[i]);
			ans+=V1[i];
		}
		printf("\n%d",V2[0]);
		for(int i=1;i<N;i++)
		{
			printf(" %d",V2[i]);
			ans+=V2[i];
		}
		printf("\n%d\n",ans);
	}
	return 0;
}
