#include<cstdio>
#include<cassert>
#include<set>
#include<map>
#include<vector>
using namespace std;
int N;
bool EDGE[1<<12][1<<12];
struct Ans
{
	int a,b,c;
	Ans(){}
	Ans(const int _a,const int _b,const int _c):a(_a),b(_b),c(_c){}
};
vector<Ans>ANS;
void Dfs(const int u,const int pre1,const int pre2,int cnt)
{
	if(cnt==3){ANS.push_back(Ans(pre2,pre1,u));return;}
	bool vis=false;
	for(int i=1;i<N;i++)if(EDGE[u][i])
	{
		if(!vis)EDGE[u][i]=EDGE[i][u]=false,Dfs(i,u,pre1,cnt+1);
		else Dfs(u,-1,-1,0);
		vis=true;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N),N=1<<N;
		for(int i=1;i<N;i++)for(int j=1;j<N;j++)EDGE[i][j]=(i!=j);
		ANS.clear();
		Dfs(1,-1,-1,1);
		for(const Ans &a:ANS)printf("%d %d %d\n",a.a,a.b,a.c);
//		puts("");
	}
	return 0;
}
