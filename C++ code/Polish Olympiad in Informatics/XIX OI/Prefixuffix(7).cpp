#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<queue>
#include<utility>
#include<queue>
using namespace std;
typedef long long LL;
const LL BASE=103,MOD=2147483647;
LL PS[2000000],POW[2000000];
bool IsSame(const int l1,const int r1,const int l2,const int r2)
{
	return ((PS[r1]-PS[l1-1]*POW[r1-l1+1])-(PS[r2]-PS[l2-1]*POW[r2-l2+1]))%MOD==0;
}
int N;
char S[2000000];
int Solve()
{
//	puts(S+1);
	vector<pair<int,int> >sot;
	sot.reserve(N);
	for(int i=1;i<N;++i)
	{
		int l=0,r=min(i-1,N-1-i);
		const int rear=N*2-i;
		while(l<r)
		{
			const int mid=(l+r+1)>>1;
			if(IsSame(i-mid,i+mid,rear-mid,rear+mid))l=mid;
			else r=mid-1;
		}
		sot.push_back(make_pair(i-r,i));
	}
	sort(sot.begin(),sot.end());
	priority_queue<int,vector<int>,greater<int> >pq;
	int ans=-1;
	for(int i=0,j=0;i<N/2;++i)if(IsSame(1,1+i*2,N*2-1-i*2,N*2-1))
	{
		const int z=1+i*2;
		for(;j<(int)sot.size()&&sot[j].first<=z+1;++j)
		{
			pq.push(sot[j].second);
		}
		const int mx=((N-1)+(z+1))/2;
		if(!pq.empty())
		{
			for(;;)
			{
				const int u=pq.top();pq.pop();
				if(pq.empty()||pq.top()>mx)
				{
					const int ta=u*2-z-2;
					if(ta>ans)ans=ta;
					pq.push(u);break;
				}
			}
		}
		if(z>ans)ans=z;
//		printf("z[%d]=%d\n",i,z[i]);
	}
	assert(ans&1);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("pre10f.in","r",stdin);
//	static char str[1000001];
	scanf("%d%s",&N,S);
	for(int i=N-1;i>=1;--i)S[i*2+1]=S[i],S[i*2]='z'+1;
	S[1]=S[0];
	PS[0]=0,POW[0]=1;
	for(int i=1;i<N*2;++i)PS[i]=(PS[i-1]*BASE+(S[i]-'a'))%MOD,POW[i]=POW[i-1]*BASE%MOD;
	printf("%d\n",(Solve()+1)/2);
	return 0;
}
