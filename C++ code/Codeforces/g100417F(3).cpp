#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int N,K;
int Mod(const int a){return (a%(N*2)+(N*2))%(N*2);}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("factor.in","r",stdin);
	freopen("factor.out","w",stdout);
	scanf("%d",&N);
	vector<pair<int,int> >ans;
	for(int i=1;i<N*2;i++)
	{
		ans.push_back(make_pair(0,i)); 
		int l=i,r=i;
		for(int j=0;j<N-1;j++)
		{
			l=Mod(l-1),r=Mod(r+1);
			if(l==0)l=Mod(l-1);
			if(r==0)r=Mod(r+1);
			ans.push_back(make_pair(min(l,r),max(l,r)));
		}
	}
	scanf("%d",&K);
	for(int i=0,v,sum=0;i<K;i++)
	{
		if(i)puts("");
		scanf("%d",&v);
		for(int j=sum;j<sum+v*N;j++)printf("%d %d\n",ans[j].first+1,ans[j].second+1);
		sum+=v*N;
	}
	return 0;
}
