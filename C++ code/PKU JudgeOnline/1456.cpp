#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
struct Product
{
	int price,deadline;
	bool operator<(const Product &p)const{return deadline<p.deadline;}
}P[10000];
int N;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&P[i].price,&P[i].deadline);
		priority_queue<int>pq;
		for(int i=N-1,d=10000;;d--)
		{
			while(i>=0&&P[i].deadline>=d)
		}
	}
	return 0;
}
