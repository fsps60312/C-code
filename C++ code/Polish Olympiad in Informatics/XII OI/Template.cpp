#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,Z[500000];
char S[500001];
int LEFT[500002],RIGHT[500002];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%s",S);
	N=-1;while(S[++N]);
	Z[0]=0;
	for(int i=1,mx=0;i<N;i++)
	{
		if(mx+Z[mx]-1>=i)Z[i]=min(mx+Z[mx]-1-i+1,Z[i-mx]);
		else Z[i]=0;
		while(S[Z[i]]==S[i+Z[i]])Z[i]++;
		if(i+Z[i]>=mx+Z[mx])mx=i;
	}
	Z[0]=N;
//	for(int i=0;i<N;i++)printf("%d ",Z[i]);puts("");
	static vector<int>sort_buffer[500001];
	for(int i=0;i<=N;i++)sort_buffer[i].clear();
	for(int i=0;i<N;i++)sort_buffer[Z[i]].push_back(i);
	int ans=N+1;
	for(int i=0;i<=N;i++)LEFT[i+1]=i,RIGHT[i]=i+1;
	for(int len=0,max_gap=1;len<=N;len++)
	{
		if(len>=max_gap){ans=len;break;}
		for(int _i=0;_i<(int)sort_buffer[len].size();_i++)
		{
			const int i=sort_buffer[len][_i]+1;
			getmax(max_gap,RIGHT[i]-LEFT[i]);
			RIGHT[LEFT[i]]=RIGHT[i];
			LEFT[RIGHT[i]]=LEFT[i];
		}
	}
	assert(ans!=N+1);
	printf("%d\n",ans);
	return 0;
}
