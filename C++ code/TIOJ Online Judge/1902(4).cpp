#include<cstdio>
#include<cassert>
#include<cmath>
#include<algorithm>
using namespace std;
int CH[1000000][2],SZ[1000000];
int LAST;
inline int Expand(){++LAST,CH[LAST][0]=CH[LAST][1]=-1,SZ[LAST]=1;return LAST;}
inline void Assign(const int u,const int d,const int v){CH[u][d]=v;}
inline int Sz(const int o){return o==-1?0:SZ[o];}
inline int Sz(const int o,const int d){return o==-1?0:Sz(CH[o][d]);}
inline int Ch(const int o,const int d){return o==-1?-1:CH[o][d];}
int Add(const int o,const int v,const int dep)
{
	if(dep==-1)return Expand();
	const int ans=Expand();
	const int d=(v>>dep)&1;
	Assign(ans,d,Add(o==-1?-1:CH[o][d],v,dep-1));
	Assign(ans,d^1,o==-1?-1:CH[o][d^1]);
	SZ[ans]=Sz(ans,0)+Sz(ans,1);
	return ans;
}
int QueryMax(const int o1,const int o2,const int v,const int dep)
{
	if(dep==-1)return 0;
	const int d=((v>>dep)&1)^1;
	if(Sz(o2,d)>Sz(o1,d))return (1<<dep)^QueryMax(Ch(o1,d),Ch(o2,d),v,dep-1);
	else return QueryMax(Ch(o1,d^1),Ch(o2,d^1),v,dep-1);
}
int N,M,Q,S[15001];
int TREE[15001];
int ANS[124][124];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&Q)==2)
	{
		LAST=-1;
		S[0]=0;
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),S[i]^=S[i-1];//,printf("S[%d]=%d\n",i,S[i]);
		TREE[0]=Add(-1,S[0],30);
		for(int i=1;i<=N;i++)TREE[i]=Add(TREE[i-1],S[i],30);
		M=max((int)sqrt(N),1);
		for(int i=0;i<=(N-1)/M;i++)
		{
			const int l=i*M;
			int ans=0;
			for(int j=i;j<=(N-1)/M;j++)
			{
				for(int k=j*M+1;k<=(j+1)*M&&k<=N;k++)ans=max(ans,QueryMax(l?TREE[l-1]:-1,TREE[k-1],S[k],30));
				ANS[i][j]=ans;
			}
		}
		for(int l,r;Q--;)
		{
			scanf("%d%d",&l,&r),--l,--r;
//			printf("l=%d,r=%d\n",l,r);
			int bl=l/M,br=r/M;
			++bl,--br;
			if(bl<=br)
			{
				int ans=ANS[bl][br];
				int lnow=bl*M,rnow=min(N,(br+1)*M);
//				printf("type1: from %d to %d\n",l,bl*M-1);
				for(;lnow>l;lnow--)ans=max(ans,QueryMax(TREE[lnow-1],TREE[rnow],S[lnow-1],30));
//				printf("type1: from %d to %d\n",(br+1)*M+1,r+1);
				for(;rnow<r+1;rnow++)ans=max(ans,QueryMax(lnow?TREE[lnow-1]:-1,TREE[rnow],S[rnow+1],30));
				printf("%d\n",ans);
			}
			else
			{
//				printf("type2: from %d to %d\n",l,r+1);
				int lnow=l,rnow=l;//=Add(-1,S[l],30);
				int ans=0;
				for(;rnow<r+1;rnow++)ans=max(ans,QueryMax(lnow?TREE[lnow-1]:-1,TREE[rnow],S[rnow+1],30));
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
