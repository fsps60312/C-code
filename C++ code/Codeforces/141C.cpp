#include<cstdio>
#include<cassert>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
vector<string>NAMES;
int N,CNT[3000];
bool Solve()
{
	vector<int>order;
	for(int i=0;i<N;i++)order.push_back(i);
	sort(order.begin(),order.end(),[](int a,int b){return CNT[a]<CNT[b];});
	vector<int>ids;
	for(const int i:order)
	{
		if(CNT[i]>(int)ids.size())return false;
		ids.insert(ids.begin()+CNT[i],i);
	}
	int *h=new int[N];
	for(int i=0;i<N;i++)h[ids[i]]=N-i;
	for(const int i:order)
	{
		printf("%s %d\n",NAMES[i].c_str(),h[i]);
	}
	delete[]h;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			static char name[11];
			scanf("%s%d",name,&CNT[i]);
			NAMES.push_back(name);
		}
		if(!Solve())puts("-1");
	}
	return 0;
}
