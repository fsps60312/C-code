#include<cstdio>
#include<cassert>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
vector<int>CH[2];
int LAST;
int Expand(){CH[0].push_back(-1),CH[1].push_back(-1);return ++LAST;}
void Assign(const int u,const int d,const int v){CH[d][u]=v;}
int Add(const int o,const int v,const int dep)
{
	if(dep==-1)return Expand();
	const int ans=Expand();
	const int d=(v>>dep)&1;
	Assign(ans,d,Add(o==-1?-1:CH[d][o],v,dep-1));
	Assign(ans,d^1,o==-1?-1:CH[d^1][o]);
	return ans;
}
int QueryMax(const int o,const int v,const int dep)
{
	if(dep==-1)return 0;
	const int d=((v>>dep)&1)^1;
	if(CH[d][o]!=-1)return (1<<dep)^QueryMax(CH[d][o],v,dep-1);
	else return QueryMax(CH[d^1][o],v,dep-1);
}
int N,M,Q,S[15001];
int TREE[124][124];
int ANS[124][124];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&Q)==2)
	{
		CH[0].clear(),CH[1].clear();
		LAST=-1;
		S[0]=0;
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),S[i]^=S[i-1];//,printf("S[%d]=%d\n",i,S[i]);
		M=max((int)sqrt(N),1);
		for(int i=0;i<=(N-1)/M;i++)
		{
			int o=Add(-1,S[i*M],30);
			int ans=0;
			for(int j=i;j<=(N-1)/M;j++)
			{
				for(int k=j*M+1;k<=(j+1)*M&&k<=N;k++)
				{
					ans=max(ans,QueryMax(o,S[k],30));
					o=Add(o,S[k],30);
				}
//				printf("i=%d,j=%d,from %d to %d\n",i,j,i*M,min((j+1)*M,N));
				ANS[i][j]=ans;
				TREE[i][j]=o;
			}
		}
		for(int l,r;Q--;)
		{
			scanf("%d%d",&l,&r),--l,--r;
			int bl=l/M,br=r/M;
			++bl,--br;
			const int pre_last=LAST;
			if(bl<=br)
			{
				int ans=ANS[bl][br];
				int o=TREE[bl][br];
//				printf("type1: from %d to %d\n",l,bl*M-1);
				for(int i=l;i<bl*M;i++)ans=max(ans,QueryMax(o,S[i],30)),o=Add(o,S[i],30);
//				printf("type1: from %d to %d\n",(br+1)*M+1,r+1);
				for(int i=r+1;i>(br+1)*M;i--)ans=max(ans,QueryMax(o,S[i],30)),o=Add(o,S[i],30);
				printf("%d\n",ans);
			}
			else
			{
//				printf("type2: from %d to %d\n",l,r+1);
				int o=Add(-1,S[l],30);
				int ans=0;
				for(int i=l+1;i<=r+1;i++)ans=max(ans,QueryMax(o,S[i],30)),o=Add(o,S[i],30);
				printf("%d\n",ans);
			}
			while(LAST>pre_last)CH[0].pop_back(),CH[1].pop_back(),--LAST;
		}
	}
	return 0;
}
