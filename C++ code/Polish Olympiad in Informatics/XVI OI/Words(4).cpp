#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<set>
using namespace std;
int N;
vector<int>S,LEFT,RIGT;
bool Solve()
{
	map<int,set<int> >p;
	LEFT.resize(N+2),RIGT.resize(N+2);
	for(int i=0;i<=N;i++)LEFT[i+1]=i,RIGT[i]=i+1;
	for(int i=1;i<=N;i++)p[S[i]].insert(i);
	for(map<int,set<int> >::iterator it=p.begin();it!=p.end();++it)
	{
		vector<int>to_delete;
		if(it->second.count(LEFT[N+1]))
		{
			const int loc=LEFT[N+1];
			it->second.erase(loc);
			if(LEFT[loc]==0)break;
			if(S[LEFT[loc]]==S[loc]+1&&(LEFT[LEFT[loc]]==0||S[LEFT[LEFT[loc]]]>S[LEFT[loc]]+1))
			{
				p[S[LEFT[loc]]].erase(LEFT[loc]);
				++S[LEFT[loc]];
				p[S[LEFT[loc]]].insert(LEFT[loc]);
				to_delete.push_back(loc);
			}
			else
			{
				if(S[loc]==0)return false;
				p[++S[loc]].insert(loc);
			}
		}
		for(set<int>::const_iterator iu=it->second.begin();iu!=it->second.end();++iu)
		{
			const int loc=*iu;
			if(LEFT[loc]==0)
			{
				p[S[loc]+=2].insert(loc);
			}
			else
			{
				if(S[LEFT[loc]]!=S[loc]+1)return false;
				p[S[LEFT[loc]]].erase(LEFT[loc]);
				S[LEFT[loc]]+=2;
				p[S[LEFT[loc]]].insert(LEFT[loc]);
				to_delete.push_back(loc);
			}
		}
		for(int i=0;i<(int)to_delete.size();i++)
		{
			const int v=to_delete[i];
			LEFT[RIGT[v]]=LEFT[v];
			RIGT[LEFT[v]]=RIGT[v];
		}
	}
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		S.clear();
		for(int i=1,v;i<=N;i++)scanf("%d",&v),S.push_back(v);
		while(S.back()>=2)
		{
			const int v=S.back();S.pop_back();
			S.push_back(v-1),S.push_back(v-2);
		}
		puts(Solve()?"TAK":"NIE");
	}
	return 0;
}
