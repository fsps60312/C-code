#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
int N;
vector<int>ET[5000];
LL CNT[5000];
vector<int>S;
void Dfs(const int u,const int parent,const int dist)
{
	if(!CNT[dist]++)S.push_back(dist);
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)Dfs(ET[u][i],u,dist+1);
}
LL Solve(const vector<int>&s)
{
	static LL a[5000],b[5000];
	const int n=s.size();
	for(int i=0;i<n;i++)a[i]=b[i]=s[i];
	for(int i=1;i<n;i++)a[i]+=a[i-1];
	for(int i=1;i<n;i++)b[i]*=a[i-1];
	for(int i=2;i<n;i++)b[i]+=b[i-1];
	LL ans=0LL;
	for(int i=2;i<n;i++)ans+=s[i]*b[i-1];
	return ans;
}
LL Solve(const int root)
{
	static vector<int>info[5000];
	for(int i=0;i<N;i++)CNT[i]=0,info[i].clear();
	for(int i=0;i<(int)ET[root].size();i++)
	{
		S.clear();
		Dfs(ET[root][i],root,1);
		for(int j=0;j<(int)S.size();j++)
		{
			info[S[j]].push_back(CNT[S[j]]);
			CNT[S[j]]=0;
		}
	}
	LL ans=0LL;
	for(int i=0;i<N;i++)if((int)info[i].size()>=3)ans+=Solve(info[i]);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0,a,b;i<N-1;i++)scanf("%d%d",&a,&b),--a,--b,ET[a].push_back(b),ET[b].push_back(a);
	LL ans=0LL;
	for(int i=0;i<N;i++)ans+=Solve(i);
	printf("%lld\n",ans);
	return 0;
}
