#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,M;
int ANS,NOW,BOUND;
bool VIS[50];
vector<int>S[70];
vector<int>P=vector<int>{2,3};
void Dfs(const int dep)
{
	if(NOW>=ANS)return;
	if(dep==BOUND){ANS=NOW;return;}
	for(const int v:S[dep])if(VIS[v]){Dfs(dep+1);return;}
	for(const int v:S[dep])
	{
		VIS[v]=true,++NOW;
		Dfs(dep+1);
		VIS[v]=false,--NOW;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(P[i]%P[j]==0);
		if(P[i]>=70)break;
	}
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int &i=BOUND=0;P[i]<M;i++)S[i].clear();
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			for(int j=0;P[j]<M;j++)
			{
				if(v%P[j]==0)S[j].push_back(i);
			}
		}
		for(int i=0;i<N;i++)VIS[i]=false;
		ANS=N+1,NOW=0;
		Dfs(0);
		if(ANS==N+1)puts("-1");
		else printf("%d\n",ANS);
	}
	return 0;
}
