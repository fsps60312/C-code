#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,K,S[200];
int Solve(const int l,const int r)
{
	vector<int>a,b;
	for(int i=0;i<N;i++)(l<=i&&i<=r?a:b).push_back(S[i]);
	sort(a.begin(),a.end());
	sort(b.begin(),b.end(),greater<int>());
	for(int i=0;i<K&&i<(int)a.size()&&i<(int)b.size()&&b[i]>a[i];i++)swap(a[i],b[i]);
	int sum=0;
	for(const int v:a)sum+=v;
	return sum;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		int ans=-INF;
		for(int l=0;l<N;l++)for(int r=l;r<N;r++)
		{
			getmax(ans,Solve(l,r));
		}
		printf("%d\n",ans);
	}
	return 0;
}
