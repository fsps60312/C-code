#include<cstdio>
#include<vector>
const int MXN=2147483647;
void getmin(int &a,int b){if(b<a)a=b;}
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
using namespace std;
int Z,R,L,N,MIN,COST[1000000],ANS[1000000],VIS[1000000];
vector<int> HIST;
void SetCost(int i,int v,int r)
{
	if(VIS[i]!=r)return;
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
	if(i!=L)termin();
	BOOK.push_back(Bookcase(i,i-1));
}
struct Cost
{
	int c,m;
	Cost(){}
	Cost(int c,int m):c(c),m(m){}
};
int GetIdx(vector<Cost> &cst,int m,int d)
{
	int l=0,r=cst.size()-1,mid;
	while(l<r)
	{
		mid=(l+r+1)/2;
		if(m-cst[mid].m<d)r=mid-1;
		else l=mid;
	}
	return l;
}
void BuildLCost(int r)
{
	Cost sum=Cost(0,0);
	vector<Cost> cst;
	cst.push_back(sum);
	for(int i0=1;i0<BOOK.size();i0++)
	{
		Bookcase &b=BOOK[i0];
		for(int i=BOOK[i0-1].r+1;i<b.l;i++)SetCost(i,0,r);
		sum.m+=b.l-BOOK[i0-1].r-1;
		if(sum.m)sum.c++;
		if(cst[cst.size()-1].c<sum.c)cst.push_back(sum);
		for(int i=b.r,m=1,cn=cst.size()-1;i>=b.l&&m<=sum.m;i--,m++)
		{
			cn=GetIdx(cst,sum.m,m);
			SetCost(i,sum.c-cst[cn].c,r);
		}
	}
//	for(int i=0;i<cst.size();i++)printf(" (%d,%d)",cst[i].m,cst[i].c);printf("\n");
}
void BuildRCost(int r)
{
	Cost sum=Cost(0,0);
	vector<Cost> cst;
	cst.push_back(sum);
	for(int i0=BOOK.size()-2;i0>=0;i0--)
	{
		Bookcase &b=BOOK[i0];
		for(int i=BOOK[i0+1].l-1;i>b.r;i--)SetCost(i,0,r);
		sum.m+=BOOK[i0+1].l-b.r-1;
		if(sum.m)sum.c++;
		if(cst[cst.size()-1].c<sum.c)cst.push_back(sum);
		for(int i=b.l,m=1,cn=cst.size()-1;i<=b.r&&m<=sum.m;i++,m++)
		{
			cn=GetIdx(cst,sum.m,m);
			SetCost(i,sum.c-cst[cn].c,r);
		}
	}
}
void BuildCost(int r)
{
	BuildLCost(r);
	BuildRCost(r);
//	for(int i=0;i<L;i++)printf(" %d",COST[i]);printf("\n");
//	for(int i=0;i<L;i++)printf(" %d",ANS[i]);printf("\n");
}
void AddToAns(int r)
{
	for(int i0=0;i0<HIST.size();i0++)
	{
		int &i=HIST[i0];
		int c=COST[i];COST[i]=-2;
		if(ANS[i]==-2)ANS[i]=c;
		else ANS[i]+=c;
		VIS[i]++;
	}
	HIST.clear();
}
void ShowAns()
{
	for(int i=0;i<L;i++)
	{
//		printf(" %d",ANS[i]);
		if(VIS[i]==R)getmin(MIN,ANS[i]);
	}
	printf("%d\n",MIN);
	bool printed=false;
	for(int i=0;i<L;i++)
	{
		if(VIS[i]==R&&ANS[i]==MIN)
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
//	freopen("in.txt","r",stdin);
	scanf("%d",&Z);
	while(Z--)
	{
		scanf("%d%d",&R,&L);
		MIN=MXN;
		for(int i=0;i<L;i++)ANS[i]=0,VIS[i]=0,COST[i]=-2;
		for(int i=0;i<R;i++)
		{
			scanf("%d",&N);
			PutBookcase();
			BuildCost(i);
			AddToAns(i);
		}
		ShowAns();
	}
	return 0;
}
