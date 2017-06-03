#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
int N,M;
struct Monkey
{
	int v,a,b;
	Monkey(){}
	Monkey(const int _v,const int _a,const int _b):v(_v),a(_a),b(_b){}
};
vector<Monkey>MONKEY;
vector<int>X;
void Discretize()
{
	X.clear();
	for(const Monkey &m:MONKEY)X.push_back(m.a),X.push_back(m.b);
	sort(X.begin(),X.end()),X.resize(unique(X.begin(),X.end())-X.begin());
	for(Monkey &m:MONKEY)m.a=lower_bound(X.begin(),X.end(),m.a)-X.begin(),m.b=lower_bound(X.begin(),X.end(),m.b)-X.begin();
}
vector<int>ANS[100];

int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<=50000;i++)MONKEY[i].clear();
		for(int i=0;i<N;i++)ANS[i].clear();
		for(int i=0,v,a,b;i<N;i++)
		{
			scanf("%d%d%d",&v,&a,&b);
			if(v)MONKEY.push_back(Monkey(v,a,b));
		}
		N=MONKEY.size();
		Discretize();
		for(int i=0;i<N;i++)AddEdge(i,N+i,MONKEY[i].v);
		for(int i=0;i<N;i++)
		{
			for(int j=MONKEY[i].a;j<MONKEY[i].b;j++)AddEdge(N+i,N+N+j,X[j+1]-X[j]);
		}
		for(int i=0;i+1<(int)X.size();i++)
		{
			AddEdge(N+N+i,N+N+(int)X.size()+i,M*(X[i+1]-X[i]));
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
				printf("%d",(int)ans.size());
				for(const auto &p:ans)printf(" (%d,%d)",p.first,p.second);puts("");
			}
		}
	}
	return 0;
}
