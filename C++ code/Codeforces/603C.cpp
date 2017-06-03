#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,K;
//int GetSG(const int n)
//{
//	if(n==0)return 0;
//	vector<int>sg;
//	sg.push_back(GetSG(n-1));
//	if(n%2==0)sg.push_back(K%2?GetSG(n/2):0);
//	sort(sg.begin(),sg.end());
//	int ans=0;
//	for(int i=0;i<(int)sg.size()&&sg[i]==ans;i++)ans++;
//	return ans;
//}
int GetSG(const int n)
{
	if(n==0)return 0;
	if(K%2==0)
	{
		if(n==1)return 1;
		if(n==2)return 2;
		if(n==3)return 0;
		if(n==4)return 1;
		if(n==5)return 0;
		if(n==6)return 1;
		return n&1?0:1;
	}
	else
	{
		if(n==1)return 1;
		if(n==2)return 0;
		if(n==3)return 1;
		if(n==4)return 2;
		if(n==5)return 0;
		if(n==6)return 2;
		if(n==7)return 0;
		if(n==8)return 1;
		if(n%2)return 0;
		else return GetSG(n/2)==1?2:1;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
//		for(int i=0;i<100;i++)printf("%d ",GetSG(i));printf("%d\n",GetSG(100));
		int ans=0;
		for(int i=0,v;i<N;i++)scanf("%d",&v),ans^=GetSG(v);
		printf("%s\n",ans==0?"Nicky":"Kevin");
	}
	return 0;
}
