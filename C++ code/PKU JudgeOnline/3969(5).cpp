#include<cstdio>
#include<vector>
using namespace std;
const int INF=2147483647;
inline bool getmax(int &a,const int b){if(b>a){a=b;return true;}return false;}
inline bool getmin(int &a,const int b){if(b<a){a=b;return true;}return false;}
int N,M,K,ANS[9999];
int HEAD[9999],NXT[200000],VAL[200000],DEG[9999],NSZ=0,CNT[9999];
bool VIS[9999];
vector<int>BANNED[9999];
void Dfs(const int u)
{
	VIS[u]=true;
	for(int i=HEAD[u];i!=-1;i=NXT[i])if(!VIS[VAL[i]])Dfs(VAL[i]);
	vector<int>&b=BANNED[u];
	const int bsz=b.size();
	for(int i=0;i<bsz;i++)CNT[b[i]]++;
	int &ans=ANS[u]=0;
	while(CNT[ans]>0)ans++;
	for(int i=0;i<bsz;i++)CNT[b[i]]--;
	for(int i=HEAD[u];i!=-1;i=NXT[i])if(ANS[VAL[i]]==-1)BANNED[VAL[i]].push_back(ans);
}
const int ZERO='0',NINE='9';
inline void GetInt(int &v)
{
	int c=getchar();
	while(c<ZERO||c>NINE)c=getchar();
	v=0;
	while(c>=ZERO&&c<=NINE)v*=10,v+=c,v-=ZERO,c=getchar();
}
inline void AddEdge(const int a,const int b)
{
	NXT[NSZ]=HEAD[a];HEAD[a]=NSZ;
	VAL[NSZ]=b;
	NSZ++;
	DEG[a]++;
}
int main()
{
//	freopen("in.txt","r",stdin);
	GetInt(N),GetInt(M);
	for(int i=0;i<N;i++)HEAD[i]=-1,DEG[i]=0;
	for(int i=0,a,b;i<M;i++)GetInt(a),GetInt(b),a--,b--,AddEdge(a,b),AddEdge(b,a);
	K=0;
	for(int i=0;i<N;i++)getmax(K,DEG[i]);
	if(K%2==0)K++;
	for(int i=0;i<K;i++)CNT[i]=0;
	int mn=INF,source=-1;
	for(int i=0;i<N;i++)if(getmin(mn,DEG[i]))source=i;
	for(int i=0;i<N;i++)
	{
		VIS[i]=false,ANS[i]=-1;
		BANNED[i].clear();
	}
	Dfs(source);
	printf("%d\n",K);
	for(int i=0;i<N;i++)printf("%d\n",ANS[i]+1);
	return 0;
}
