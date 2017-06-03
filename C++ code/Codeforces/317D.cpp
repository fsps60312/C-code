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
//	for(int i=0;i<8;i++)printf("SG(%d)=%d\n",i,GetSG(0x0fffffff));
//	printf("%d %d\n",0x0fffffff,GetSG(0x0fffffff));
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
