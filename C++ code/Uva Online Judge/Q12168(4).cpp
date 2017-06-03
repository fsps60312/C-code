#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
struct Voter
{
	int like,hate;
	Voter(){}
	Voter(const int _l,const int _h):like(_l),hate(_h){assert(like!=hate);}
};
struct Hungary
{
	int N,M;
	int MATCH[500];
	bool VA[500],VB[500],EDGE[500][500];
	void Build(const vector<Voter>&catliker,const vector<Voter>&dogliker)
	{
		N=catliker.size(),M=dogliker.size();
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)EDGE[i][j]=false;
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)
		{
			const Voter &v1=catliker[i],&v2=dogliker[j];
			if(v1.like==v2.hate||v1.hate==v2.like)EDGE[i][j]=true;
		}
	}
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(int nxt=0;nxt<M;nxt++)if(EDGE[u][nxt])
		{
			VB[nxt]=true;
			if(MATCH[nxt]==-1||Match(MATCH[nxt]))
			{
				MATCH[nxt]=u;
				return true;
			}
		}
		return false;
	}
	int Solve()
	{
		int ans=0;
		for(int i=0;i<M;i++)MATCH[i]=-1;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)VA[j]=false;
			for(int j=0;j<M;j++)VB[j]=false;
			if(Match(i))ans++;
		}
		return N+M-ans;
	}
}HUNGARY;
int C,D,V;
int GetPet()
{
	static char tmp[100];
	assert(scanf("%s",tmp)==1);
	int ans;
	assert(sscanf(tmp+1,"%d",&ans)==1);
	ans--;
	if(tmp[0]=='D')assert(ans>=0&&ans<D),ans+=C;
	else assert(tmp[0]=='C'&&ans>=0&&ans<C);
	return ans;
}
vector<Voter>CATLIKER,DOGLIKER;
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d%d",&C,&D,&V)==3);
		DOGLIKER.clear(),CATLIKER.clear();
		for(int i=0;i<V;i++)
		{
			const int like=GetPet(),hate=GetPet();
//			printf("(%d,%d)\n",like,hate);
			(like<C?CATLIKER:DOGLIKER).push_back(Voter(like,hate));
		}
		HUNGARY.Build(CATLIKER,DOGLIKER);
		printf("%d\n",HUNGARY.Solve());
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
