#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
int N,K,P,X,Y;
int S[1000];
bool Solve(vector<int>&ans)
{
	int sum=0;
	vector<int>l,r;
	for(int i=0;i<K;i++)(S[i]>=Y?r:l).push_back(S[i]),sum+=S[i];
	if((int)l.size()>N/2)return false;
	ans.clear();
	for(int i=l.size();i<N/2&&i<N-(int)r.size();i++)ans.push_back(1);
	for(int i=N/2;i<N-(int)r.size();i++)ans.push_back(Y);
	for(const int v:ans)sum+=v;
	return sum<=X;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d%d",&N,&K,&P,&X,&Y)==5)
	{
		for(int i=0;i<K;i++)scanf("%d",&S[i]);
		vector<int>ans;
		if(!Solve(ans))puts("-1");
		else
		{
			for(int i=0;i<(int)ans.size();i++)
			{
				if(i)putchar(' ');
				printf("%d",ans[i]);
			}
			puts("");
		}
	}
	return 0;
}
