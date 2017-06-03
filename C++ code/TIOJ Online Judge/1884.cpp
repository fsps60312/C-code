#include<cstdio>
#include<cassert>
#include<utility>
using namespace std;
int N,K,L;
vector<pair<int,int> >S;
LL SUM[10000001];
void InputS()
{
	S.resize(1);
	int pre;scanf("%d",&pre);
	S.push_back(make_pair(pre,1));
	for(int i=0,j=0,v;i<N;i++)
	{
		scanf("%d",&v);
		if(v==pre)S[j].second++;
		else S.push_back(make_pair(pre=v,1));
	}
	SUM[0]=0LL;
	for(int i=1;i<(int)S.size();i++)SUM[i]
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&N,&K,&L);
	}
	return 0;
}
