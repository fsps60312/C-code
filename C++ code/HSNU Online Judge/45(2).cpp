#include<bits/stdc++.h>
using namespace std;
int N,F[100001];
char FOOD[100001];
vector<int>V[2];
int DP[2][16][16];
//string PATH[2][16][16][2];
bool getmax(int &a,const int &b){if(b>a){a=b;return true;}return false;}
int Id(const int &a,const int &b){return a+b*4;}
int Push(const int &v,const int &ori){return v+(ori%4)*4;}
int Cnt(const int &ori,const int &v)
{
	static int a,b,c,cnt[4];
	for(b=0;b<3;b++)cnt[b]=0;
	a=ori/4,b=ori%4,c=v;
	cnt[a]++,cnt[b]++,cnt[c]++;
	a=0;
	for(b=0;b<3;b++)if(cnt[b])a++;
	return a;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%s",&N,FOOD)==2)
	{
		for(int i=0;i<N;i++)
		{
			char &f=FOOD[i];
			if(f=='M')F[i]=0;
			else if(f=='F')F[i]=1;
			else F[i]=2;
		}
		V[0].clear(),V[1].clear();
		for(int i=0;i<16;i++)for(int j=0;j<16;j++)DP[0][i][j]=DP[1][i][j]=-1;
		V[0].push_back(Id(3,3)*16+Id(3,3));DP[0][15][15]=0;
//		PATH[0][15][15][0]=PATH[0][15][15][1]="";
		for(int i=0;i<N;i++)
		{
			int d=i&1;
			for(int j=0,a,b,t;j<V[d].size();j++)
			{
				int &v=V[d][j];
				a=v/16,b=v%16;
				t=Push(F[i],a);
				if(DP[d^1][t][b]==-1)V[d^1].push_back(t*16+b);
				if(getmax(DP[d^1][t][b],DP[d][a][b]+Cnt(a,F[i])))
				{
//					PATH[d^1][t][b][0]=PATH[d][a][b][0]+FOOD[i];
//					PATH[d^1][t][b][1]=PATH[d][a][b][1];
				}
				
				t=Push(F[i],b);
				if(DP[d^1][a][t]==-1)V[d^1].push_back(a*16+t);
				if(getmax(DP[d^1][a][t],DP[d][a][b]+Cnt(b,F[i])))
				{
//					PATH[d^1][a][t][0]=PATH[d][a][b][0];
//					PATH[d^1][a][t][1]=PATH[d][a][b][1]+FOOD[i];
				}
				
//				printf("%d: dp[{%d%d}][{%d%d}]=%d\n",i,a/4,a%4,b/4,b%4,DP[d][a][b]);
				DP[d][a][b]=-1;
			}
			V[d].clear();
		}
		int ans=0,d=N&1;
//		string s1,s2;
		for(int i=0;i<16;i++)for(int j=0;j<16;j++)if(getmax(ans,DP[d][i][j]));//s1=PATH[d][i][j][0],s2=PATH[d][i][j][1];
		printf("%d\n",ans);//,s1.c_str(),s2.c_str());
//		break;
	}
	return 0;
}
