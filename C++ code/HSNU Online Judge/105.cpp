#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
int T,N,A,B,C;
vector<int>ET[5000];
LL GetF(const LL u){return A*u*u+B*u+C;}
LL Gcd(const LL a,const LL b){return b==0LL?a:Gcd(b,a%b);}
bool VIS[5000];
void Dfs(const int u)
{
	if(VIS[u])return;
	VIS[u]=true;
	for(int i=0;i<ET[u].size();i++)Dfs(ET[u][i]);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&N,&A,&B,&C);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)
		{
			for(int j=i+1;j<N;j++)if(Gcd(GetF(i),GetF(j))==1LL)ET[i].push_back(j),ET[j].push_back(i);
		}
		for(int i=0;i<N;i++)VIS[i]=false;
		int ans=0;
		for(int i=0;i<N;i++)
		{
			if(VIS[i])continue;
			Dfs(i);
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
