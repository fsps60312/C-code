#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
int N,M,T[100000],J[100000],I[100000];
bool Solve(const int tick)
{
	vector<pair<int,int> >counts;
	for(int i=0;i<tick;i++)counts.push_back(make_pair(T[i],I[i]+1));
	sort(counts.begin(),counts.end());
	for(int i=1;i<(int)counts.size();i++)if(counts[i].first==counts[i-1].first&&counts[i].second!=counts[i-1].second)return false;
	static int mn[100001],mx[100001];
	for(int i=1;i<=N;i++)mn[i]=INF,mx[i]=-INF;
	for(int i=0;i<tick;i++)getmin(mn[J[i]],T[i]),getmax(mx[J[i]],T[i]);
	static int enter[100002],leave[100002];
	for(int i=1;i<=M+1;i++)enter[i]=leave[i]=0;
	for(int i=1;i<=N;i++)if(mn[i]!=INF)enter[mn[i]]++,leave[mx[i]+1]++;
	int certain=0,canleave=0,uncertain=0,leaved=0;
	for(int i=0,j=1;i<(int)counts.size();i++)
	{
		for(;j<=counts[i].first;j++)
		{
			const int v=min(enter[j],uncertain);
			uncertain-=v,certain+=v,enter[j]-=v;
			certain+=enter[j];
			certain-=leave[j],canleave+=leave[j];
		}
		while(certain+canleave+uncertain<counts[i].second)uncertain++;
		while(certain+canleave+uncertain>counts[i].second)
		{
			if(canleave)canleave--,leaved++;
			else
			{
				if(!uncertain)return false;
				uncertain--,leaved++;
			}
		}
	}
	return certain+uncertain+canleave+leaved<=N;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<M;i++)scanf("%d%d%d",&T[i],&J[i],&I[i]);
		int l=0,r=M;
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(Solve(mid))l=mid;
			else r=mid-1;
		}
		printf("%d\n",r);
	}
	return 0;
}
