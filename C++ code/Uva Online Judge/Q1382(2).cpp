#include<cstdio>
#include<algorithm>
using namespace std;
int N,Y[100],YN,X[100],XN;
struct Star
{
	int x,y;
	bool operator<(Star a)const{return x<a.x;}
}S[100];
void getmax(int &a,int b){if(b>a)a=b;}
bool AtRange(int v,int l,int r){return v>=l&&v<=r;}
int solve()
{
	if(YN<=2||XN<=2)return N;
	int ans=0;
	for(int i1=0;i1<YN;i1++)
	{
		for(int i2=0;i2<YN;i2++)
		{
			int &y1=Y[i1],&y2=Y[i2],l,r;
			int onx=0,ln=0;
			for(l=0;S[l].x==X[0];l++)if(AtRange(S[l].y,y1,y2))onx++;
			ln=onx;
			for(r=1;r<XN;r++)
			{
				int addln=0;
				for(onx=0;S[l].x==X[r];l++)
				{
					if(AtRange(S[l].y,y1,y2))
					{
						onx++;
						if(S[l].y==y1||S[l].y==y2)addln++;
					}
				}
				getmax(ans,ln+onx);
				ln+=addln;
				if(onx>ln)ln=onx;
			}
		}
	}
	return ans;
}
int main()
{
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			scanf("%d%d",&S[i].x,&S[i].y);
			Y[i]=S[i].y;
			X[i]=S[i].x;
		}
		sort(S,S+N),sort(Y,Y+N),sort(X,X+N);
		YN=XN=0;
		for(int i=0;i<N;i++)if(i==0||Y[i]!=Y[i-1])Y[YN++]=Y[i];
		for(int i=0;i<N;i++)if(i==0||X[i]!=X[i-1])X[XN++]=X[i];
		printf("Case %d: %d\n",kase++,solve());
	}
	return 0;
}
