#include "interactive/290.h"
#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
struct St
{
	int door,l,r,id;
	bool operator<(St a)const
	{
		return door>a.door;
	}
};
int N,SZ;
St ST[40000];
int ANS_D[5000];

/*
int Initialize(){return 4;}
int S_D[]={3, 1, 0, 2};
int A_S[]={1, 1, 1, 0};
int tryCombination(int *array)
{
	int ts[4];
	for(int i=0;i<N;i++)
	{
		ts[S_D[i]]=array[i]^A_S[i];
	}
	printf("switch:");
	for(int i=0;i<N;i++)printf(" %d",array[i]);
	printf("\nresult:");
	for(int i=0;i<N;i++)printf(" %d",ts[i]);
	printf("\n");
	for(int i=0;i<N;i++)
	{
		if(ts[i])
		{
			//printf("return: %d\n",i);
			return i;
		}
	}
	//printf("return: %d\n",N);
	return N;
}
void answer(int *a,int *b)
{
	printf("switch:");
	for(int i=0;i<N;i++)
	{
		printf(" %d",a[i]);
	}
	printf("\ndoor:");
	for(int i=0;i<N;i++)
	{
		printf(" %d",b[i]);
	}
	printf("\n");
}
*/

void buildtree(int id,int l,int r)
{
	St &s=ST[id];
	s.id=id;
	s.door=-1;
	s.l=l,s.r=r;
	if(l==r)return;
	int mid=(l+r)/2;
	buildtree(id*2,l,mid);
	buildtree(id*2+1,mid+1,r);
}
int SWITCH[5000];
void get_ANS(int id,int l,int r)
{
	//printf("(%d,%d)=%d\n",l,r,ST[id].door);
	if(l==r)
	{
		ANS_D[l]=ST[id].door;
		return;
	}
	int mid=(l+r)/2;
	get_ANS(id*2,l,mid);
	get_ANS(id*2+1,mid+1,r);
}
void pushswitch(int id)
{
	St &s=ST[id];
	for(int i=s.l;i<=s.r;i++)
	{
		SWITCH[i]^=1;
	}
}
void get_betterswitch(int id)
{
	St &s=ST[id];
	int a=tryCombination(SWITCH);
	pushswitch(id);
	int b=tryCombination(SWITCH);
	if(b>a)
	{
		s.door=a;
		//s.swc=1;
	}
	else
	{
		pushswitch(id);
		s.door=b;
		//s.swc=0;
	}
}
int main()
{
	N=Initialize();
	SZ=1;
	for(int i=0;i<N;i++)
	{
		SWITCH[i]=0;
	}
	buildtree(1,0,N-1);
	get_betterswitch(1);
	priority_queue<St> pq;
	pq.push(ST[1]);
	while(!pq.empty())
	{
		St s=pq.top();pq.pop();
		if(s.l==s.r)continue;
		get_betterswitch(s.id*2);
		get_betterswitch(s.id*2+1);
		pq.push(ST[s.id*2]);
		pq.push(ST[s.id*2+1]); 
	}
	get_ANS(1,0,N-1);
	answer(SWITCH,ANS_D);
	return 0;
}
