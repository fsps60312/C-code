#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
int N,S[200000];
void Solve(vector<int>&ans)
{
	sort(S,S+N);
	ans.clear();
	if(N<=2){for(int i=0;i<N;i++)ans.push_back(S[i]);return;}
	int l=-1,r=N;
	LL sum=0LL;
	sum+=S[++l],ans.push_back(S[l]);
	double best=0.0;
	while(l+1<r-1)
	{
		sum+=S[++l]+S[--r];
		if((double)sum/(2.0+ans.size())-S[l]<=best)return;
		ans.push_back(S[l]),ans.push_back(S[r]);
		best=(double)sum/ans.size()-S[l];
	}
	if(l+1<r)
	{
		sum+=S[++l];
		if((double)sum/(1.0+ans.size())-0.5*(S[l-1]+S[l])<=best)return;
		ans.push_back(S[l]);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		vector<int>ans;
		Solve(ans);
		printf("%d\n",(int)ans.size());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
	}
	return 0;
}
