#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<queue>
#include<set>
#include<cmath>
using namespace std;
const double EPS=1e-9;
void getmax(double &a,const double b){if(b>a)a=b;}
int N,M;
double W[2501];
set<int>ET[2501];
void Merge(const int a,const int b)
{
	W[b]+=W[a],W[a]=-1e100;
	for(const int nxt:ET[a])if(nxt!=b)
	{
		ET[b].insert(nxt);
		ET[nxt].erase(a),ET[nxt].insert(b);
	}
	ET[b].erase(a);
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0,v;i<N;i++)scanf("%d%lf",&v,&W[i]);
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),--a,--b;
		ET[a].insert(b),ET[b].insert(a);
	}
	puts("a");
	priority_queue<pair<double,int> >pq;
	double ans=0.0;
	for(int i=0;i<N;i++)pq.push(make_pair(W[i],i)),getmax(ans,W[i]);
	while(!pq.empty())
	{
		const auto p=pq.top();pq.pop();
		if(W[p.second]==1e-100)continue;
//		printf("p=(%.3f,%d)\n",p.first,p.second);
		for(const int nxt:ET[p.second])if(W[p.second]+W[nxt]>=0.0)
		{
			for(const int oxt:ET[nxt])if(oxt!=p.second&&W[oxt]+W[nxt]>=0.0)
			{
				const double v=W[p.second]+W[nxt]+W[oxt];
				Merge(oxt,p.second),Merge(nxt,p.second);
//				printf("(%.3f,%.3f)\n",v,W[p.second]);
				assert(fabs(W[p.second]-v)<EPS);
				pq.push(make_pair(W[p.second],p.second)),getmax(ans,W[p.second]);
				goto index;
			}
		}
		index:;
	}
	printf("%.9f\n",ans);
	return 0;
}
