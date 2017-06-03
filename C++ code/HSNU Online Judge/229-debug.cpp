#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
int N,K,s[100005],L[100005],R[100005],Ls[100005],Rs[100005];
struct Cable
{
	int l,r,p;
	bool operator<(Cable b)const{return p>b.p;}
};
priority_queue<Cable>pq;
int main()
{
	freopen("in.txt","r",stdin);
	int i,ans=0,x,y;
	int add;
	scanf("%d%d",&N,&K);
	for(i=0;i<N;i++)
	{
		scanf("%d",&s[i]);
		L[i]=R[i]=i;
		Ls[i]=Rs[i]=0;
		if(i)
		{
			L[i]=i-1;
			Ls[i]=s[i]-s[i-1];
			Rs[i-1]=s[i]-s[i-1];
			pq.push((Cable){i-1,i,s[i]-s[i-1]});
		}
		if(i<N-1)R[i]=i+1;
	}
	for(i=0;i<K;i++)
	{
		Cable c;
		do{c=pq.top(),pq.pop();}while(R[c.l]!=c.r||L[c.r]!=c.l);
		ans+=c.p;
		if(L[c.l]!=c.l&&R[c.r]!=c.r)//left cable and right cable not used
		{
			add=-c.p;
			add+=Ls[c.l];
			add+=Rs[c.r];
			lc=L[c.l],rc=R[c.r];
			R[lc]=rc,L[rc]=lc;
			Ls[rc]=Rs[lc]=add;
			pq.push((Cable){lc,rc,add});
			L[c.l]=c.l,R[c.l]=c.l;
			L[c.r]=c.r,R[c.r]=c.r;
		}
		else if(R[c.r]!=c.r)R[c.l]=c.l,L[R[c.r]]=R[c.r];
		else if(L[c.l]!=c.l)L[c.r]=c.r,R[L[c.l]]=L[c.l];
	}
	printf("%d\n",ans);
}
