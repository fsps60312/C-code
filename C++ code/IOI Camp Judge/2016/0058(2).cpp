#include<cstdio>
#include<cassert>
#include<set>
#include<map>
#include<vector>
using namespace std;
int N;
bool EDGE[1<<12][1<<12];
struct Ans
{
	int a,b,c;
	Ans(){}
	Ans(const int _a,const int _b,const int _c):a(_a),b(_b),c(_c){}
};
vector<Ans>ANS;
void Process(const int u)
{
	vector<int>ch;
	for(int i=1;i<N;i++)if(EDGE[u][i])ch.push_back(i);
	assert((int)ch.size()%2==0);
	for(int i=0;i<(int)ch.size();i+=2)
	{
		EDGE[u][ch[i]]=EDGE[ch[i]][u]=false;
		EDGE[u][ch[i+1]]=EDGE[ch[i+1]][u]=false;
		EDGE[ch[i]][ch[i+1]]=EDGE[ch[i+1]][ch[i]]=false;
		ANS.push_back(Ans(u,ch[i],ch[i+1]));
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N),N=1<<N;
		for(int i=1;i<N;i++)for(int j=1;j<N;j++)EDGE[i][j]=(i!=j);
		ANS.clear();
		for(int i=1;i<N;i++)Process(i);
		for(const Ans &a:ANS)printf("%d %d %d\n",a.a,a.b,a.c);
//		puts("");
	}
	return 0;
}
