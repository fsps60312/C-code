#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
int N,COLOR[100000];
vector<int>ET[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("bicoloring.in","r",stdin);
	freopen("bicoloring.out","w",stdout);
	scanf("%d",&N),N/=2;
	for(int i=0;i<N*2;i++)ET[i].clear();
	for(int i=0,a,b;i<N*2-1;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	vector<int>order;
	for(int i=0;i<N*2;i++)order.push_back(i);
	sort(order.begin(),order.end(),[](const int a,const int b)->bool{return ET[a].size()<ET[b].size();});
	for(int i=0;i<N*2;i++)COLOR[i]=i;
	for(int l=0,r=N*2-1;;l++,r--)
	{
		for(;r>l&&(int)(ET[r].size()+ET[l].size())>N;r--);
		if(r==l)break;
		COLOR[l]=COLOR[r];
	}
	map<int,int>trans;
	for(int i=0;i<N*2;i++)trans[COLOR[i]]=-1;
	{int cnt=0;for(auto &it:trans)it.second=++cnt;assert(cnt<=N+1);}
	for(int i=0;i<N*2;i++)
	{
		if(i)putchar(' ');
		printf("%d",trans[COLOR[i]]);
	}
	puts("");
	return 0;
}
