#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,B;
vector<int>PASSWORD;
vector<vector<int> >PLATE;
int ANS;
void Dfs(const int dep,vector<int>&now,const int step)
{
	if(step>=ANS)return;
	if(dep==N)
	{
		assert(now.size()==N);
		for(int i=0;i<N;i++)if(now[i]!=PASSWORD[i])return;
		ANS=step;
		return;
	}
	for(int move=0;move<B;move++)
	{
		Dfs(dep+1,now,step+move);
		for(int i=0;i<N;i++)(now[i]+=PLATE[dep][i])%=B;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&B)==2&&!(N==0&&B==0))
	{
		PASSWORD.clear(),PLATE.clear();
		for(int i=0,v;i<N;i++)scanf("%d",&v),PASSWORD.push_back((B-(--v))%B);
		for(int i=0,p;i<N;i++)
		{
			vector<int>plate;
			for(int j=0;j<N;j++)plate.push_back(0);
			scanf("%d",&p);
			for(int j=0,a,b;j<p;j++)scanf("%d%d",&a,&b),(plate[--a]+=b)%=B;
			PLATE.push_back(plate);
		}
		ANS=INF;
		vector<int>now;
		for(int i=0;i<N;i++)now.push_back(0);
		Dfs(0,now,0);
		if(ANS==INF)puts("No solution");
		else printf("%d\n",ANS);
	}
	return 0;
}
