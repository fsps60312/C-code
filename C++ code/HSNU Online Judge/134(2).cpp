#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
void Unique(vector<int>&s){sort(s.begin(),s.end());s.resize(unique(s.begin(),s.end())-s.begin());}
int R,C,K;
void Solve(const vector<int>*et,int *ans)
{
	static int dp[100001],len;//visit i edges, walk to highest point is dp[i]
	dp[0]=R,len=1;
	dp[len]=-1;
	ans[0]=len-1;
	for(int i=1;i<C;i++)
	{
		for(const int row:et[i-1])//row is from high to low
		{
			int l=0,r=len;
			while(l<r)
			{
				const int mid=(l+r+1)/2;
				if(dp[mid]>=row)l=mid;
				else r=mid-1;
			}//walk to row visit max r edges, dp[r]>=row
			if(r+1==len)dp[len++]=row,dp[len]=-1;
			else getmax(dp[r+1],row);
		}
//		printf("i=%d:",i);for(int j=0;j<len;j++)printf(" %d",dp[j]);puts("");
		ans[i]=len-1;
	}
}
vector<int>ER[100000],EL[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	static int n;scanf(4,"%d%d%d%d",&C,&R,&n,&K);
	for(int i=0;i<C;i++)ER[i].clear(),EL[i].clear();
	for(int i=0;i<n;i++)
	{
		static int c,r,d;scanf(3,"%d%d%d",&c,&r,&d),c--;
		if(d==1)ER[c].push_back(r);
		else if(d==0)EL[C-1-(c+1)].push_back(r);
		else assert(0);
	}
	for(int i=0;i<C;i++)Unique(ER[i]),Unique(EL[i]);
	static int right_edge[100000],left_edge[100000];
	Solve(ER,right_edge),Solve(EL,left_edge);
	for(int i=0;i<C;i++)right_edge[i]=i-right_edge[i],left_edge[i]=i-left_edge[i];
	for(int l=0,r=C-1;l<r;l++,r--)swap(left_edge[l],left_edge[r]);
//	printf("R:");for(int i=0;i<C;i++)printf(" %d",right_edge[i]);puts("");
//	printf("L:");for(int i=0;i<C;i++)printf(" %d",left_edge[i]);puts("");
	int ans=0;
	for(int l=0,r=-1;l<C;l++)
	{
		while(r+1<C&&right_edge[r+1]+left_edge[l]<=K)r++;
		if(left_edge[l]+right_edge[r]<=K)getmax(ans,r-l+1);
	}
	int r=0,l=C-1;
	while(r<C&&right_edge[r]==0)r++;
	while(l>=0&&left_edge[l]==0)l--;
	printf("%d\n",ans-max(0,r-l-1));
	return 0;
}
