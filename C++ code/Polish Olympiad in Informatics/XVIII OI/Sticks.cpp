#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Info
{
	pair<int,int>short_one;
	pair<int,int>short_two;
	pair<int,int>close_one;
	pair<int,int>close_two;
	Info(){short_one=short_two=make_pair(-1,-INF),close_one=close_two=make_pair(-1,INF);}
	void UpdateShort(const int len,const pair<int,int>&p)
	{
		assert(p.second<=len);
		if(p.second>=short_one.second)short_two=short_one,short_one=p;
		else if(p.second>=short_two.second)short_two=p; 
	}
	void UpdateClose(const int len,const pair<int,int>&p)
	{
		const int dis=abs(len-p.second);
		if(dis<=abs(len-close_one.second))close_two=close_one,close_one=p;
		else if(dis<=abs(len-close_two.second))close_two=p;
	}
};
int K;
vector<map<int,Info> >S;
typedef map<int,Info>::iterator Iterator;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&K)==1)
	{
		S.clear();
		for(int i=0,n;i<K;i++)
		{
			map<int,Info>s;
			scanf("%d",&n);
			for(int j=0,v;j<n;j++)scanf("%d",&v),s[v]=Info();
			S.push_back(s);
		}
		for(int color=0;color<K;color++)
		{
			for(Iterator it=S[color].begin();it!=S[color].end();++it)
			{
				for(int nxtc=0;nxtc<K;nxtc++)if(nxtc!=color)
				{
					Iterator iu=S[nxtc].upper_bound(it->first);
					pair<int,int>p1=make_pair(-1,INF),p2=make_pair(-1,INF);
					if(iu!=S[nxtc].end())p2=make_pair(nxtc,iu->first);
					if(iu!=S[nxtc].begin())
					{
						--iu;
						const pair<int,int>&p=p1=make_pair(nxtc,iu->first);
						it->second.UpdateShort(it->first,p);
					}
					if(abs(it->first-p1.second)<abs(it->first-p2.second))it->second.UpdateClose(it->first,p1);
					else it->second.UpdateClose(it->first,p2);
				}
			}
		}
	}
	return 0;
}
