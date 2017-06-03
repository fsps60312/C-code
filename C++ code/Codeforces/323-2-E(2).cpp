#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int N,S[200000];
bool VIS[200000];
vector<int>MX,F;
int gcd(const int &a,const int &b){return b?gcd(b,a%b):a;}
int main()
{
	while(scanf("%d",&N)==1)
	{
		F.clear();
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=1;i<N;i++)F.push_back(gcd(i,N));
		sort(F.begin(),F.end());
		F.resize(unique(F.begin(),F.end())-F.begin());
		LL ans=0LL;
		for(int i=0;i<F.size();i++)
		{
			const int &f=F[i],n=N/f;
			MX.clear();
			for(int j=0;j<f;j++)
			{
				int mx=0;
				for(int k=0;k<n;k++)
				{
					mx=max(mx,S[k*f+j]);
				}
				MX.push_back(mx);
			}
			for(int i=0;i<N;i++)VIS[i]=(S[i]>=MX[i%f]);
			int idx=0,len;
			while(idx<N)
			{
				for(;idx<N&&!VIS[idx];idx++);
				if(idx==N)break;
				int cnt=0;
				queue<int>q;
				for(len=0;(len<N||(!q.empty()&&idx+len+1-q.front()<N))&&VIS[(idx+len)%N];len++)
				{
					if(len+1<N&&gcd(len+1,N)==f)
					{
						cnt++;
						q.push(len+1);
					}
					while(!q.empty()&&idx+len+1-q.front()>=N)
					{
						cnt--;
						q.pop();
					}
					ans+=cnt;
//					printf("f=%d idx=%d len=%d cnt=%d\n",f,idx,len+1,cnt);
//					if(!q.empty())printf("front=%d\n",q.front());
//					else puts("q.empty");
					while(!q.empty()&&idx+len+2-q.front()>=N)
					{
						cnt--;
						q.pop();
					}
				}
				idx+=len;
			}
		}
		printf("%I64d\n",ans);
//		break;
	}
	return 0;
}
