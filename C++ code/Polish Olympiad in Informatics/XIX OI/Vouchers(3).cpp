#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int M,N;
int S[1000001];
bool SOLD[1000001],VOUCHERED[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=1;i<=1000000;i++)SOLD[i]=VOUCHERED[i]=false,S[i]=0;
	scanf("%d",&M);
	for(int i=0,v;i<M;i++)scanf("%d",&v),VOUCHERED[v]=true;
	scanf("%d",&N);
	vector<long long>ans;
	long long cid=1LL;
	for(int i=0,a;i<N;i++)
	{
		scanf("%d",&a);
		int &v=S[a];
		if(v<1000000)
		{
			for(int j=0;j<a;)
			{
				v+=a;
				if(v>1000000)break;
				if(!SOLD[v])
				{
					SOLD[v]=true;
					if(VOUCHERED[v])ans.push_back(cid+j);
					j++;
				}
			}
		}
		cid+=a;
	}
	printf("%d\n",(int)ans.size());
	for(int i=0;i<(int)ans.size();i++)printf("%lld\n",ans[i]);
	return 0;
}
