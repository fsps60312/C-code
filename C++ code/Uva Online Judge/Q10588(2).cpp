#include<cstdio>
#include<queue>
#include<set>
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
	bool operator>(const Sche &s)const{return t!=s.t?t<s.t:a<s.a;}
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
set<Sche,greater<Sche> >HASP;
int main()
{
//	freopen("in.txt","r",stdin);
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
		HASP.clear();
		int ans=-1;
		for(;!HASP.empty()||!pq.empty();) 
		{
			if(!HASP.empty()&&(pq.empty()||(*HASP.begin()).t<pq.top().t))
			{
				assert(ans<=(*HASP.begin()).t+1);
				ans=(*HASP.begin()).t+1;
				while(!HASP.empty()&&(*HASP.begin()).t+1==ans)
				{
					Sche s=*HASP.begin();
					HASP.erase(HASP.begin());
					const int v=VISIT[s.a][s.b];
					assert(!Q[v].empty());
					Q[v].pop();
					s.t++,s.b++;
					assert(ans==s.t);
					if(s.b<VISIT[s.a].size())pq.push(s);
					if(!Q[v].empty())Q[v].front().t=s.t,HASP.insert(Q[v].front());
				}
			}
			else
			{
				assert(ans<=pq.top().t);
				ans=pq.top().t;
				while(!pq.empty()&&pq.top().t==ans)
				{
					const Sche s=pq.top();pq.pop();
					auto &q=Q[VISIT[s.a][s.b]];
					if(q.empty())HASP.insert(s);
					q.push(s);
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
