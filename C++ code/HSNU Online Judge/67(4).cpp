#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
int N,S[100000],DP[100000],PRE[100000];
int HEAD[100000],NEXT[100000],MOVE[100000],SZ;
void Insert(const int &i,const int &v)
{
	NEXT[SZ]=HEAD[i];
	MOVE[SZ]=v;
	HEAD[i]=SZ++;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	for(int i=0;i<N;i++)HEAD[i]=-1;
	SZ=0;
	for(int i=0;i<N;i++)
	{
		S[i]--;
		if(S[i]>=N||S[i]<0||i-S[i]<0)continue;
		Insert(S[i],i);
	}
	int len=0;
	for(int v=0;v<N;v++)
	{
		static vector<int>ans;
		ans.clear();
		for(int u=HEAD[v];u!=-1;u=NEXT[u])
		{
			const int &idx=MOVE[u];
			assert(S[idx]==v);
			int l=0,r=len,mid;
			while(l<r)
			{
				mid=(l+r)/2;
				if(idx-S[idx]>=DP[mid]-S[DP[mid]])l=mid+1;
				else r=mid;
			}
			if(l==0)PRE[idx]=-1;
			else PRE[idx]=DP[l-1];
			ans.push_back(l);
		}
		for(int i=0,u=HEAD[v];i<ans.size();i++,u=NEXT[u])
		{
			if(ans[i]==len||MOVE[u]-S[MOVE[u]]<DP[ans[i]]-S[DP[ans[i]]])DP[ans[i]]=MOVE[u];
			if(ans[i]==len)len++;
		}
	}
	vector<int>fit;
	for(int idx=DP[len-1];idx!=-1;idx=PRE[idx])fit.push_back(idx);
	sort(fit.begin(),fit.end());
	assert(fit.size()==len);
	int removed=0;
	vector<int>ans;
	for(int i=0;i<fit.size();i++)
	{
		const int &goal=fit[i]-S[fit[i]];
		int cnt=goal-removed;
		assert(cnt>=0);
		for(;cnt>0;cnt--,removed++)ans.push_back(fit[i]-cnt);
		assert(removed==goal);
	}
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++)
	{
		assert(ans[i]>=0);
		if(i)
		{
			printf(" ");
			assert(ans[i-1]<ans[i]);
		}
		printf("%d",ans[i]+1);
	}
	puts("");
	return 0;
}
