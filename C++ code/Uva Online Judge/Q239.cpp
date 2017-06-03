#include<cstdio>
#include<stack>
#include<queue>
using namespace std;
#define LL long long
int N,MAT[7000],VIS[7000];
stack<int> S1,S2,S3;
queue<int> Q;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
LL lcm(LL a,LL b){return a/gcd(a,b)*b;}
LL getCYC(int p)
{
	int u=MAT[p];
	for(LL ans=1LL;;ans++,u=MAT[u])if(u==p)return ans;
}
int main()
{
	while(scanf("%lld",&N)&&N)
	{
		for(int i=0;i<N;i++)Q.push(i);
		for(;;)
		{
			if(S1.size()==4)
			{
				while(S1.size())Q.push(S1.top()),S1.pop();
				if(S2.size()==11)
				{
					while(S2.size())Q.push(S2.top()),S2.pop();
					if(S3.size()==11)
					{
						while(S3.size())Q.push(S3.top()),S3.pop();
						Q.push(Q.front()),Q.pop();
						break;
					}
					else S3.push(Q.front()),Q.pop();
				}
				else S2.push(Q.front()),Q.pop();
			}
			else S1.push(Q.front()),Q.pop();
		}
		for(int i=0;i<N;i++)VIS[i]=0,MAT[i]=Q.front(),Q.pop();
		LL ans=1LL;
		for(int i=0;i<N;i++)
		{
			if(VIS[i])continue;
			ans=lcm(ans,getCYC(i));
		}
		printf("%lld balls cycle after %lld days.\n",N,ans&1LL?ans:ans>>1);
	}
	return 0;
}
