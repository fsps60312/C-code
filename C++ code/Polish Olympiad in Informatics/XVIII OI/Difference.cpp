#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int Solve(const vector<int>&a,const vector<int>&b)
{
	vector<int>s;
	for(int i=0,j=0;i<(int)a.size()||j<(int)b.size();)
	{
		if(i<(int)a.size()&&(j==(int)b.size()||a[i]<b[j]))s.push_back(1),i++;
		else s.push_back(-1),j++;
	}
	int sum=0,ans=0;
	bool hasa=false,hasb=false;
	for(int i=0,l=0;i<(int)s.size();i++)
	{
		if(sum<0)sum=0,l=i,hasa=hasb=false;
		sum+=s[i];
		if(s[i]==1)hasa=true;
		else hasb=true;
		if(hasa)
		{
			if(hasb)getmax(ans,sum);
			else
			{
				if(l&&s[l-1]==-1)getmax(ans,sum-1);
				if(i+1<(int)s.size()&&s[i+1]==-1)getmax(ans,sum-1);
			}
		}
	}
	return ans;
}
int N;
char S[1000001];
vector<int>LOCS[26];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%s",&N,S)==2)
	{
		for(int i=0;i<26;i++)LOCS[i].clear();
		for(int i=0;i<N;i++)LOCS[S[i]-'a'].push_back(i);
		int ans=0;
		for(int i=0;i<26;i++)for(int j=0;j<26;j++)if(i!=j)
		{
			getmax(ans,Solve(LOCS[i],LOCS[j]));
		}
		printf("%d\n",ans);
	}
	return 0;
}
