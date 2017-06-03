#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int N,I;
bool getmax(int &a,int b){if(b>a){a=b;return true;}return false;}
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
struct BetInfo
{
	int dis,differ,p1,p2;
	BetInfo(){}
	BetInfo(int dis,int dif,int p1,int p2):dis(dis),differ(dif),p1(p1),p2(p2){}
	bool operator<(BetInfo a)const{return dis<a.dis;}
}INFO[500000-500];
int sq(int a){return a*a;}
struct Planet
{
	int x,y,z,eco,idx,unstable;
	void canf(int i){idx=i,unstable=-1;scanf("%d%d%d%d",&x,&y,&z,&eco);}
	BetInfo operator-(Planet a)const{return BetInfo(sq(x-a.x)+sq(y-a.y)+sq(z-a.z),eco^a.eco,idx,a.idx);}
}PLANET[1000];
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)PLANET[i].canf(i);
		I=0;
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)INFO[I++]=PLANET[i]-PLANET[j];
		int ans=0,ansr=0;
		if(I)
		{
			if(I>499500)termin();
			sort(INFO,INFO+I);
			for(int i=0,r=INFO[0].dis,uns=0;;)
			{
				while(i<I&&INFO[i].dis==r)
				{
					BetInfo &info=INFO[i++];
					Planet &p1=PLANET[info.p1],&p2=PLANET[info.p2];
					if(info.differ)
					{
						if(!p1.unstable++)uns++;
						if(!p2.unstable++)uns++;
						
					}
					else
					{
						if(!--p1.unstable)uns--;
						if(!--p2.unstable)uns--;
					}
				}
				//printf("r=%d,i=%d,uns=%d\n",r,i,uns);
				if(getmax(ans,uns))ansr=r;
				if(i==I)break;
				r=INFO[i].dis;
			}
		}
		if(ansr<0)termin();
		printf("%d\n%.6f\n",ans,sqrt((double)ansr));
	}
	return 0;
}
