#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
void Swap(int *s,int *sloc,const int i1,const int i2)
{
	swap(sloc[s[i1]],sloc[s[i2]]);
	swap(s[i1],s[i2]);
}
int R,C;
bool ExchangeRow(int *s,int *sloc,const int r1,const int r2)
{
	if(r1==-1||r2==-1)return false;
	for(int i=0;i<C;i++)Swap(s,sloc,r1*C+i,r2*C+i);
	return true;
}
bool ExchangeColumn(int *s,int *sloc,const int c1,const int c2)
{
	if(c1==-1||c2==-1)return false;
	for(int i=0;i<R;i++)Swap(s,sloc,i*C+c1,i*C+c2);
	return true;
}
int A[1000000],B[1000000],*ALOC=new int[2000001]+1000000,*BLOC=new int[2000001]+1000000;
bool Solve()
{
	for(int v=-1000000;v<=1000000;v++)if(ALOC[v]!=-1)
	{
		const int r=ALOC[v]/C;
		if(!ExchangeRow(B,BLOC,r,BLOC[v]/C))return false; 
		for(int i=0;i<C;i++)if(BLOC[A[r*C+i]]%C!=i)if(!ExchangeColumn(B,BLOC,BLOC[A[r*C+i]]%C,i))return false;
		break;
	}
	for(int i=0;i<R;i++)
	{
		const int r=BLOC[A[i*C]]/C;
		if(r==-1)return false;
		for(int j=0;j<C;j++)if(A[i*C+j]!=B[r*C+j])return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&R,&C);
		for(int i=-1000000;i<=1000000;i++)ALOC[i]=BLOC[i]=-1;
		for(int i=0;i<R*C;i++)scanf("%d",&A[i]),ALOC[A[i]]=i;
		for(int i=0;i<R*C;i++)scanf("%d",&B[i]),BLOC[B[i]]=i;
		puts(Solve()?"TAK":"NIE");
	}
	return 0;
}
