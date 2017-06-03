#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int A,B,T,RW[50000],RV[50000];
struct Toy
{
	int w,v;
}TOY[1000000];
int TW[50000],TV[50000],NXW[50000],NXV[50000];
bool cmp_Toy_v(Toy a,Toy b){if(a.v!=b.v)return a.v>b.v;return a.w<b.w;}
bool cmp_int(int a,int b){return a<b;}
int findnxW(int a){if(a>=A)return a;return NXW[a]==a?a:(NXW[a]=findnxW(NXW[a]));}
int findnxV(int a){if(a>=B)return a;return NXV[a]==a?a:(NXV[a]=findnxV(NXV[a]));}
int bsearch_RW(int w)
{
	int l=0,r=A;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(RW[mid]<=w)l=mid+1;
		else r=mid;
	}
	//printf("bsearch_RW(%d)=%d\n",w,r);
	return r;
}
int bsearch_RV(int v)
{
	int l=0,r=B;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(RV[mid]<=v)l=mid+1;
		else r=mid;
	}
	//printf("bsearch_RV(%d)=%d\n",v,r);
	return r;
}
bool possible(int t)
{
	for(int i=0;i<A;i++)
	{
		TW[i]=0;
		NXW[i]=i;
	}
	for(int i=0;i<B;i++)
	{
		TV[i]=0;
		NXV[i]=i;
	}
	for(int i=0;i<T;i++)
	{
		int pos=bsearch_RW(TOY[i].w);
		pos=findnxW(pos);
		while(pos<A&&TW[pos]>=t)
		{
			NXW[pos]=pos+1;
			pos=findnxW(pos);
		}
		if(pos>=A)
		{
			pos=bsearch_RV(TOY[i].v);
			//printf("pos=%d\n",pos);
			pos=findnxV(pos);
			while(pos<B&&TV[pos]>=t)
			{
				NXV[pos]=pos+1;
				pos=findnxV(pos);
			}
			if(pos>=B)
			{
				//printf("TOY w=%d v=%d\n",TOY[i].w,TOY[i].v);
				//for(int i=0;i<A;i++)printf(" %d(%d)",TW[i],RW[i]);printf("\n");
				//for(int i=0;i<B;i++)printf(" %d(%d)",TV[i],RV[i]);printf("\n");
				return false;
			}
			TV[pos]++;
		}
		else TW[pos]++;
	}
	return true;
}
int bsearch_ans()
{
	int l=0,r=T+2;
	while(l<r)
	{
		int mid=(l+r)/2;
		//printf("mid=%d\n",mid);
		if(!possible(mid))l=mid+1;
		else r=mid;
	}
	return l;
}
int main()
{
	//freopen("IN.txt","r",stdin);
	while(scanf("%d%d%d",&A,&B,&T)==3)
	{
		for(int i=0;i<A;i++)scanf("%d",&RW[i]);
		for(int i=0;i<B;i++)scanf("%d",&RV[i]);
		for(int i=0;i<T;i++)scanf("%d%d",&TOY[i].w,&TOY[i].v);
		sort(RW,RW+A,cmp_int);
		sort(RV,RV+B,cmp_int);
		sort(TOY,TOY+T,cmp_Toy_v);
		//for(int i=0;i<T;i++)printf("w=%d v=%d\n",TOY[i].w,TOY[i].v);
		int ans=bsearch_ans();
		//printf("%d\n",ans);
		if(ans>T)printf("-1\n");
		else printf("%d\n",ans);
		return 0;
	}
	return 0;
}
