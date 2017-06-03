#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
void getmax(double &a,const double b){if(b>a)a=b;}
int N,M;
double W[2501];
vector<int>ET[2501];
void Unique(vector<int>&s){sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());}
void Merge(const int a,const int b)
{
	W[b]+=W[a],W[a]=0.0;
	for(const int nxt:ET[a])
	{
		ET[b].push_back(nxt);
		for(int &nnxt:ET[nxt])if(nnxt==a)nnxt=b;
		sort(ET[nxt].begin(),ET[nxt].end());
		Unique(ET[nxt]);
	}
	Unique(ET[b]);
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0,v;i<N;i++)scanf("%d%lf",&v,&W[i]);
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),--a,--b;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	priority_queue<pair<double,int> >pq;
	double ans=0.0;
	for(int i=0;i<N;i++)pq.push(make_pair(W[i],i)),getmax(ans,W[i]);
	while(!pq.empty())
	{
		const auto p=pq.top();pq.pop();
		for(const int nxt:ET[p.second])
		{
			for(const int oxt:ET[nxt])if(oxt!=p.second&&W[oxt]>=W[nxt]&&W[p.second]>=W[nxt])
			{
				Merge(oxt,p.second),Merge(nxt,p.second);
				pq.push(make_pair(W[p.second],p.second)),getmax(ans,W[p.second]);
				goto index;
			}
		}
		index:;
	}
	printf("%.9f\n",ans);
	return 0;
}
