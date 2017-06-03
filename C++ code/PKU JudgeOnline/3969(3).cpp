#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
const int INF=2147483647;
inline void getmax(int &a,const int b){if(b>a)a=b;}
int N,M,K,ANS[9999];
vector<int>ET[9999];
bool VIS[9999];
set<int>BANNED[9999];
void Dfs(const int u)
{
//	assert(!VIS[u]);
	VIS[u]=true;
	const vector<int>&et=ET[u];
	const int sz=(int)et.size();
	for(int i=0;i<sz;i++)if(!VIS[et[i]])Dfs(et[i]);
	int &ans=ANS[u]=1;
	set<int>&banned=BANNED[u];
	for(set<int>::iterator it=banned.begin();it!=banned.end()&&(*it)==ans;it++,ans++);
//	assert(ans<=K);
	for(int i=0;i<sz;i++)if(ANS[et[i]]==-1)BANNED[et[i]].insert(ans);
}
const int ZERO='0',NINE='9';
inline void GetInt(int &v)
{
	int c=getchar();
	while(c<ZERO||c>NINE)c=getchar();
	v=0;
	while(c>=ZERO&&c<=NINE)v*=10,v+=c,v-=ZERO,c=getchar();
}
int main()
{
//	freopen("in.txt","r",stdin);
	GetInt(N),GetInt(M);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b;i<M;i++)GetInt(a),GetInt(b),a--,b--,ET[a].push_back(b),ET[b].push_back(a);
	K=0;
	for(int i=0;i<N;i++)getmax(K,(int)ET[i].size());
	if(K%2==0)K++;
	int mn=INF,source=-1;
	for(int i=0;i<N;i++)if((int)ET[i].size()<mn)mn=(int)ET[i].size(),source=i;
	for(int i=0;i<N;i++)
	{
		VIS[i]=false,ANS[i]=-1;
		BANNED[i].clear();
	}
	Dfs(source);
//		static int kase=0;
//		if(kase++)puts("");
	printf("%d\n",K);
	for(int i=0;i<N;i++)printf("%d\n",ANS[i]);
	return 0;
}
