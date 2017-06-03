#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
int N;
struct Car
{
	int x,v;
	bool operator<(const Car &c)const{return x<c.x;}
	double operator-(const Car &c){return (double)(x-c.x)/(c.v-v);}
}CAR[250000];
struct Bit
{
	int v[100];
	void Clear(){for(int i=1;i<100;i++)v[i]=0;}
	int lowbit(int i){return i&(-i);}
	void Add(int i){while(i<100){v[i]++;i+=lowbit(i);}}
	int Query(int i){int ans=0;while(i){ans+=v[i];i-=lowbit(i);}return ans;}
}BIT;
#include<queue>
int RK[250000],IDX[250000];
struct Pq
{
	int a,b,up,down;
	double loc;
	Pq(int a,int b):a(a),b(b),up(CAR[b].x-CAR[a].x),down(CAR[a].v-CAR[b].v),loc(CAR[b].x+CAR[b].v*((double)up/down)){}
	bool operator<(const Pq &p)const
	{
		if(up*p.down!=down*p.up)return up*p.down>p.up*down;
		return loc>p.loc;
	}
};
#include<cstdlib>
#include<set>
void Push(priority_queue<Pq>&pq,set<LL>&vis,int a,int b)
{
	if(vis.find((LL)a*N+b)!=vis.end())return;
	vis.insert((LL)a*N+b);
	pq.push(Pq(a,b));
}
void Solve()
{
	priority_queue<Pq>pq;
	set<LL>vis;
	for(int i=0;i<N;i++)RK[i]=IDX[i]=i;
	for(int i=1;i<N;i++)
	{
		if(CAR[i-1].v<=CAR[i].v)continue;
		Push(pq,vis,i-1,i);
	}
	for(int i=0;!pq.empty()&&i<10000;i++)
	{
		Pq p=pq.top();pq.pop();
		printf("%d %d\n",p.a+1,p.b+1);
		int ra=RK[p.b],rb=RK[p.a];
		RK[p.a]=ra,RK[p.b]=rb;
		IDX[ra]=p.a,IDX[rb]=p.b;
		if(ra+1<N)
		{
			Car &ca=CAR[IDX[ra]],&cb=CAR[IDX[ra+1]];
			if(ca.v>cb.v)Push(pq,vis,IDX[ra],IDX[ra+1]);
		}
		if(rb-1>=0)
		{
			Car &ca=CAR[IDX[rb-1]],&cb=CAR[IDX[rb]];
			if(ca.v>cb.v)Push(pq,vis,IDX[rb-1],IDX[rb]);
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		int total=0;
		BIT.Clear();
		for(int i=0;i<N;i++)
		{
			int &x=CAR[i].x,&v=CAR[i].v;
			scanf("%d%d",&x,&v);
		}
		sort(CAR,CAR+N);
		for(int i=0;i<N;i++)
		{
			int &x=CAR[i].x,&v=CAR[i].v;
			total+=i-BIT.Query(v);
			total%=1000000;
			BIT.Add(v);
		}
		printf("%d\n",total);
		Solve();
	}
	return 0;
}
