#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,S[4],TMP[4];
bool VIS[4];
bool Dfs(const int _loc,const int *o)
{
	if(_loc==N)
	{
		for(int i=0;i<N;i++)assert(VIS[i]);
		return true;
	}
	const int loc=o[_loc];
	bool valid=false;
	for(int i=0;i<N;i++)if(!VIS[i]&&(TMP[loc]&(1<<i)))
	{
		valid=true;
		VIS[i]=true;
		if(!Dfs(_loc+1,o))return false;
		VIS[i]=false;
	}
	return valid;
}
int O[4];
bool Solve()
{
	for(int i=0;i<N;i++)if((TMP[i]&S[i])!=S[i])return false;
	for(int i=0;i<N;i++)O[i]=i;
	bool ans=true;
	do
	{
		for(int i=0;i<N;i++)VIS[i]=false;
		ans&=Dfs(0,O);
	}while(next_permutation(O,O+N));
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		int pre=0;
		for(int i=0;i<N;i++)
		{
			static char str[26];
			scanf("%s",str);
			int &v=S[i]=0;
			for(int j=0;j<N;j++)v=v*2+(str[j]-'0');
			for(int j=0;j<N;j++)if(v&(1<<j))++pre;
		}
		int ans=100000000;
		for(int s=0;s<(1<<(N*N));s++)
		{
			for(int i=0;i<N;i++)TMP[i]=0;
			int cnt=0;
			for(int i=0;i<N*N;i++)if(s&(1<<i))TMP[i/N]|=(1<<(i%N)),++cnt;
			if(cnt<ans&&Solve())ans=cnt;
		}
		static int kase=0;
		printf("Case #%d: ",++kase);
		if(ans==100000000)assert(0);
		else printf("%d\n",ans-pre);
	}
	return 0;
}
