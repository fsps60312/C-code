#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<algorithm>
#include<utility>
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
vector<set<int> >S;
typedef set<int>::const_iterator Iterator;
bool Solve(vector<pair<int,int> >&ans)
{
	ans.resize(3);
	for(int color=0;color<K;color++)
	{
		for(Iterator it=S[color].begin();it!=S[color].end();++it)
		{
			Info info=Info();
			for(int nxtc=0;nxtc<K;nxtc++)if(nxtc!=color)
			{
				Iterator iu=S[nxtc].upper_bound(*it);
				pair<int,int>p1=make_pair(-1,INF),p2=make_pair(-1,INF);
				if(iu!=S[nxtc].end())p2=make_pair(nxtc,*iu);
				if(iu!=S[nxtc].begin())
				{
					--iu;
					const pair<int,int>&p=p1=make_pair(nxtc,*iu);
					info.UpdateShort(*it,p);
				}
				if(abs(*it-p1.second)<abs(*it-p2.second))info.UpdateClose(*it,p1);
				else info.UpdateClose(*it,p2);
			}
			for(int type=0;type<2;type++)
			{
				pair<int,int>p1,p2;
				p1=info.short_one,p2=info.close_one;
				if(p1.first==p2.first)
				{
					if(type)p2=info.close_two;
					else p1=info.short_two;
				}
				if(p1.first!=-1&&p2.first!=-1&&abs(*it-p2.second)<p1.second)
				{
					ans[0]=make_pair(color,*it);
					ans[1]=p1;
					ans[2]=p2;
					return true;
				}
			}
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&K)==1)
	{
		S.clear();
		for(int i=0,n;i<K;i++)
		{
			set<int>s;
			scanf("%d",&n);
			for(int j=0,v;j<n;j++)scanf("%d",&v),s.insert(v);
			S.push_back(s);
		}
		vector<pair<int,int> >ans;
		if(!Solve(ans))puts("NIE");
		else
		{
			assert((int)ans.size()==3);
			for(int i=0;i<3;i++)
			{
				if(i)putchar(' ');
				printf("%d %d",ans[i].first+1,ans[i].second);
			}
			puts("");
		}
	}
	return 0;
}
