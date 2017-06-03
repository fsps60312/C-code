#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
using namespace std;
int N,S[100];
map<int,int>F;
vector<LL>P;
void AddFactor(LL n)
{
	for(int i=0;P[i]*P[i]<=n;i++)
	{
		int cnt=0;
		while(n%P[i]==0LL)n/=P[i],cnt++;
		if(cnt)F[P[i]]+=cnt;
	}
	if(n>1)F[n]++;
}
int main()
{
	P.push_back(2LL),P.push_back(3LL);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2LL;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(P[i]%P[j]==0LL);
		if(P[i]*P[i]>2147483647LL)break;
	}
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		F.clear();
		for(int i=0;i<N;i++)AddFactor(S[i]);
	}
	return 0;
}
