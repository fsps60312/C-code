#include<cstdio>
#include<vector>
using namespace std;
int N,S[100000],DP[100000],PRE[100000];
vector<int>MOVE[100000];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	for(int i=0;i<N;i++)
	{
		S[i]--;
		if(S[i]>=N||S[i]<0||i-S[i]<0)continue;
		MOVE[S[i]].push_back(i);
	}
	int len=0;
	for(int v=0;v<N;v++)
	{
		vector<int>ans;
		for(int i=0;i<MOVE[v].size();i++)
		{
			const int &idx=MOVE[v][i];
			int l=0,r=len,mid;
			while(l<r)
			{
				mid=(l+r)/2;
				if(idx-v>=DP[mid]-S[DP[mid]])l=mid+1;
				else r=mid;
			}
			if(l==0)PRE[idx]=-1;
			else PRE[idx]=DP[l-1];
			ans.push_back(l);
		}
		for(int i=0;i<ans.size();i++)
		{
			DP[ans[i]]=MOVE[v][i];
			if(ans[i]==len)len++;
		}
	}
	printf("%d\n",len);
	vector<int>ans;
	for(int idx=DP[len-1];idx!=-1;idx=PRE[idx])ans.push_back(idx);
	for(int i=0;i<ans.size();i++)
	{
		if(i)printf(" ");
		printf("%d",ans[i]);
	}
	puts("");
	return 0;
}
