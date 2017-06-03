#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
int N,M,PRE[10000],PRE_CNT,LOW[10000],BCC_CNT,CNT[10000];
vector<vector<int> >BCC;
bool ISCUT[10000];
vector<int>TO[10000];
void getmin(int &a,int b){if(b<a)a=b;}
void dfs(int u,int fa)
{
	static stack<int>stk;
	if(fa==-1)
	{
		stk=stack<int>();
		if(!TO[u].size())
		{
			BCC.push_back(vector<int>());
			BCC[BCC_CNT].push_back(u);
			BCC_CNT++;
			return;
		}
	}
	stk.push(u);
	LOW[u]=PRE[u]=++PRE_CNT;
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(j==fa)continue;
		if(!PRE[j])
		{
			dfs(j,u);
			getmin(LOW[u],LOW[j]);
			if(fa==-1||LOW[u]==PRE[u])
			{
				BCC.push_back(vector<int>());
				BCC[BCC_CNT].push_back(u);
				while(stk.top()!=u)
				{
					int a=stk.top();stk.pop();
					BCC[BCC_CNT].push_back(a);
				}
				BCC_CNT++;
			}
		}
		else
		{
			getmin(LOW[u],PRE[j]);
		}
	}
}
struct Ans
{
	int idx,peg;
	Ans(){}
	Ans(int i,int p):idx(i),peg(p){}
	bool operator<(const Ans &a)const
	{
		if(peg!=a.peg)return peg>a.peg;
		return idx<a.idx;
	}
};
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		PRE_CNT=BCC_CNT=0;
		BCC.clear();
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			PRE[i]=0;
			ISCUT[i]=false;
			CNT[i]=0;
		}
		for(int a,b;scanf("%d%d",&a,&b)==2&&!(a==-1&&b==-1);)
		{
			TO[a].push_back(b);
			TO[b].push_back(a);
		}
		dfs(0,-1);
		for(int i=0;i<BCC_CNT;i++)
		{
//			printf("BCC%d:",i);
			for(int j=0;j<BCC[i].size();j++)
			{
				int &u=BCC[i][j];
//				printf(" %d",u);
				CNT[u]++;
			}
//			puts("");
		}
		vector<Ans>ans;
		for(int i=0;i<N;i++)ans.push_back(Ans(i,CNT[i]));
		sort(ans.begin(),ans.end());
		for(int i=0;i<M;i++)printf("%d %d\n",ans[i].idx,ans[i].peg);
		puts("");
	}
	return 0;
}
