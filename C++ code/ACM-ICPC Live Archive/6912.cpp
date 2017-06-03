#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,K,S[1000],B;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		for(int i=0;i<K;i++)scanf("%d",&S[i]);
		sort(S,S+K);
		B=0;
		while(B+1<K&&S[B]*S[B+1]<=N)B++;
		int ans=0;
		for(int s=0;s<(1<<B);s++)
		{
			static bool lamp[1001];
			for(int i=2;i<=N;i++)lamp[i]=false;
			for(int i=0;i<B;i++)if(s&(1<<i))
			{
				for(int j=S[i];j<=N;j+=S[i])lamp[j]^=true;
			}
			for(int i=B;i<K;i++)
			{
				int cnt=0;
				for(int j=S[i];j<=N;j+=S[i])
				{
					lamp[j]^=true;
					if(lamp[j])cnt++;
					else cnt--;
				}
				if(cnt<0)for(int j=S[i];j<=N;j+=S[i])lamp[j]^=true;
			}
			int ta=0;
			for(int i=2;i<=N;i++)if(lamp[i])ta++;
			if(ta>ans)ans=ta;
		}
		static int kase=1;
		printf("Case #%d: %d\n",kase++,ans);
	}
	return 0;
}
