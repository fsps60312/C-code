#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,S[100001];
bool Solve(const int start)
{
	if(start>N)return false;
	vector<int>path;
	for(int l=start,r=N;l<=r;l++,r--)
	{
		if(l==r)
		{
			const int v=S[l-1]*10+S[l];
			if(v%2==1||v/2>9)return false;
			path.push_back(v/2);
		}
		else
		{
			const int v=S[r];
			S[r]-=v,S[l]-=v;
			if(S[l]<0)
			{
				S[l-1]--,S[l]+=10;
				if(S[l-1]<0)return false;
			}
			if(S[l-1]>1)return false;
			if(S[l-1]==1)
			{
				S[l-1]--;
				S[r-1]--;
				for(int i=r-1;i>l&&S[i]<0;i--)S[i-1]--,S[i]+=10;
				if(S[l]<0||v==9)return false;
				path.push_back(10+v);
			}
			else path.push_back(v);
		}
		if(l+1==r)
		{
			if(S[l]||S[r])return false;
		}
	}
	if(path[0]==0)return false;
	int v=-1;
	if((N-start+1)%2==1)v=path[path.size()-1],path.pop_back();
	vector<char>ans;
	for(int i=0;i<(int)path.size();i++)
	{
		const int v=min(9,path[i]);
		path[i]-=v;
		ans.push_back('0'+v);
	}
	if(v!=-1)ans.push_back('0'+v);
	for(int i=(int)path.size()-1;i>=0;i--)ans.push_back('0'+path[i]);
	ans.push_back('\0');
	puts(&ans[0]);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char str[100001];
	while(scanf("%s",str)==1)
	{
		N=-1;while(str[++N]);
		S[0]=0;
		for(int i=0;i<N;i++)S[i+1]=str[i]-'0';
		if(!Solve(1))
		{
			S[0]=0;
			for(int i=0;i<N;i++)S[i+1]=str[i]-'0';
			if(!Solve(2))puts("0");
		}
	}
	return 0;
}
