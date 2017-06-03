#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL &b){if(b>a)a=b;}
int N;
LL DP[700][3];
vector<int>ET[700];
struct Type
{
	LL yes,no;
	Type(){}
	Type(const LL &_yes,const LL &_no):yes(_yes),no(_no){}
	bool operator<(const Type &t)const{return yes*t.no<no*t.yes;}
};
LL Dfs(const int u,const int fa,const int dep)
{
	LL &ans=DP[u][dep];
	if(ans!=-1LL)return ans;
	if(true)
	{
		ans=1LL;
		for(const int nxt:ET[u])if(nxt!=fa)ans*=Dfs(nxt,u,2);
	}
	if(dep==0)return ans;
	if(true)
	{
		vector<Type>chinfo;
		for(const int nxt:ET[u])if(nxt!=fa)chinfo.push_back(Type(Dfs(nxt,u,0),Dfs(nxt,u,2)));
		sort(chinfo.begin(),chinfo.end());
		LL ta=1LL,sz=(dep==1?2LL:1LL)+(LL)chinfo.size();
		for(const auto &v:chinfo)ta*=v.yes;
		ans=sz*ta;
		for(const auto &v:chinfo)
		{
			(ta/=v.yes)*=v.no,sz--;
			getmax(ans,sz*ta);
		}
	}
	if(dep==1)return ans;
	if(true)
	{
		LL ta=1LL;
		for(const int nxt:ET[u])if(nxt!=fa)ta*=Dfs(nxt,u,2);
		for(const int nxt:ET[u])if(nxt!=fa)
		{
			getmax(ans,ta/Dfs(nxt,u,2)*Dfs(nxt,u,1));
		}
	}
	assert(dep==2);
//	printf("ans=%lld\n",ans);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		LL ans=0LL;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)for(int k=0;k<3;k++)DP[j][k]=-1LL;
			getmax(ans,Dfs(i,-1,2));
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
