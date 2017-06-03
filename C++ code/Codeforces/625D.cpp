#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int S[100002];
int N;
bool Solve(const int _l)
{
	if(_l>N)return false;
	vector<int>path;
	for(int l=_l,r=N;;l++,r--)
	{
		if(r<l)
		{
			if(S[l-1]||S[l])return false;
			break;
		}
		int v;
		if(l==r)
		{
			v=S[l-1]*10+S[r];
			if(v%2==1)return false;
			v/=2;
		}
		else
		{
			if(S[r]*2/10==S[l-1])v=S[r];
			else v=S[l-1]*10+S[r];
		}
//		printf("(%d,%d)v=%d\n",l,r,v);
		path.push_back(v);
		S[l-1]-=v/10;
		S[l]-=v%10;
		S[r-1]-=v/10;
		S[r]-=v%10;
		while(S[r]<0)S[r]+=10,S[r-1]--;
		for(int i=r-1;i>l&&S[i]<0;i--)S[i-1]--,S[i]+=10;
		if(S[l]<0)return false;
	}
	const int n=path.size();
	vector<char>ans;
	for(int i=0;i<n-1;i++)
	{
		const int v=min(9,path[i]);
		path[i]-=v;
		ans.push_back('0'+v);
	}
	if((N-_l+1)%2==1)
	{
		if(path[n-1]>9)return false;
		ans.push_back('0'+path[n-1]);
		for(int i=n-2;i>=0;i--)
		{
			if(path[i]>9)return false;
			ans.push_back('0'+path[i]);
		}
	}
	else
	{
		const int v=min(9,path[n-1]);
		path[n-1]-=v;
		ans.push_back('0'+v);
		for(int i=n-1;i>=0;i--)
		{
			if(path[i]>9)return false;
			ans.push_back('0'+path[i]);
		}
	}
	if(ans[0]=='0')return false;
	ans.push_back('\0');
	puts(&ans[0]);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char s[100001];
	while(scanf("%s",s)==1)
	{
		N=-1;while(s[++N]);
		S[0]=0;
		for(int i=0;i<N;i++)S[i+1]=s[i]-'0';
		if(!Solve(1))
		{
//			puts("a");
			for(int i=0;i<N;i++)S[i+1]=s[i]-'0';
			if(!Solve(2))puts("0");
		}
	}
	return 0;
}
