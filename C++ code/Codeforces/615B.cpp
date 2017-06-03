#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,M,INC[100000],DEC[100000];
vector<int>ET[100000];
int GetDEC(const int u)
{
	int &ans=DEC[u];
	if(ans!=0)return ans;
	ans=1;
	for(const int nxt:ET[u])if(nxt<u)getmax(ans,GetDEC(nxt)+1);
	return ans;
}
int GetINC(const int u)
{
	int &ans=DEC[u];
	if(ans!=0)return ans;
	ans=1;
	for(const int nxt:ET[u])if(nxt>u)getmax(ans,GetINC(nxt)+1);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),INC[i]=DEC[i]=0;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		long long ans=0;
		for(int i=0;i<N;i++)getmax(ans,(long long)ET[i].size()*GetDEC(i)),getmax(ans,(long long)ET[i].size()*GetINC(i));
		printf("%lld\n",ans);
	}
	return 0;
}
