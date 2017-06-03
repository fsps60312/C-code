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
	int N;
	int MATCH[500];
	bool VA[500],VB[500],EDGE[500][500];
	void Build(const vector<Voter>&voter)
	{
		N=voter.size();
		for(int i=0;i<N*N;i++)EDGE[i/N][i%N]=false;
//		for(int i=0;i<N;i++)EDGE[i][i]=true;
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)
		{
			const Voter &v1=voter[i],&v2=voter[j];
			if(v1.like==v2.hate||v1.hate==v2.like)EDGE[i][j]=EDGE[j][i]=true;
		}
	}
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(int nxt=0;nxt<N;nxt++)if(EDGE[u][nxt])
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
		for(int i=0;i<N;i++)MATCH[i]=-1;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)VA[j]=VB[j]=false;
			if(Match(i))ans++;
		}
		return N-ans;
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
vector<Voter>VOTER;
int main()
{
	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d%d",&C,&D,&V)==3);
		VOTER.clear();
		for(int i=0;i<V;i++)
		{
			const int like=GetPet(),hate=GetPet();
			printf("(%d,%d)\n",like,hate);
			VOTER.push_back(Voter(like,hate));
		}
		HUNGARY.Build(VOTER);
		printf("%d\n",HUNGARY.Solve());
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
