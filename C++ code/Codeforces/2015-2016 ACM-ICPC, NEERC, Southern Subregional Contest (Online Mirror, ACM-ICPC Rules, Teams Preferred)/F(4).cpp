#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cassert>
using namespace std;
int N;
struct Dish
{
	int b,cnt;
	bool operator<(const Dish &d)const{return b>d.b;}
};
vector<Dish>NXT[10000];
bool Fit(const int v)
{
	priority_queue<Dish>pq;
	for(int i=0,now=0;i<10000;i++)
	{
		for(int j=0;j<NXT[i].size();j++)
		{
			Dish d=NXT[i][j];
			d.cnt=v;
			if(d.cnt)pq.push(d);
		}
		if(!pq.empty())
		{
			Dish d=pq.top();pq.pop();
			if(i>=d.b)return false;
			d.cnt--;
			if(d.cnt)pq.push(d);
		}
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<10000;i++)NXT[i].clear();
	for(int i=0;i<N;i++)
	{
		Dish d;
		int a;
		scanf("%d%d",&a,&d.b);
		assert(a>=0&&a<=10000&&d.b>=0&&d.b<=10000);
		NXT[a].push_back(d);
	}
	int l=0,r=10000,mid;
	while(l<r)
	{
		mid=(l+r+1)/2;
		if(Fit(mid))l=mid;
		else r=mid-1;
	}
	printf("%d\n",l*N);
	return 0;
}
