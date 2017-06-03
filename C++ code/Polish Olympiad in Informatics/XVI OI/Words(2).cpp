#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<set>
using namespace std;
int N,S[100001],LEFT[100002],RIGT[100002];
bool LargerThan(vector<int>&remain,const int d)
{
	if(remain.empty())return false;
	const int v=remain.back();remain.pop_back();
	assert(v<=d);
	if(v==d){return !remain.empty();}
	else if(v<d-1)return false;
	return LargerThan(remain,v-1);
}
int Solve()
{
	map<int,set<int> >p;
	for(int i=1;i<=N;i++)p[S[i]].insert(i);
	vector<int>remain;
	for(map<int,set<int> >::iterator it=p.begin();it!=p.end();)
	{
		vector<int>to_delete;
		for(set<int>::const_reverse_iterator iu=it->second.rbegin();iu!=it->second.rend();++iu)
		{
			const int loc=*iu;
			if(RIGT[loc]==N+1&&S[loc]>0)
			{
				remain.push_back(S[loc]);
				to_delete.push_back(loc);
			}
			else if(LEFT[loc]==0)
			{
				p[S[loc]+=2].insert(loc);
			}
			else if(S[LEFT[loc]]==S[loc]+1)
			{
				const int u=LEFT[loc];
				p[S[u]++].erase(u);
				p[S[u]].insert(u);
				to_delete.push_back(loc);
			}
			else
			{
				return -1;
			}
		}
		for(int i=0;i<(int)to_delete.size();i++)
		{
			const int v=to_delete[i];
			RIGT[LEFT[v]]=RIGT[v];
			LEFT[RIGT[v]]=LEFT[v];
		}
		p.erase(it++);
	}
	int ans=remain.back();remain.pop_back();
	if(remain.empty())return ans;
	if(LargerThan(remain,ans-1))return ans+2;
	else return ans+1;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("slw2ocen.in","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		for(int i=0;i<=N;i++)LEFT[i+1]=i,RIGT[i]=i+1;
		const int ans=Solve();
		if(ans==-1)puts("NIE");
		else puts("TAK");//printf("%d\n",ans);
	}
	return 0;
}
/*
1
3
5 3 3
*/
