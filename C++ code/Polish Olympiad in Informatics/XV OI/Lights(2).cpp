#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
using namespace std;
vector<pair<int,int> >GetFactors(int n)
{
	vector<pair<int,int> >f;
	for(int v=2;v*v<=n;v++)
	{
		int cnt=0;
		while(n%v==0)n/=v,++cnt;
		if(cnt)f.push_back(make_pair(v,cnt));
	}
	if(n>1)f.push_back(make_pair(n,1));
	return f;
}
void Add(map<int,int>&s,const vector<pair<int,int> >&v,const int sign)
{
	if(s.begin()->first==-1)return;
	for(int i=0;i<(int)v.size();i++)
	{
		const pair<int,int>p=v[i];
		s[p.first]+=p.second*sign;
	}
}
void Print(const vector<int>&s)
{
	vector<int>ans;
	ans.push_back(1);
	for(int i=0;i<(int)s.size();i++)
	{
		for(int j=0;j<(int)ans.size();j++)ans[j]*=s[i];
		for(int j=0;j<(int)ans.size();j++)if(ans[j]>=10)
		{
			if(j+1==(int)ans.size())ans.push_back(0);
			ans[j+1]+=ans[j]/10;
			ans[j]%=10;
		}
	}
	for(int i=(int)ans.size()-1;i>=0;i--)putchar('0'+ans[i]);
}
void Print(const map<int,int>&s)
{
	if(s.begin()->first==-1){printf("0/1");return;}
	vector<int>upon,down;
	for(map<int,int>::const_iterator it=s.begin();it!=s.end();++it)
	{
			 if(it->second<0)for(int i=0;i>it->second;i--)down.push_back(it->first);
		else if(it->second>0)for(int i=0;i<it->second;i++)upon.push_back(it->first);
	}
	Print(upon),putchar('/'),Print(down);
}
int N;
map<int,int>S[1000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0,val;i<N;i++)
		{
			S[i].clear();
			scanf("%d",&val);
			if(val==1)
			{
				for(int j=0;j<i;j++)S[j].clear(),++S[j][-1];
			}
			else
			{
				const vector<pair<int,int> >&f0=GetFactors(val),&f1=GetFactors(val-1);
				Add(S[i],f0,-1);
				for(int j=0;j<i;j++)Add(S[j],f1,1),Add(S[j],f0,-1);
			}
		}
		for(int i=0;i<N;i++)Print(S[i]),puts("");
	}
	return 0;
}
