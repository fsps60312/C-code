#include<cstdio>
#include<cassert>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
map<int,int>SG;
int GetSG(const int s)
{
	{const auto it=SG.find(s);if(it!=SG.end())return it->second;}
	bool *vis=new bool[31];
	for(int i=0;i<=30;i++)vis[i]=false;
	for(int i=0;i<=30;i++)if(s&(1<<i))
	{
		int nxts=s;
		for(int j=1;(i+1)*j-1<=30;j++)nxts&=~(1<<((i+1)*j-1));
		vis[GetSG(nxts)]=true;
	}
	int &ans=SG[s]=0;
	for(;vis[ans];ans++);
	delete[]vis;
	return ans;
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	SG[0]=0;
//	for(int i=0;i<=30;i++)printf("%d %d\n",(1<<i)-1,GetSG((1<<i)-1));
	if(true)
	{
		int *ans=new int[31]{0,1,2,1,4,3,2,1,5,6,2,1,8,7,5,9,8,7,3,4,7,4,2,1,10,9,3,6,11,12,14};
		for(int i=0;i<=30;i++)SG[(1<<i)-1]=ans[i];
	}
	while(scanf("%d",&N)==1)
	{
		int ans=0;
		set<int>all;
		for(int i=2;i<=N;i++)if(all.find(i)==all.end())
		{
			int n=1,cnt=0;
			while(n<=N/i)n*=i,cnt++,all.insert(n);
			if(cnt==1)
			{
				while(!all.empty()&&*all.begin()<=i)all.erase(all.begin());
				if(((N-i+1)-(int)all.size())&1)ans^=1;
				break;
			}
			else ans^=GetSG((1<<cnt)-1);
		}
		ans^=1;
//		printf("ans=%d\n",ans);
		puts(ans==0?"Petya":"Vasya");
//		printf("ans=%d\n",ans);
//		assert(0);
	}
	return 0;
}
