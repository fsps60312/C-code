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
int N,M,H[500][500];
Span GetSPAN(const int r,const int c,const int h)
{
	if(r<0||c<0||r>=N||c>=M||H[r][c]<=h)return Span(INF,-INF);
	Span &ans=SPAN[r][c];
	if(ans.l!=-1)return ans;
	ans=(r==0?Span(c,c):Span(INF,-INF));
	static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
	for(int i=0;i<4;i++)
	{
		const Span tmp=GetSPAN(r+d[i][0],c+d[i][1],H[r][c]);
		getmin(ans.l,tmp.l),getmax(ans.r,tmp.r);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)scanf("%d",&H[i][j]),SPAN[i][j]=Span(-1,-1);
		int reservoir=0,drought=0,mxr=-1;
		for(int i=0;i<M;i++)
		{
			const Span s=GetSPAN(N-1,i,-INF);
//			printf("(%d,%d)\n",s.l,s.r);
			if(s.l==INF)drought++;
			else if(drought==0&&s.l>mxr)reservoir++,mxr=s.r;
		}
		if(drought>0)printf("0\n%d\n",drought);
		else printf("1\n%d\n",reservoir);
		break;
	}
	return 0;
}
