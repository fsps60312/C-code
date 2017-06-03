#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int max(int a,int b){return a>b?a:b;}
int N,DEG[15],ADJ[15][15];
bool VIS[15];
void dfs(int u,vector<int>&ans)
{
	if(VIS[u])return;
	VIS[u]=true;
	ans.push_back(u);
	for(int i=0;i<N;i++)
	{
		if(!ADJ[u][i])continue;
		dfs(i,ans);
	}
}
void ClearZero(int &ans,int &end,int &trans,int &zero)
{
	if(!zero)return;
	if(trans)
	{
		if(trans>=zero)
		{
			ans+=zero;
			trans-=zero,end+=zero;
			zero=0;
			return;
		}
		else
		{
			ans+=trans;
			zero-=trans,end+=trans;
			trans=0;
		}
	}
	assert(trans==0&&zero);
	if(!end)
	{
		end=2;
		ans+=zero-1;
		zero=0;
		return;
	}
	ans+=zero,zero=0;
}
void ClearTrans(int &ans,int &end,int &trans,int &zero)
{
	if(!trans)return;
	if(trans<=end-2)
	{
		ans+=trans;
		end-=trans,trans=0;
		return;
	}
	else if(end>=2)
	{
		ans+=end-2;
		trans-=end-2;
		end=2;
	}
	else
	{
		ans+=2-end;
		trans-=2-end;
		end=2;
	}
	assert(trans%2==0);
	ans+=trans;
	trans=0;
}
int solve()
{
	for(int a,b;scanf("%d%d",&a,&b)==2&&!(a==-1&&b==-1);)
	{
		a--,b--;
		ADJ[a][b]++,ADJ[b][a]++;
		DEG[a]++,DEG[b]++;
	}
	int trans=0,end=0,zero=0;
	for(int i=0;i<N;i++)
	{
		if(VIS[i])continue;
		vector<int>v;
		dfs(i,v);
		bool isloop=true;
		for(int i=0;i<v.size();i++)
		{
			int &d=DEG[v[i]];
			if(d==0)zero++;
			else if(d==1)end++,isloop=false;
			else if(d>2)
			{
				trans+=d-2;
				isloop=false;
			}
		}
		if(isloop&&!zero)trans++,end++;
	}
//	printf("end=%d,trans=%d,zero=%d\n",end,trans,zero);
	int ans=0;
	ClearZero(ans,end,trans,zero);
	ClearTrans(ans,end,trans,zero);
	assert(end%2==0&&end>=2);
	ans+=(end-2)/2;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			VIS[i]=false;
			DEG[i]=0;
			for(int j=0;j<N;j++)ADJ[i][j]=false;
		}
		static int kase=1;
		printf("Set %d: Minimum links to open is %d\n",kase++,solve());
	}
	return 0;
}
