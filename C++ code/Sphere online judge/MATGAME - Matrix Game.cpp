#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,M;
int LastTakeWin(const int value){assert(value>0);return value;}
int LastTakeLose(const int value)
{
	assert(value>0);
	if(value==1)return 0;
	return value;
}
int GetSG(const vector<int>&s)
{
	int ans=0;
	for(int i=(int)s.size()-1;i>=0;i--)
	{
		if(ans==0)ans=LastTakeWin(s[i]);
		else ans=LastTakeLose(s[i]);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		int ans=0;
		for(int row=0;row<N;row++)
		{
			vector<int>s;
			for(int col=0,v;col<M;col++)
			{
				scanf("%d",&v);
				if(v)s.push_back(v); 
			}
			ans^=GetSG(s);
		}
		puts(ans==0?"SECOND":"FIRST");
	}
	return 0;
}
