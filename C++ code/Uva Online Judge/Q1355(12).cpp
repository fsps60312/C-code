#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int P,M,S[4][4][4],KASE=0;
int NOW[4][4],CNT[4][10],VIS[100];
struct Pair
{
	int p,r,c;
	Pair(){}
	Pair(int p,int r,int c):p(p),r(r),c(c){}
};
vector<Pair>APPEAR[100];
inline void Tag(const int &v,const int &d)
{
	if(d==1)VIS[v]=KASE;
	else VIS[v]=0;
	for(int i=0;i<APPEAR[v].size();i++)
	{
		Pair &p=APPEAR[v][i];
		CNT[p.p][p.r]+=d;
		CNT[p.p][M+p.c]+=d;
		if(p.r==p.c)CNT[p.p][M*2]+=d;
		if(p.r+p.c==M-1)CNT[p.p][M*2+1]+=d;
	}
}
inline bool Bingo(const int &i)
{
	for(int j=0;j<M*2+2;j++)if(CNT[i][j]>=M)return true;
	return false;
}
inline bool Legal()
{
	bool fulled=false;
	for(int i=P-1;i>=0;i--)
	{
		bool win=Bingo(i);
		if(!win&&fulled)return false;
		if(win)fulled=true;
	}
	return true;
}
int GLVS[1<<4],GLKS=0;
void GetLegal(const int &idx,vector<int>&v,int &s)
{
	if(GLVS[s]==GLKS)return;
	GLVS[s]=GLKS;
	if(!Legal())return;
	if(!Bingo(idx)){v.push_back(s);return;}
	for(int i=0;i<M;i++)
	{
		if(!(s&(1<<i))||VIS[NOW[idx][i]]!=KASE)continue;
		s-=1<<i;
		Tag(NOW[idx][i],-1);
		GetLegal(idx,v,s);
		Tag(NOW[idx][i],1);
		s+=1<<i;
	}
} 
inline void GetLegal(const int &idx,vector<int>&v)
{
	GLKS++;
	int s=(1<<M)-1;
	for(int i=0;i<M;i++)
	{
		if(VIS[NOW[idx][i]]!=KASE)continue;
		s-=1<<i;
		Tag(NOW[idx][i],-1);
		GetLegal(idx,v,s);
		Tag(NOW[idx][i],1);
		s+=1<<i;
	}
}
bool Solve(const int &idx)
{
	if(idx==0)return true;
	if(!Bingo(idx))return Solve(idx-1);
	vector<int>v;
	GetLegal(idx,v);
	for(int i=0;i<v.size();i++)
	{
		int &s=v[i];
		for(int j=0;j<M;j++)if(!(s&(1<<j)))Tag(NOW[idx][j],-1);
		if(Solve(idx-1))return true;
		for(int j=0;j<M;j++)if(!(s&(1<<j)))Tag(NOW[idx][j],1);
	}
	return false;
}
inline bool Solve(){return Solve(P-1);}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(int i=0;i<100;i++)VIS[i]=0;
	for(int i=0;i<(1<<4);i++)GLVS[i]=0;
	while(scanf("%d%d",&P,&M)==2&&P&&M)
	{
		for(int i=0;i<100;i++)APPEAR[i].clear();
		for(int i=0;i<P;i++)
		{
			for(int r=0;r<M;r++)
			{
				for(int c=0;c<M;c++)
				{
					int &v=S[i][r][c];
					scanf("%d",&v);
					APPEAR[v].push_back(Pair(i,r,c));
				}
			}
		}
		int limit=1;
		for(int i=0;i<P;i++)limit*=M*2+2;
		int ans=INF;
		for(int s=0;s<limit;s++)
		{
			KASE++;
			int ta=0;
			for(int i=0;i<P;i++)for(int j=0;j<M*2+2;j++)CNT[i][j]=0;
			for(int i=0,t=s;i<P;i++,t/=M*2+2)
			{
				int v=t%(M*2+2);
				for(int j=0;j<M;j++)
				{
					int &n=NOW[i][j];
					if(v<M)n=S[i][v][j];
					else if(v<M*2)n=S[i][j][v-M];
					else if(v==M*2)n=S[i][j][j];
					else n=S[i][j][M-1-j];
					if(VIS[n]!=KASE)
					{
						ta++;
						Tag(n,1);
					}
				}
			}
			if(ta<ans&&Solve())ans=min(ans,ta);
		}
		printf("%d\n",ans==INF?0:ans);
	}
	return 0;
}
/*
4 3

13 30 23
12 15 17
5 24 28

8 28 30
0 5 26
19 4 16

2 3 27
30 28 25
29 6 19

29 27 8
14 28 1
17 26 7
*/
