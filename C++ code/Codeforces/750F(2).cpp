#include<cstdio>
#include<cassert>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;
int COUNTER=0;
vector<int>Q[129];
vector<int>Ask(const int u)
{
	if(!Q[u].empty())return Q[u];
	if(++COUNTER>16)assert(0);
	printf("? %d\n",u);
	fflush(stdout);
	int k;scanf("%d",&k);
	vector<int>&ans=Q[u];
	for(int i=0,v;i<k;i++)scanf("%d",&v),ans.push_back(v);
	random_shuffle(ans.begin(),ans.end());
	return ans;
}
int H;
bool Dfs(const int u,const int pre,vector<int>&path)
{
	path.push_back(u);
	const vector<int>s=Ask(u);
	if((int)s.size()==2)return true;
	if((int)s.size()==1)return false;
	for(const int nxt:s)if(nxt!=pre)
	{
		return Dfs(nxt,u,path);
	}
	assert(0);return false;
}
int Exclude(const int u,const int e1,const int e2)
{
	const vector<int>et=Ask(u);
	vector<int>ans;
	for(const int nxt:et)
	{
		if(nxt!=e1&&nxt!=e2)ans.push_back(nxt);
	}
	assert((int)ans.size()==1);
	return ans[0];
}
int Exclude(const vector<int>&path,const int i)
{
	const vector<int>et=Ask(path[i]);
	vector<int>ans;
	for(const int nxt:et)
	{
		if(nxt!=path[i-1]&&nxt!=path[i+1])ans.push_back(nxt);
	}
	assert((int)ans.size()==1);
	return ans[0];
}
int Solve(const int u,const int upward,const int h)
{
	if(h==6)
	{
		const vector<int>et=Ask(upward);
		if((int)et.size()==2)return upward;
		assert(0);return -1;
	}
	if(h==5)
	{
		const vector<int>et=Ask(upward);
		if((int)et.size()==2)return upward;
		vector<int>s;
		for(const int nxt:et)if(nxt!=u)s.push_back(nxt);
		assert((int)s.size()==2);
		if((int)Ask(s[0]).size()==2)return s[0];
		else return s[1];
	}
	if(h==4)
	{
		assert(COUNTER<=10);
		const vector<int>et=Ask(upward);
		if((int)et.size()==2)return upward;
		vector<int>s;
		for(const int nxt:et)if(nxt!=u)s.push_back(nxt);
		assert((int)s.size()==2);
		const vector<int>v1=Ask(s[0]),v2=Ask(s[1]);
		{
			if((int)v1.size()==2)return s[0];
			vector<int>_;
			_.clear();
			for(const int nxt:v1)if(nxt!=upward)_.push_back(nxt);
			assert((int)_.size()==2);
			if((int)Ask(_[0]).size()==2)return _[0];
			if((int)Ask(_[1]).size()==2)return _[1];
		}
		{
			if((int)v2.size()==2)return s[1];
			vector<int>_;
			_.clear();
			for(const int nxt:v2)if(nxt!=upward)_.push_back(nxt);
			assert((int)_.size()==2);
			if((int)Ask(_[0]).size()==2)return _[0];
			else return _[1];
		}
	}
	vector<int>path;
	path.push_back(u);
	if(Dfs(upward,u,path))return path.back();
	assert((int)path.size()-1>h);
	const int n=h+(int)path.size()-1;
	assert(n%2==1);
	const int i=n/2-h+1;
	return Solve(path[i],Exclude(path,i),n/2+1);
}
int Solve()
{
	const vector<int>s=Ask(1);
	if((int)s.size()==2)return 1;
	else if((int)s.size()==3)
	{
		vector<vector<int> >paths;
		for(int i=0;i<2;i++)
		{
			vector<int>path;
			path.push_back(1);
			if(Dfs(s[i],1,path))return path.back();
			paths.push_back(path);
		}
		if(paths[0].size()==paths[1].size())
		{
			return Solve(1,Exclude(1,paths[0][1],paths[1][1]),(int)paths[0].size());
		}
		else
		{
			if(paths[0].size()>paths[1].size())swap(paths[0],paths[1]);
			assert(paths[0].size()<paths[1].size());
			const int n=(int)paths[0].size()+(int)paths[1].size()-1;
			assert(n%2==1);
			const int i=n/2-(int)paths[0].size()+1;
			return Solve(paths[1][i],Exclude(paths[1],i),n/2+1);
		}
	}
	else if((int)s.size()==1)
	{
		vector<int>path;path.push_back(1);
		if(Dfs(s[0],1,path))return path.back();
		assert((int)path.size()%2==1);
		return Solve(path[(int)path.size()/2],Exclude(path,(int)path.size()/2),(int)path.size()/2+1);
	}
	else
	{
		assert(0);return -1;
	}
}
int main()
{
	srand((unsigned int)time(NULL));
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		for(int i=0;i<=128;i++)Q[i].clear();
		COUNTER=0;
		scanf("%d",&H);
		printf("! %d\n",Solve());
		fflush(stdout);
	}
	return 0;
}
