#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int X,K,N;
int CNT[1001];
struct Steak
{
	int dead,cnt;
	Steak(){}
	Steak(const int _d,const int _c):dead(_d),cnt(_c){}
	bool operator<(const Steak &s)const{return dead+cnt>s.dead+s.cnt;}
};
int main()
{
	freopen("inn.txt","r",stdin);
	while(scanf("%d%d",&X,&K)==2)
	{
		scanf("%d",&N);
		for(int i=0;i<=1000;i++)CNT[i]=0;
		for(int i=0,t;i<N;i++)scanf("%d",&t),CNT[t]++;
		priority_queue<Steak>pq;
		int ans=0;
		for(int t=1000;t>=-X;t--)
		{
			if(t>=0)for(;CNT[t];CNT[t]--)pq.push(Steak(t-X,2));
			if((int)pq.size()>=K||(!pq.empty()&&pq.top().dead+pq.top().cnt==t))
			{
				vector<Steak>used;
				for(int i=0;i<K&&!pq.empty();i++)
				{
					Steak s=pq.top();pq.pop();
					if(--s.cnt)used.push_back(s);
				}
				ans++;
				for(const auto &s:used)pq.push(s);
			}
		}
//		ans+=(pq.size()+K-1)/K;
		printf("%d\n",ans);
	}
	return 0;
}
