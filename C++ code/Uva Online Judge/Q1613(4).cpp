#include<stdio.h>
const int INF=2147483647,MAGNI=3;
inline bool getmax(int &a,const int b){if(b>a){a=b;return true;}return false;}
inline bool getmin(int &a,const int b){if(b<a){a=b;return true;}return false;}
int N,M,K,ANS[9999*MAGNI];
int HEAD[9999*MAGNI],NXT[200000*MAGNI],VAL[200000*MAGNI],DEG[9999*MAGNI],NSZ,CNT[10000*MAGNI];
bool VIS[9999*MAGNI];
void Dfs(const int u)
{
	VIS[u]=true;
	for(int i=HEAD[u];i!=-1;i=NXT[i])if(!VIS[VAL[i]])Dfs(VAL[i]);
	int sum=0;
	for(int i=HEAD[u];i!=-1;i=NXT[i])if(ANS[VAL[i]]!=-1)CNT[ANS[VAL[i]]]++,sum++;
	int &ans=ANS[u]=0;
	while(CNT[ans]>0&&sum-->0)ans++;
	for(int i=HEAD[u];i!=-1;i=NXT[i])if(ANS[VAL[i]]!=-1)CNT[ANS[VAL[i]]]--;
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
	while(scanf("%d%d",&N,&M)==2)
	{
//		GetInt(N),GetInt(M);
		for(int i=0;i<N;i++)HEAD[i]=-1,DEG[i]=0;
		NSZ=0;
		for(int i=0,a,b;i<M;i++)GetInt(a),GetInt(b),a--,b--,AddEdge(a,b),AddEdge(b,a);
		K=0;
		for(int i=0;i<N;i++)if(DEG[i]>K)K=DEG[i];
		if(K%2==0)K++;
		for(int i=0;i<=K;i++)CNT[i]=0;
		int mn=INF,source=-1;
		for(int i=0;i<N;i++)if(DEG[i]<mn)mn=DEG[i],source=i;
		for(int i=0;i<N;i++)VIS[i]=false,ANS[i]=-1;
		Dfs(source);
		static int kase=0;
		if(kase++)puts("");
		printf("%d\n",K);
		for(int i=0;i<N;i++)printf("%d\n",ANS[i]+1);
	}
	return 0;
}
