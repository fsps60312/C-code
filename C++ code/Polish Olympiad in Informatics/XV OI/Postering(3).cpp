#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,H[250000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0,d;i<N;i++)scanf("%d%d",&d,&H[i]);
		vector<int>deq;deq.push_back(H[0]);
		int ans=0;
		for(int i=1;i<N;i++)
		{
			while(!deq.empty()&&deq.back()>H[i])deq.pop_back(),ans++;
			if(deq.empty()||deq.back()<H[i])deq.push_back(H[i]);
		}
		ans+=(int)deq.size();
		printf("%d\n",ans);
	}
	return 0;
}
