#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int T,N,S[100];
struct Ans
{
	int type,column;
	Ans(){}
	Ans(const int &t,const int &c):type(t),column(c){}
};
vector<Ans>ANS;
struct Block
{
	int buttom[4],body[4],sz;
	Block(){}
	Block(const int &sz,int *bo,int *bu):sz(sz){for(int i=0;i<sz;i++)buttom[i]=bu[i],body[i]=bo[i];}
	void Measure(const int &c,bool &suc,int &differ)
	{
		for(int i=1,v=S[c]-buttom[0];i<sz;i++)if(S[c+i]-buttom[i]!=v){suc=false;return;}
		for(int i=0;i<sz;i++)S[c+i]+=body[i];
		suc=true;
		differ=0;
		int mx=S[0];
		for(int i=1;i<N;i++)
		{
			mx=max(mx,S[i]);
			if(S[i]!=S[i-1])differ++;
		}
		differ+=100*mx;
		for(int i=0;i<sz;i++)S[c+i]-=body[i];
	}
	void Stack(const int &c){for(int i=0;i<sz;i++)S[c+i]+=body[i];}
}BLOCK[19];
void BuildBlocks()
{
	int sz[19]={1,4,2,3,3,2,2,3,3,2,2,3,3,3,3,2,2,2,2};
	int bo[19][4]={{4},{1,1,1,1},{2,2},{1,2,1},{1,2,1},
	{2,2},{2,2},{1,2,1},{1,2,1},{1,3},
	{3,1},{2,1,1},{1,1,2},{2,1,1},{1,1,2},
	{3,1},{1,3},{3,1},{1,3}};
	int bu[19][4]={{0},{0,0,0,0},{0,0},{1,0,0},{0,0,1},
	{1,0},{0,1},{0,0,0},{1,0,1},{1,0},
	{0,1},{0,1,1},{1,1,0},{0,0,0},{0,0,0},
	{0,2},{2,0},{0,0},{0,0}};
	for(int i=0;i<19;i++)BLOCK[i]=Block(sz[i],bo[i],bu[i]);
}
bool StackBlock()
{
	Ans ans=Ans(-1,-1);
	int dif=INF;
	for(int i=0;i<19;i++)
	{
		Block &b=BLOCK[i];
		for(int c=0;c+b.sz<=N;c++)
		{
			static bool sus;
			static int differ;
			b.Measure(c,sus,differ);
			if(sus&&differ<dif)dif=differ,ans.column=c,ans.type=i;
		}
	}
//	printf("column=%d,type=%d,dif=%d\n",ans.column,ans.type,dif);
	assert(ans.type!=-1);
	ANS.push_back(ans);
	BLOCK[ans.type].Stack(ans.column);
//	for(int i=0;i<N;i++)printf(" %d",S[i]);puts("");
	return dif%100==0;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	BuildBlocks();
//	for(int i=0;i<19;i++)
//	{
//		Block &b=BLOCK[i];
//		printf("i=%d\n",i);
//		for(int j=0;j<b.sz;j++)printf(" %d",b.buttom[j]);puts("");
//		for(int j=0;j<b.sz;j++)printf(" %d",b.body[j]);puts("");
//	}
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d",&N);
			ANS.clear();
			for(int i=0;i<N;i++)scanf("%d",&S[i]);
			while(!StackBlock());
			for(int i=0;i<ANS.size();i++)
			{
				printf("%d %d\n",++ANS[i].type,++ANS[i].column);
			}
			puts("-1 -1");
		}
	}
	return 0;
}
