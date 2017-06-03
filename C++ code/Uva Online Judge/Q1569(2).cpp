#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
typedef double LL;
int N,M;
bool VALID[100000],VIS[100000];
struct Pq
{
	LL val,mod;
	int id;
	vector<char>s;
	Pq(){} 
	Pq(const LL _val,const LL _mod,const int _id,const vector<char>&_s):val(_val),mod(_mod),id(_id),s(_s){}
	bool operator<(const Pq &p)const{return val!=p.val?val>p.val:mod>p.mod;}
};
Pq Solve()
{
	priority_queue<Pq>pq;
	for(int i=1;i<10;i++)if(VALID[N*i%10])pq.push(Pq(N*i,10,N*i/10,vector<char>{'0'+N*i%10}));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(VIS[p.id])continue;
		VIS[p.id]=true;
		if(VALID[p.id])return p;
		for(int i=0;i<10;i++)if(VALID[(p.id+(N*i))%10])
		{
			Pq q=p;
			q.val+=q.mod*N*i;
			q.mod*=10LL;
			q.s.push_back('0'+(q.id+N*i)%10); 
			(q.id+=N*i)/=10;
			pq.push(q);
		}
	}
	return Pq(-1,-1,-1,vector<char>());
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<100000;i++)VALID[i]=VIS[i]=false;
		for(int i=0,v;i<M;i++)scanf("%d",&v),VALID[v]=true;
		for(int i=10;i<100000;i++)
		{
			VALID[i]=true;
			for(int n=i;n;n/=10)if(!VALID[n%10]){VALID[i]=false;break;}
		}
		Pq ans=Solve();
		if(ans.val==-1)puts("0");
		else
		{
			printf("%d",ans.id);
			for(int i=(int)ans.s.size()-1;i>=0;i--)putchar(ans.s[i]);puts("");
		}
	}
	return 0;
}
