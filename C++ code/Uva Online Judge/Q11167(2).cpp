#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
int N,M;
struct Monkey
{
	int id,thirsty,deadline;
	Monkey(){}
	Monkey(const int _id,const int _thirsty,const int _deadline):id(_id),thirsty(_thirsty),deadline(_deadline){}
	bool operator<(const Monkey&m)const{return deadline-thirsty>m.deadline-m.thirsty;}
};
vector<Monkey>MONKEY[50001];
vector<int>ANS[100];
bool Solve()
{
	priority_queue<Monkey>pq;
	for(int tick=0;tick<=50000;tick++)
	{
		for(const Monkey &m:MONKEY[tick])pq.push(m);
		vector<Monkey>drinked;
		for(int count=0;count<M&&!pq.empty();count++)
		{
			Monkey m=pq.top();pq.pop();
			if(m.deadline<=tick)return false;
			ANS[m.id].push_back(tick);
			m.thirsty--;
			if(m.thirsty)drinked.push_back(m);
		}
		for(const Monkey &m:drinked)pq.push(m);
	}
	return pq.empty();
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&N)
	{
		for(int i=0;i<=50000;i++)MONKEY[i].clear();
		for(int i=0;i<N;i++)ANS[i].clear();
		for(int i=0,v,a,b;i<N;i++)
		{
			scanf("%d%d%d",&v,&a,&b);
			MONKEY[a].push_back(Monkey(i,v,b));
		}
		static int kase=1;
		printf("Case %d: ",kase++);
		if(!Solve())puts("No");
		else
		{
			puts("Yes");
			for(int i=0;i<N;i++)
			{
				vector<pair<int,int> >ans;
				for(const int v:ANS[i])
				{
					if(ans.empty()||ans.back().second<v)ans.push_back(make_pair(v,v+1));
					else ans.back().second++;
				}
				printf("%d ",(int)ans.size());
				for(const auto &p:ans)printf("(%d,%d)",p.first,p.second);puts("");
			}
		}
//		if(kase==26){printf("M=%d\n",M);break;}
	}
	return 0;
}
