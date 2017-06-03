#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
struct Pq
{
	int id;
	vector<int>s;
	Pq(const int _id,const vector<int>_s):id(_id),s(_s){}
	bool operator<(const Pq &p)const{return s.size()!=p.s.size()?s.size()>p.s.size():id>p.id;}
};
int N;
bool VALID[10000],VIS[10000];
vector<int>Solve()
{
	for(int i=0;i<10000;i++)VIS[i]=false;
	priority_queue<Pq>pq;
	for(int i=1;i<10;i++)if(N*i%10<=1)pq.push(Pq(N*i/10,vector<int>{N*i%10}));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(VIS[p.id])continue;
		VIS[p.id]=true;
		if(VALID[p.id])
		{
			vector<int>ans=p.s;
			for(int n=p.id;n;n/=10)ans.push_back(n%10);
			return ans;
		}
		for(int i=0;i<10;i++)if((p.id+N*i)%10<=1)
		{
			Pq q=p;
			q.s.push_back((p.id+N*i)%10);
			q.id=(p.id+N*i)/10;
			pq.push(q);
		}
	}
	assert(0);
	return vector<int>();
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<10;i++)VALID[i]=(i<=1);
	for(int i=10;i<10000;i++)
	{
		VALID[i]=true;
		for(int n=i;n;n/=10)if(!VALID[n%10]){VALID[i]=false;break;}
	}
	while(scanf("%d",&N)==1&&N)
	{
		const vector<int>&ans=Solve();
		for(int i=(int)ans.size()-1;i>=0;i--)putchar('0'+ans[i]);puts("");
	}
	return 0;
}
