#include<cstdio>
#include<cassert>
#include<string>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
inline void getmax(int &a,const int b){if(a<b)a=b;}
int N,L,M,ANS[1000];
inline void Update(const set<int>&s)
{
	for(set<int>::iterator it=s.begin();it!=s.end();++it)getmax(ANS[*it],(int)s.size());
}
string TRAIN[1000];
map<string,set<int> >S;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&L,&M)==3)
	{
		S.clear();
		for(int i=0;i<N;i++)
		{
			static char train[101];
			scanf("%s",train);
			S[TRAIN[i]=train].insert(i);
		}
		for(int i=0;i<N;i++)ANS[i]=(int)S[TRAIN[i]].size();
		for(int i=0,p1,w1,p2,w2;i<M;i++)
		{
			scanf("%d%d%d%d",&p1,&w1,&p2,&w2),--p1,--w1,--p2,--w2;
			S[TRAIN[p1]].erase(p1),S[TRAIN[p2]].erase(p2);
			swap(TRAIN[p1][w1],TRAIN[p2][w2]);
			S[TRAIN[p1]].insert(p1),S[TRAIN[p2]].insert(p2);
			Update(S[TRAIN[p1]]),Update(S[TRAIN[p2]]);
		}
		for(int i=0;i<N;i++)printf("%d\n",ANS[i]);
	}
	return 0;
}
