#include<cstdio>
#include<vector>
const int MXN=2147483647;
void getmin(int &a,int b){if(b<a)a=b;}
using namespace std;
int Z,R,L,N,MIN,COST[1000000],ANS[1000000];
vector<int> HIST;
void SetCost(int i,int v)
{
	if(ANS[i]==-1)return;
	int &c=COST[i];
	if(c==-2)
	{
		HIST.push_back(i);
		c=v;
	}
	else getmin(c,v);
}
struct Bookcase
{
	int l,r;
	Bookcase(){}
	Bookcase(int l,int r):l(l),r(r){}
};
vector<Bookcase> BOOK;
void PutBookcase()
{
	int n,i=0;
	BOOK.clear();
	BOOK.push_back(Bookcase(0,-1));
	while(N--)
	{
		scanf("%d",&n);
		if(n==0)i++;
		else BOOK.push_back(Bookcase(i,i+n-1));
		i+=n;
	}
	if(i!=L)printf("error i=%d\n",i);
	BOOK.push_back(Bookcase(i,i-1));
}
struct Cost
{
	int c,m;
	Cost(){}
	Cost(int c,int m):c(c),m(m){}
};
void BuildLCost()
{
	Cost sum=Cost(0,0);
	vector<Cost> cst;
	cst.push_back(sum);
	for(int i0=1;i0<BOOK.size();i0++)
	{
		Bookcase &b=BOOK[i0];
		for(int i=BOOK[i0-1].r+1;i<b.l;i++)SetCost(i,0);
		sum.m+=b.l-BOOK[i0-1].r-1;
		if(sum.m)sum.c++;
		if(cst[cst.size()-1].c<sum.c)cst.push_back(sum);
		for(int i=b.r,m=1,cn=cst.size()-1;i>=b.l&&m<=sum.m;i--,m++)
		{
			while(sum.m-cst[cn].m<m)cn--;
			SetCost(i,sum.c-cst[cn].c);
		}
	}
//	for(int i=0;i<cst.size();i++)printf(" (%d,%d)",cst[i].m,cst[i].c);printf("\n");
}
void BuildRCost()
{
	Cost sum=Cost(0,0);
	vector<Cost> cst;
	cst.push_back(sum);
	for(int i0=BOOK.size()-2;i0>=0;i0--)
	{
		Bookcase &b=BOOK[i0];
		for(int i=BOOK[i0+1].l-1;i>b.r;i--)SetCost(i,0);
		sum.m+=BOOK[i0+1].l-b.r-1;
		if(sum.m)sum.c++;
		if(cst[cst.size()-1].c<sum.c)cst.push_back(sum);
		for(int i=b.l,m=1,cn=cst.size()-1;i<=b.r&&m<=sum.m;i++,m++)
		{
			while(sum.m-cst[cn].m<m)cn--;
			SetCost(i,sum.c-cst[cn].c);
		}
	}
}
void BuildCost()
{
	BuildLCost();
	BuildRCost();
	for(int i=0;i<L;i++)printf(" %d",COST[i]);printf("\n");
	for(int i=0;i<L;i++)printf(" %d",ANS[i]);printf("\n");
}
void AddToAns()
{
	for(int i0=0;i0<HIST.size();i0++)
	{
		int &i=HIST[i0];
		int c=COST[i];COST[i]=-2;
		if(c==-2)ANS[i]=-1;
		if(ANS[i]==-1)continue;
		if(ANS[i]==-2)ANS[i]=c;
		else ANS[i]+=c;
	}
	HIST.clear();
}
void ShowAns()
{
	for(int i=0;i<L;i++)
	{
		printf(" %d",ANS[i]);
		if(ANS[i]!=-1)getmin(MIN,ANS[i]);
	}
	printf("\n%d\n",MIN);
	bool printed=false;
	for(int i=0;i<L;i++)
	{
		if(ANS[i]==MIN)
		{
			if(printed)printf(" ");
			printf("%d",i);
			printed=true;
		}
	}
	printf("\n");
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&Z);
	while(Z--)
	{
		scanf("%d%d",&R,&L);
		MIN=MXN;
		for(int i=0;i<L;i++)ANS[i]=-2,COST[i]=-2;
		for(int i=0;i<R;i++)
		{
			scanf("%d",&N);
			PutBookcase();
			BuildCost();
			AddToAns();
		}
		ShowAns();
	}
	return 0;
}
