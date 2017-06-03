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
//	if(N<=2){for(int i=0;i<N;i++)ans.push_back(S[i]);return;}
	int l=-1,r=N;
	LL sum=0LL,cnt=0LL;
	sum+=S[++l],cnt++;
	int ans_l=l,ans_r=r;
	double best=0.0;
	while(l+1<r)
	{
		sum+=S[++l],cnt++;
		if((double)sum/cnt-0.5*(S[l-1]+S[l])>best)best=(double)sum/cnt-0.5*(S[l-1]+S[l]),ans_l=l,ans_r=r;
		if(l+1==r)break;
		sum+=S[--r],cnt++;
		if((double)sum/cnt-S[l]>best)best=(double)sum/cnt-S[l],ans_l=l,ans_r=r;
	}
	for(int i=0;i<=ans_l;i++)ans.push_back(S[i]);
	for(int i=ans_r;i<N;i++)ans.push_back(S[i]);
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
