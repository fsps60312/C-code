#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
void getmin(int &a,const int b){if(b<a)a=b;}
int Id(const vector<double>&s,const double v){return lower_bound(s.begin(),s.end(),v)-s.begin();}
int K,N,M,CNT[1500002],LEFT[1500002];
void ReadPoints()
{
	vector<pair<double,double> >segs_d;
	vector<double>xs;xs.push_back(0.0);
	for(int i=0,x1,y1,x2,y2;i<N;i++)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		pair<double,double>p=make_pair((double)y1/x1,(double)y2/x2);
		if(p.first>p.second)swap(p.first,p.second);
		segs_d.push_back(p);
		xs.push_back(p.first),xs.push_back(0.5*(p.first+p.second)),xs.push_back(p.second);
	}
	sort(xs.begin(),xs.end()),xs.resize(unique(xs.begin(),xs.end())-xs.begin());
	vector<pair<int,int> >segs;
	for(int i=0;i<N;i++)segs.push_back(make_pair(Id(xs,segs_d[i].first),Id(xs,segs_d[i].second)));
	M=xs.size();
	for(int i=0;i<=M;i++)CNT[i]=0;
	for(int i=0;i<N;i++)CNT[segs[i].first]++,CNT[segs[i].second+1]--;
	for(int i=1;i<=M;i++)CNT[i]+=CNT[i-1];
	assert(CNT[M]==0);
	for(int i=0;i<=M;i++)LEFT[i]=i;
	for(int i=0;i<N;i++)getmin(LEFT[segs[i].second],segs[i].first);
	for(int i=M-1;i>=0;i--)getmin(LEFT[i],LEFT[i+1]);
}
void DoDP(int *pre,int *dp)
{
//	for(int i=0;i<=M;i++)printf(" %d",pre[i]);puts("");
	for(int i=1;i<=M;i++)getmax(pre[i],pre[i-1]);
	dp[0]=0;
	for(int i=1;i<=M;i++)dp[i]=pre[LEFT[i]-1]+CNT[i];
}
int DP[2][1500002];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&K,&N);
	ReadPoints();
	for(int i=0;i<=M;i++)DP[0][i]=CNT[i];
	int d=0;
	for(int i=1;i<K;i++,d^=1)DoDP(DP[d],DP[d^1]);
	int ans=0;
	for(int i=0;i<=M;i++)getmax(ans,DP[d][i]);
	printf("%d\n",ans);
	return 0;
}
