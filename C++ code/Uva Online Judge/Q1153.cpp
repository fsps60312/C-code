#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
int T,N;
struct Order
{
	int s,d;
	Order(){}
	Order(int s,int d):s(s),d(d){}
	bool operator<(Order a)const{return d<a.d;}
};
vector<Order>O;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		O.clear();
		for(int i=0,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			O.push_back(Order(a,b));
		}
		sort(O.begin(),O.end());
		priority_queue<int>pq;
		if(O.size())
		{
			int tnow=0;
			for(int i=0,v;i<O.size();i++)
			{
				Order &o=O[i];
				v=tnow+o.s-o.d;
				if(v<=0)tnow+=o.s,pq.push(o.s);
				else if(!pq.empty()&&pq.top()>o.s)
				{
					v-=pq.top();
					tnow=v+o.d;
					pq.pop();
					pq.push(o.s);
				}
			}
		}
		printf("%d\n",pq.size());
		if(T)puts("");
	}
	return 0;
}
