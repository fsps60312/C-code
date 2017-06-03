#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<queue>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int N,S[100000];
bool VIS[100000];
bool Valid(const int l,const int r)
{
	queue<int>pq;
	for(int i=l;i<=r;i++)pq.push(S[i]);
	int pre=pq.front(),cnt=1;pq.pop();
	while(!pq.empty()&&cnt<=4)
	{
		const int u=pq.front();pq.pop();
		if(pre>=u)return false;
		while(u-pre>10&&cnt<=4)pre+=10,cnt++;
		pre=u,cnt++;
	}
	return cnt<=4;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcase;scanf(1,"%d",&testcase);
	while(testcase--)
	{
		scanf(1,"%d",&N);
		for(int i=0;i<N;i++)scanf(1,"%d",&S[i]),VIS[i]=false;
		int cnt=0;
		for(int i=0;i<N;i++)if(!VIS[i])
		{
			for(int j=min(N-1,i+3);;j--)
			{
				assert(i<=j);
				if(Valid(i,j)){while(j>=i)VIS[j--]=true;break;}
			}
			cnt++;
		}
		const int ans=cnt*4-N;
		assert(ans>=0);
		static int kase=1;
		printf("Case #%d: %d\n",kase++,ans);
	}
	scanf(-1,"%d",&testcase);
	return 0;
}
