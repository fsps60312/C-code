#include<stdio.h>
int INF=2147483647;
int N,M,K,ANS[9999];
int HEAD[9999],NXT[200000],VAL[200000],DEG[9999],NSZ=0,CNT[9999];
int VIS[9999];
int STKU[9999],STKI[9999],SSZ; 
void Dfs(int source)
{
	SSZ=0;
	STKU[0]=source,STKI[0]=HEAD[source],VIS[source]=1;
	while(SSZ>=0)
	{
		int u=STKU[SSZ],i=STKI[SSZ];SSZ--;
		if(i!=-1)
		{
			int nxt=VAL[i];
			if(!VIS[nxt])SSZ++,STKU[SSZ]=nxt,STKI[SSZ]=HEAD[nxt],VIS[nxt]=1;
			SSZ++,STKU[SSZ]=u,STKI[SSZ]=NXT[i];
		}
		else
		{
			for(i=HEAD[u];i!=-1;i=NXT[i])if(ANS[VAL[i]]!=-1)CNT[ANS[VAL[i]]]++;
			int ans=0;
			while(CNT[ans]>0)ans++;
			ANS[u]=ans;
			for(i=HEAD[u];i!=-1;i=NXT[i])if(ANS[VAL[i]]!=-1)CNT[ANS[VAL[i]]]--;
		}
	}
}
int ZERO='0',NINE='9';
int GetInt()
{
	static int v,c;c=getchar();
	while(c<ZERO||c>NINE)c=getchar();
	v=0;
	while(c>=ZERO&&c<=NINE)v*=10,v+=c,v-=ZERO,c=getchar();
	return v;
}
void AddEdge(int a,int b)
{
	NXT[NSZ]=HEAD[a];HEAD[a]=NSZ;
	VAL[NSZ]=b;
	NSZ++;
	DEG[a]++;
}
int main()
{
//	freopen("in.txt","r",stdin);
	N=GetInt(),M=GetInt();
	int i,a,b;
	for(i=0;i<N;i++)HEAD[i]=-1,DEG[i]=0;
	for(i=0;i<M;i++)a=GetInt(),b=GetInt(),a--,b--,AddEdge(a,b),AddEdge(b,a);
	K=0;
	for(i=0;i<N;i++)if(DEG[i]>K)K=DEG[i];
	if(K%2==0)K++;
	for(i=0;i<K;i++)CNT[i]=0;
	int mn=INF,source=-1;
	for(i=0;i<N;i++)if(DEG[i]<mn)mn=DEG[i],source=i;
	for(i=0;i<N;i++)VIS[i]=0,ANS[i]=-1;
	Dfs(source);
	printf("%d\n",K);
	for(i=0;i<N;i++)printf("%d\n",ANS[i]+1);
	return 0;
}
