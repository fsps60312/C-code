#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int L,R;
int SG[1000000];
int main()
{
	while(scanf("%d%d%d",&L,&R,&SG[0])==3)
	{
		for(int i=1;i<=100;i++)
		{
			vector<int>s;
			for(int j=i-L;j>=i-R&&j>=0;j--)s.push_back(SG[j]);
			sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());
			for(SG[i]=0;SG[i]<(int)s.size()&&s[SG[i]]==SG[i];SG[i]++);
		}
		for(int i=0;i<=100;i++)printf("%d ",SG[i]);puts("");
	}
	return 0;
}
