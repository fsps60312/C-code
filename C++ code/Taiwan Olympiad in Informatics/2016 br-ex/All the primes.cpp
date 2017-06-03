#include<cstdio>
#include<cassert>
using namespace std;
int N,M;
int ANS,NOW,CNT[70];
vector<int>S[50];
vector<int>P=vector<int>{2,3};
void Dfs(const int dep)
{
	if(NOW>=ANS)return;
	if(dep==N){ANS=NOW;return;}
	for(const int v:S[dep])if(CNT[v]){Dfs(dep+1);return;}
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=2,j;;i++)
	{
		P.push_back(i-1);
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
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			S[i].clear();
			for(int j=0;P[j]<M;j++)
			{
				if(v%P[j]==0)S[i].push_back(j);
			}
		}
		for(int &i=BOUND=0;P[i]<M;i++)CNT[i]=0;
		ANS=BOUND+1,NOW=0;
		Dfs(0);
		if(ANS==BOUND+1)puts("-1");
		else printf("%d\n",ANS);
	}
	return 0;
}
