#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N;
vector<int>P,F,CNT;
void GetF(int n)
{
	for(int i=0,cnt=0;P[i]<=n/P[i];i++,cnt=0)
	{
		while(n%P[i]==0)n/=P[i],cnt++;
		if(cnt>0)F.push_back(P[i]),CNT.push_back(cnt);
	}
	if(n>1)F.push_back(n),CNT.push_back(1);
}
vector<int>ANS;
void Dfs(const int &dep,int now)
{
	if(dep==F.size()){ANS.push_back(now);return;}
	for(int i=0;i<=CNT[dep];i++,now*=F[dep])Dfs(dep+1,now);
}
int main()
{
	P.push_back(2),P.push_back(3);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j]!=0;j++);
		}while(P[i]%P[j]==0);
		if(P[i]>INF/P[i])break;
	}
	while(scanf("%d",&N)==1)
	{
		F.clear(),CNT.clear();
		GetF(N);
		ANS.clear();
		Dfs(0,1);
		sort(ANS.begin(),ANS.end());
		for(int i=0;i<ANS.size();i++)
		{
			if(i)printf(" ");
			printf("%d",ANS[i]);
		}
		puts("");
	}
	return 0;
}
