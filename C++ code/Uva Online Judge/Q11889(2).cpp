#include<cstdio>
#include<vector>
#include<cassert> 
#include<map>
using namespace std;
int T,A,C;
vector<int>P;
void GetFactor(int n,map<int,int>&f)
{
	f.clear();
	for(int i=0;P[i]*P[i]<=n;i++)
	{
		int cnt=0;
		while(n%P[i]==0)n/=P[i],cnt++;
		if(cnt)f[P[i]]=cnt;
	}
	if(n>1)f[n]=1;
}
int Solve()
{
	if(C%A)return -1;
	map<int,int>ma,mb;
	GetFactor(C/A,ma);
	GetFactor(C,mb);
	int ans=1;
	for(const auto &it:ma)
	{
		const auto search=mb.find(it.first);
		assert(search!=mb.end());
		for(int i=0;i<search->second;i++)ans*=it.first;
	}
	return ans;
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
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(P[i]%P[j]==0);
		if(P[i]*P[i]>10000000)break;
	}
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&A,&C);
		int ans=Solve();
		if(ans==-1)puts("NO SOLUTION");
		else printf("%d\n",ans);
	}
	return 0;
}
