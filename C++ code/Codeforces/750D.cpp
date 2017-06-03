#include<cstdio>
#include<cassert>
#include<set>
#include<utility>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
template<class T>inline bool getmin(T&a,const T&b){return a>b?(a=b,true):false;}
int N,S[30];
const int D[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		set<pair<pair<int,int>,int> >f[2];
		set<pair<int,int> >answer;
		f[0].insert(make_pair(make_pair(0,0),0));
		for(int i=0,d=0;i<N;i++)
		{
			for(int j=0;j<S[i];j++,d^=1)
			{
				for(const auto &p:f[d])
				{
					const int x=p.first.first,y=p.first.second,t=p.second;
					const auto &nxtp=make_pair(x+D[t][0],y+D[t][1]);
					f[d^1].insert(make_pair(nxtp,t));
					answer.insert(nxtp);
				}
				f[d].clear();
			}
			for(const auto &p:f[d])
			{
				const int x=p.first.first,y=p.first.second,t=p.second;
				f[d^1].insert(make_pair(make_pair(x,y),(t+1)%8));
				f[d^1].insert(make_pair(make_pair(x,y),(t+7)%8));
			}
			f[d].clear();
			d^=1;
		}
		printf("%d\n",(int)answer.size());
	}
	return 0;
}
