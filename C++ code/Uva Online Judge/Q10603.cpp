#include<cstdio>
#include<queue>
using namespace std;
int T,A,B,C,D;
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int max(int a,int b,int c){return max(a,max(b,c));}
struct Pq
{
	int a,b,c,d,cost;
	Pq(){}
	Pq(int a,int b,int c,int cost):a(a),b(b),c(c),cost(cost)
	{
		d=max(a>D?0:a,b>D?0:b,c>D?0:c);
	}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
bool VIS[201][201][201];
bool Pour(int &x,int &y,int &bound,int &cost)
{
	if(!x||y==bound)return false;
	if(x+y<=bound)cost=x,y+=x,x=0;
	else cost=bound-y,x=x+y-bound,y=bound;
	return true;
}
Pq solve()
{
	priority_queue<Pq>pq;
	Pq ans=Pq(0,0,C,0);
	pq.push(ans);
	while(!pq.empty())
	{
		Pq u=pq.top();pq.pop();
		if(VIS[u.a][u.b][u.c])continue;
		VIS[u.a][u.b][u.c]=true;
		if(u.d==D)return u;
		if(u.d>ans.d||(u.d==ans.d&&u.cost<ans.cost))ans=u;
		static int x,y,cost;
		if(Pour(x=u.a,y=u.b,B,cost))pq.push(Pq(x,y,u.c,u.cost+cost));
		if(Pour(x=u.a,y=u.c,C,cost))pq.push(Pq(x,u.b,y,u.cost+cost));
		if(Pour(x=u.b,y=u.a,A,cost))pq.push(Pq(y,x,u.c,u.cost+cost));
		if(Pour(x=u.b,y=u.c,C,cost))pq.push(Pq(u.a,x,y,u.cost+cost));
		if(Pour(x=u.c,y=u.a,A,cost))pq.push(Pq(y,u.b,x,u.cost+cost));
		if(Pour(x=u.c,y=u.b,B,cost))pq.push(Pq(u.a,y,x,u.cost+cost));
	}
//	printf("can't find\n");
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d%d%d",&A,&B,&C,&D);
			for(int a=0;a<=A&&a<=C;a++)
			{
				for(int b=0;b<=B&&b<=C;b++)
				{
					for(int c=0;c<=C;c++)
					{
						VIS[a][b][c]=false;
					}
				}
			}
			Pq ans=solve();
			printf("%d %d\n",ans.cost,ans.d);
		}
	}
	return 0;
}
