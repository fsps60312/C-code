#include<cstdio>
#include<cassert>
#include<set>
#include<algorithm>
using namespace std;
int N,M,DJ[100000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
multiset<int,greater<int> >S[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0,v;i<N;i++)
		{
			DJ[i]=i;
			scanf("%d",&v);
			S[i].clear(),S[i].insert(v);
		}
		scanf("%d",&M);
		for(int a,b;M--;)
		{
			scanf("%d%d",&a,&b),a--,b--;
			a=Find(a),b=Find(b);
			if(a==b)puts("-1");
			else
			{
				if(S[a].size()>S[b].size())swap(a,b);
				multiset<int>::iterator ita=S[a].begin(),itb=S[b].begin();
				S[a].insert((*ita)/2),S[b].insert((*itb)/2);
				S[a].erase(ita),S[b].erase(itb);
				for(multiset<int>::iterator it=S[a].begin();it!=S[a].end();it++)S[b].insert(*it);
				S[a].clear();
				DJ[a]=b;
				printf("%d\n",*S[b].begin());
			}
		}
	}
	return 0;
}
