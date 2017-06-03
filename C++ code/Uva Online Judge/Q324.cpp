#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void Mul(vector<int>&s,const int n)
{
	for(int &v:s)v*=n;
	for(int i=0;i<(int)s.size();i++)if(s[i]>=10)
	{
		if(i+1==(int)s.size())s.push_back(0);
		s[i+1]+=s[i]/10;
		s[i]%=10;
	}
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		vector<int>s;s.push_back(1);
		for(int i=2;i<=N;i++)Mul(s,i);
		static int cnt[10];
		for(int i=0;i<10;i++)cnt[i]=0;
		for(const int v:s)++cnt[v];
		printf("%d! --\n",N);
		printf("   (0)%5d    (1)%5d    (2)%5d    (3)%5d    (4)%5d\n",cnt[0],cnt[1],cnt[2],cnt[3],cnt[4]);
		printf("   (5)%5d    (6)%5d    (7)%5d    (8)%5d    (9)%5d\n",cnt[5],cnt[6],cnt[7],cnt[8],cnt[9]);
	}
	return 0;
}
