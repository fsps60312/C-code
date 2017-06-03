#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
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
vector<vector<int> >S;
bool Solve(vector<pair<int,int> >&ans)
{
	ans.resize(3);
	for(int color=0;color<K;color++)
	{
		static int js[50];
		for(int i=0;i<K;i++)js[i]=0;
		for(int i=0;i<(int)S[color].size();i++)
		{
			const int len=S[color][i];
			Info info=Info();
			for(int nxtc=0;nxtc<K;nxtc++)if(nxtc!=color)
			{
				const vector<int>&s=S[nxtc];
				const int n=(int)s.size();
				int &j=js[nxtc];
				while(j<n&&S[nxtc][j]<=len)++j;
				if(max(j-2,0)<=min(j+1,n-1))
				{
					pair<int,pair<int,int> >p1=make_pair(INF,make_pair(-1,-1)),p2=make_pair(INF,make_pair(-1,-1));
					for(int k=max(j-2,0);k<=min(j+1,n-1);k++)
					{
						if(s[k]<=len)getmin(p1,make_pair(len-s[k],make_pair(nxtc,s[k])));
						getmin(p2,make_pair(abs(len-s[k]),make_pair(nxtc,s[k])));
					}
					info.UpdateShort(len,p1.second);
					info.UpdateClose(len,p2.second);
				}
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
				if(p1.first!=-1&&p2.first!=-1&&abs(len-p2.second)<p1.second)
				{
					ans[0]=make_pair(color,len);
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
			vector<int>s;
			scanf("%d",&n);
			for(int j=0,v;j<n;j++)scanf("%d",&v),s.push_back(v);
			sort(s.begin(),s.end());
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
