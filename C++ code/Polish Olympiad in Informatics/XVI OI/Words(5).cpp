#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<set>
using namespace std;
int N;
vector<int>S,LEFT,RIGT;
void Delete(const int loc)
{
	LEFT[RIGT[loc]]=LEFT[loc];
	RIGT[LEFT[loc]]=RIGT[loc];
}
bool Solve()
{
	map<int,set<int> >p;
	LEFT.resize(N+2),RIGT.resize(N+2);
	for(int i=0;i<=N;i++)LEFT[i+1]=i,RIGT[i]=i+1;
	for(int i=1;i<=N;i++)p[S[i]].insert(i);
	for(map<int,set<int> >::iterator it=p.begin();it!=p.end();)
	{
		printf("v=%d\n",it->first);
		for(set<int>::const_iterator iu=it->second.begin();iu!=it->second.end();++iu)
		{
			const int loc=*iu;
			if(RIGT[loc]==N+1)
			{
				if(LEFT[loc]==0)return true;
				if(S[LEFT[loc]]==S[loc]+1)
				{
					p[S[LEFT[loc]]].erase(LEFT[loc]);
					++S[LEFT[loc]];
					p[S[LEFT[loc]]].insert(LEFT[loc]);
					Delete(loc);
				}
				else if(S[LEFT[loc]]==S[loc])
				{
					if(S[loc]<2){return false;}
					p[S[LEFT[loc]]].erase(LEFT[loc]);
					S[LEFT[loc]]+=2;
					p[S[LEFT[loc]]].insert(LEFT[loc]);
					Delete(loc);
				}
				else
				{
					if(S[loc]==0)return false;
					p[++S[loc]].insert(loc);
				}
			}
			else if(LEFT[loc]==0)
			{
				p[S[loc]+=2].insert(loc);
			}
			else
			{
				if(S[LEFT[loc]]!=S[loc]+1)return false;
				p[S[LEFT[loc]]].erase(LEFT[loc]);
				++S[LEFT[loc]];
				p[S[LEFT[loc]]].insert(LEFT[loc]);
				Delete(loc);
			}
		}
		p.erase(it++);
	}
	assert(0);return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("slw2ocen.in","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		S.resize(N+1);
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		puts(Solve()?"TAK":"NIE");
	}
	return 0;
}
