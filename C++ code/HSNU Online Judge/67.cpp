#include<cstdio>
#include<vector>
using namespace std;
int N,DP[100000],PRE[100000];
vector<int>S[100000];
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)S[i].clear();
	for(int i=0,v;i<N;i++)
	{
		scanf("%d",&v);
		v--;
		if(v>=N||v<0||v-i<0)continue;
		S[v].push_back(v-i);
	}
	int len=0;
	for(int i=0;i<N;i++)
	{
		vector<int>seq;
		for(int j=0;j<S[i].size();j++)
		{
			const int &v=S[i][j];
			int l=0,r=len,mid;
			while(l<r)
			{
				mid=(l+r)/2;
				if(v>=DP[mid])l=mid+1;
				else r=mid;
			}
			seq.push_back(l);
			if(l==0)PRE[i-S[i][j]]=-1;
			else PRE[i-S[i][j]]=DP[l-1];
		}
		for(int j=0;j<seq.size();j++)
		{
			DP[seq[j]]=S[i][j];
			if(seq[j]==len)len++;
		}
	}
	printf("%d\n",len);
	for(int u=DP[len-1];
	return 0;
}
