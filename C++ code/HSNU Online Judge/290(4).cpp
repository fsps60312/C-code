#include<cstdio>
#include<cstdlib>
#include<queue>
#include<ctime>
using namespace std;
int N;
#include "interactive/290.h"
/*
const int MAXN=500;
int S_D[MAXN];
int A_S[MAXN];
int ts[MAXN];
int querytime=0;
int Initialize()
{
	srand(time(NULL));
	for(int i=0;i<MAXN;i++)
	{
		A_S[i]=rand()&1;
		int j;
		do
		{
			j=(rand()%MAXN+MAXN)%MAXN;
		}while(ts[j]);
		ts[j]=1;
		S_D[i]=j;
	}
	return MAXN;
}
int tryCombination(int *array)
{
	querytime++;
	for(int i=0;i<N;i++)
	{
		ts[S_D[i]]=array[i]^A_S[i];
	}
	//printf("switch:");for(int i=0;i<N;i++)printf(" %d",array[i]);printf("\nresult:");for(int i=0;i<N;i++)printf(" %d",ts[i]);printf("\n");
	for(int i=0;i<N;i++)
	{
		if(ts[i])
		{
			//printf("return: %d\n",i);
			return i;
		}
	}
	//printf("return: %d\n",N);
	return -1;
}
void answer(int *a,int *b)
{
	//printf("switch:");
	//for(int i=0;i<N;i++)printf(" %d",a[i]);
	//printf("\nswitch:");
	//for(int i=0;i<N;i++)printf(" %d",A_S[i]);
	//printf("\ndoor:");
	//for(int i=0;i<N;i++)printf(" %d",b[i]);
	//printf("\ndoor:");
	//for(int i=0;i<N;i++)printf(" %d",S_D[i]);
	//printf("\n");
	bool correct=true;
	for(int i=0;i<N;i++)
	{
		if(A_S[i]!=a[i])correct=false;
		if(b[i]!=S_D[i])correct=false;
	}
	if(correct)printf("Correct\n");
	else printf("Wrong\n");
	printf("%d\n",querytime);
}
*/
int ONOFF[5001],VIS[5001],StoD[5001];//,DtoS[5000];
void turnonoff(int l,int r)
{
	for(int i=l;i<=r;i++)
	{
		if(VIS[i])continue;
		ONOFF[i]^=1;
	}
}
int min(int &a,int &b){return a<b?a:b;}
int getswitch(int l,int r,int &d,int a)
{
	if(l==r)return l;
	int mid=(l+r)/2;
	turnonoff(l,mid);
	int b=tryCombination(ONOFF);
	if(b==-1)b=N;
	if(a!=b&&min(a,b)==d)
	{
		if(a>b)turnonoff(l,mid);
		return getswitch(l,mid,d,a>b?a:b);
	}
	else
	{
		turnonoff(mid+1,r);
		a=tryCombination(ONOFF);
		if(a==-1)a=N;
		//if(b==c)printf("error\n");
		if(b>a)turnonoff(mid+1,r);
		return getswitch(mid+1,r,d,a>b?a:b);
	}
}
int main()
{
	N=Initialize();
	for(int i=0;i<N;i++)
	{
		ONOFF[i]=0;
		VIS[i]=0;
	}
	for(int i=0;i<N;i++)
	{
		int a=tryCombination(ONOFF);
		if(a==-1)a=N;
		int s=getswitch(0,N-1,i,a);
		//printf("%d control door %d %d\n",s,i,tryCombination(ONOFF));
		VIS[s]=1;
		StoD[s]=i;
	}
	answer(ONOFF,StoD);
	return 0;
}
