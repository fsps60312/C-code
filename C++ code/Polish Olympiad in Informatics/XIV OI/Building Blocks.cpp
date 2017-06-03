#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int N,A[100001];
vector<pair<int,int> >S;
int Val(const int i){return S[i].second-S[i].first;}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		S.clear();
		for(int i=1;i<=N;i++)scanf("%d",&A[i]),S.push_back(make_pair(A[i],i));
//		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		//0<=i-A[i]<=j-A[j]...(1)
		//i<j.................(2)
		//A[i]<A[j]...........(3)
		//A[j]-A[i]<=j-i
		//(1)+(3)=>(2)
		static int pre[100000],dp[100000];
		sort(S.begin(),S.end());
		int ans=0;
		for(int i=0;i<N;i++)if(Val(i)>=0)
		{
			int l=0,r=ans;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(Val(i)>=Val(dp[mid]))l=mid+1;
				else r=mid;
			}
			dp[r]=i;
			if(r==ans)++ans;
			pre[i]=(r==0?-1:dp[r-1]);
		}
		vector<int>reserve;
		assert(ans>=1);
		for(int cur=dp[ans-1];cur!=-1;cur=pre[cur])reserve.push_back(S[cur].second);
		sort(reserve.begin(),reserve.end());
		assert((int)reserve.size()==ans);
		vector<int>bns;
		for(int i=0,removed=0,cur=1;i<ans;i++)
		{
			printf("A[%d]=%d\n",reserve[i],A[reserve[i]]);
			while(removed<reserve[i]-A[reserve[i]])bns.push_back(cur++),++removed;
			assert(cur<=reserve[i]);
			cur=reserve[i]+1;
		}
		printf("%llu\n",bns.size());
		for(int i=0;i<(int)bns.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",bns[i]);
		}
		puts("");
	}
	return 0;
}
