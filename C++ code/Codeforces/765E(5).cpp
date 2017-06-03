#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<set>
using namespace std;
const int INF=0x7fffffff;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
int N;
vector<int>ET[200000];
int Dfs(const int u,const int pa)
{
	if(ET[u].size()==1&&pa!=-1)return 0;
	int ans=-1;
	for(const int nxt:ET[u])if(nxt!=pa)
	{
		const int h=Dfs(nxt,u);
		if(h==INF)return INF;
		if(ans==-1)ans=h+1;
		else if(ans!=h+1)return INF;
	}
	assert(ans!=-1);
	return ans;
}
int ANS;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		ANS=INF;
		for(int i=0;i<N;i++)if(ET[i].size()==1)
		{
			int h=Dfs(i,-1);
			while(h%2==0)h/=2;
			getmin(ANS,h);
		}
		printf("%d\n",ANS==INF?-1:ANS);
	}
	return 0;
}
