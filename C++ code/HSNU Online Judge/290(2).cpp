#include<cstdio>
#include<cstdlib>
#include<queue>
#include<ctime>
int N,SZ;
//#include "interactive/290.h"

const int MAXN=1000;
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
	return N;
}
void answer(int *a,int *b)
{
	/*printf("switch:");
	for(int i=0;i<N;i++)printf(" %d",a[i]);
	printf("\nswitch:");
	for(int i=0;i<N;i++)printf(" %d",A_S[i]);
	printf("\ndoor:");
	for(int i=0;i<N;i++)printf(" %d",b[i]);
	printf("\ndoor:");
	for(int i=0;i<N;i++)printf(" %d",S_D[i]);
	printf("\n");*/
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


using namespace std;
struct St
{
	int door,l,r,id;//dep
	/*bool operator<(St a)const
	{
		if(door!=a.door) door>a.door;
		return step>a.step;
	}*/
};
St ST[40000];
int ANS_D[5000];
void buildtree(int id,int l,int r)
{
	St &s=ST[id];
	s.id=id;
	//s.step=0;
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
bool get_betterswitch(int id)
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
	else if(b<a)
	{
		pushswitch(id);
		s.door=b;
		//s.swc=0;
	}
	else return false;
	return true;
}
void termin()
{
	int a[10];
	for(int i=0;;i--)
	{
		a[i]=100;
	}
}
int TEST[5000];
int main()
{
	N=Initialize();
	SZ=1;
	for(int i=0;i<N;i++)
	{
		SWITCH[i]=0;
	}
	buildtree(1,0,N-1);
	queue<St> pq;
	pq.push(ST[1]);
	int step=1;
	while(!pq.empty())
	{
		St s=pq.front();pq.pop();
		if(s.door==-1)
		{
			if(!get_betterswitch(s.id))
			{
				//ST[s.id].step=step++;
				ST[s.id].door=-1;
				pq.push(ST[s.id]);
				continue;
			}
			//else printf("(%d,%d)=%d\n",ST[s.id].l,ST[s.id].r,ST[s.id].door);
		}
		if(s.l==s.r)continue;
		if(!get_betterswitch(s.id*2))
		{
			//ST[s.id*2].step=step++;
			ST[s.id*2].door=-1;
		}
		//else printf("(%d,%d)=%d\n",ST[s.id*2].l,ST[s.id*2].r,ST[s.id*2].door);
		if(!get_betterswitch(s.id*2+1))
		{
			//ST[s.id*2+1].step=step++;
			ST[s.id*2+1].door=-1;
		}
		//else printf("(%d,%d)=%d\n",ST[s.id*2+1].l,ST[s.id*2+1].r,ST[s.id*2+1].door);
		pq.push(ST[s.id*2]);
		pq.push(ST[s.id*2+1]);
	}
	get_ANS(1,0,N-1);
	for(int i=0;i<N;i++)TEST[i]=0;
	for(int i=0;i<N;i++)
	{
		int &j=ANS_D[i];
		if(j<0||j>=N||TEST[j])termin();
		TEST[j]=1;
	}
	answer(SWITCH,ANS_D);
	return 0;
}
