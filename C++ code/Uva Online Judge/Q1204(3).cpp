#include<cstdio>
const int INF=1<<30;
int N;
char STR[32][101];
int LEN[16];
int OLAP[32][32];
void getmin(int &a,int b){if(b<a)a=b;}
bool check_contain(char *a,char *b)
{
	for(int i=0;b[i];i++)
	{
		for(int j=0;;j++)
		{
			if(!a[j])return true;
			if(a[j]!=b[i+j])break;
		}
	}
	return false;
}
bool is_same(char *a,char *b)
{
	for(int i=0;;i++)
	{
		if(a[i]!=b[i])return false;
		if(!a[i])return true;
	}
}
void copy_str(char *a,char *b)
{
	for(int i=0;;i++)
	{
		b[i]=a[i];
		if(!a[i])return;
	}
}
void remove_contain()
{
	bool is_ctn[N];
	for(int i=0;i<N;i++)is_ctn[i]=false;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(i==j)continue;
			if(check_contain(STR[i],STR[j]))
			{
				if(!is_ctn[j]||!is_same(STR[i],STR[j]))
				{
					is_ctn[i]=true;
					break;
				}
			}
		}
	}
	int i=0,n=0;
	for(int i=0;i<N;i++)
	{
		if(is_ctn[i])continue;
		copy_str(STR[i],STR[n]);
		n++;
	}
	N=n;
}
int get_OLAP(char *a,char *b)
{
	for(int i=1;;i++)
	{
		for(int j=0;;j++)
		{
			if(!a[i+j])return j;
			if(a[i+j]!=b[j])break;
		}
	}
}
void build_OLAP()
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<LEN[i];j++)
		{
			STR[i+N][LEN[i]]=0;
			STR[i+N][LEN[i]-1-j]=STR[i][j];
		}
	}
	for(int i=0;i<N*2;i++)
	{
		for(int j=0;j<N*2;j++)
		{
			OLAP[i][j]=get_OLAP(STR[i],STR[j]);
		}
	}
}
int DP[1<<16][32];
int get_DP(int s,int last)
{
	int &dp=DP[s][last];
	if(dp!=-1)return dp;
	if(last==N)return dp=INF;
	if(last==0)return dp=(s==1?LEN[0]:INF);
	dp=INF;
	for(int i=0;i<N*2;i++)
	{
		int j=1<<(i%N);
		if(!(s&j)||i%N==last%N)continue;
		getmin(dp,get_DP(s-(1<<(last%N)),i)+LEN[last%N]-OLAP[i][last]);
	}
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			scanf("%s",&STR[i]);
		}
		remove_contain();//N changed
//		for(int i=0;i<N;i++)
//		{
//			printf("%s\n",STR[i]);
//		}
		for(int i=0;i<N;i++)
		{
			int &j=LEN[i]=-1;
			while(STR[i][++j]);
		}
		build_OLAP();
//		for(int i=0;i<N;i++)
//		{
//			for(int j=0;j<N;j++)
//			{
//				printf(" %d",OLAP[i][j]);
//			}printf("\n");
//		}
		for(int i=0;i<(1<<N);i++)
		{
			for(int j=0;j<N*2;j++)
			{
				DP[i][j]=-1;
			}
		}
		int ans=INF;
		for(int i=0;i<N*2;i++)
		{
			getmin(ans,get_DP((1<<N)-1,i)-OLAP[i][0]);
		}
		printf("%d\n",ans==1?2:ans);
	}
	return 0;
}
