#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
struct Span
{
	int l,r;
	Span(){}
	Span(const int _l,const int _r):l(_l),r(_r){}
}SPAN[500][500];
int H[500][500];
const Span &GetSPAN(const int r,const int c,const int h)
{
	if(r<0||c<0||r>=N||c>=M||H[r][c]>=h)return Span(INF,-INF);
	Span &ans=SPAN[r][c];
	if(ans.l!=-1)return ans;
	ans=Span(INF,-INF);
	static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
	for(int i=0;i<d;i++)
	{
		const Span tmp=GetSPAN(r+d[i][0],c+d[i][1],H[r][c]);
		getmin(ans.l,tmp.l),getmax(ans.r,tmp.r);
	}
	return ans;
}
int GetMinReservoir()
{
	int ans=-1,nowr=-1,mxr=-1;
	for(int i=0,prel=-1,prer=-1;i<M;i++)
	{
		const Span &s=GetSPAN(0,i,H[0][i]);
		if(s.l==INF)continue;
		if(s.l>nowr+1)
		{
			nowr=mxr;
		}
		assert(prel<=s.l),prel=s.l;
		assert(prer<=s.r),prer=s.r;
	}
}
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)scanf("%d%d",&H[i][j]),SPAN[i][j]=Span(-1,-1);
		for(int i=0;i<M;i++)SPAN[N-1][i]=Span(i,i);
		const int reservoir=GetMinReservoir();
	}
	return 0;
}
