#include<cstdio>
#include<queue>
#include<cassert>
using namespace std;
int T,N,M;
vector<vector<int> >VISIT;
struct Sche
{
	int t,a,b;
	Sche(){}
	Sche(const int _t,const int _a,const int _b):t(_t),a(_a),b(_b){}
	bool operator<(const Sche &s)const{return t!=s.t?t>s.t:a>s.a;}
};
struct Deq
{
	vector<Sche>s;
	int l,r;
	void clear(){s.clear();l=0,r=-1;}
	Sche &front(){return s[l];}
	void pop(){l++;}
	void push(const Sche &v){s.push_back(v);r++;}
	bool empty()const{return r<l;}
};
Deq Q[1000];
vector<int>HASP[2];
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		VISIT.clear();
		scanf("%d%d",&N,&M);
		for(int i=0;i<M;i++)Q[i].clear();
		priority_queue<Sche>pq;
		for(int i=0,t,k;i<N;i++)
		{
			scanf("%d%d",&t,&k);
			vector<int>tmp;
			for(int j=0,v;j<k;j++)scanf("%d",&v),tmp.push_back(--v);
			VISIT.push_back(tmp);
			if(0<tmp.size())pq.push(Sche(t,i,0));
		}
		HASP[0].clear(),HASP[1].clear();
		int d=0;
		int ans=-1;
		for(;!HASP[d].empty()||!pq.empty();d^=1) 
		{
//			printf("HASP:");for(auto v:HASP[d])printf(" %d",v+1);puts("");
			for(const auto v:HASP[d])
			{
				assert(!Q[v].empty());
				Sche s=Q[v].front();
				Q[v].pop();
				s.t++,s.b++;
				assert(ans<=s.t),ans=s.t;
//				printf("time %d: ",s.t);
				if(s.b<VISIT[s.a].size())pq.push(s);//,printf("%d from (%d)%d to (%d)%d\n",s.a+1,s.b-1,VISIT[s.a][s.b-1]+1,s.b,VISIT[s.a][s.b]+1);
//				else printf("%d leave\n",s.a+1);
				if(!Q[v].empty())HASP[d^1].push_back(v),Q[v].front().t=s.t;
			}
			HASP[d].clear();
			if(pq.empty())continue;
			assert(ans<=pq.top().t),ans=pq.top().t;
			while(!pq.empty()&&pq.top().t==ans)
			{
				const Sche s=pq.top();pq.pop();
				auto &q=Q[VISIT[s.a][s.b]];
				if(q.empty())HASP[d^1].push_back(VISIT[s.a][s.b]);
				q.push(s);
//				printf("time %d: %d enter %d\n",s.t,s.a+1,VISIT[s.a][s.b]+1);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
