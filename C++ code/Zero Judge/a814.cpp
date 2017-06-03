#include<cstdio>
#include<queue>
#include<cassert>
using namespace std;
int T,N,M,S[1000000],CNT[1000001];
priority_queue<int,vector<int>,greater<int> >L;
priority_queue<int>R;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=1;i<=M;i++)CNT[i]=0;
		int sum=0;
		for(int i=0;i<N;i++)if(CNT[S[i]]++==1)sum++;
		for(int i=1;i<=M;i++)if(!CNT[i])L.push(i),R.push(i);
		bool found=false;
		for(int i=N-1;i>=0;i--)
		{
			CNT[S[i]]--;
			if(CNT[S[i]]==0)L.push(S[i]),R.push(S[i]);
			else if(CNT[S[i]]==1)sum--;
			if(sum==0&&R.top()>S[i])
			{
				found=true;
				bool changed=false;
				for(int j=i+1;j<N||!changed;)
				{
					if(!changed&&L.top()>S[i])
					{
						changed=true;
						S[i]=L.top();
					}
					else if(j<N)S[j++]=L.top();
					L.pop();
				}
				while(!R.empty())R.pop();
				while(!L.empty())L.pop();
				break;
			}
		}
		assert(found);
		printf("%d",S[0]);
		for(int i=1;i<N;i++)printf(" %d",S[i]);
		puts("");
	}
	return 0;
}
