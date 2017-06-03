#include<cstdio>
#define abs(x) (x>=0?x:-(x))
int T,C,N,DP[100001],ABS[100001],DIS[100001],W[100001];
void getmin(int &a,int b){if(b<a)a=b;}
struct Point
{
	int x,y,w;
	Point(){}
	Point(int x,int y,int w):x(x),y(y),w(w){}
	int operator-(Point a){return abs(x-a.x)+abs(y-a.y);}
}P1,P2;
struct Mq
{
	Point v[100000];
	int l,r;
	void clear(){l=0,r=-1;}
	int SZ(){return r-l+1;}
	Point L(){return v[l];}
	Point R(){return v[r];}
	void push(Point p){v[++r]=p;}
}MQ;
int main()
{
	DIS[0]=W[0]=0;
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&C,&N);
		DP[0]=0;
		P1=Point(0,0,0);
		MQ.clear();
		for(int i=1;i<=N;i++,P1=P2)
		{
			scanf("%d%d%d",&P2.x,&P2.y,&P2.w);
			W[i]=W[i-1]+P2.w;
			DIS[i]=DIS[i-1]+(P2-P1);
			ABS[i]=abs(P2.x)+abs(P2.y);
		}
		//DP[i]=min(DP[j-1]+Dis(j)+Dis(j,i)+Dis(i)),W[i]-W[j-1]<=C
		//   =DP[j-1]+Dis(j)-DIS[j]+DIS[i]+Dis[i]
		for(int i=1;i<=N;i++)
		{
			while(MQ.SZ()&&W[i]-MQ.L().y>C)MQ.l++;
			Point p=Point(DP[i-1]+ABS[i]-DIS[i],W[i],0);
			while(MQ.SZ()&&MQ.L().x>=p.x)MQ.r--;
			MQ.push(p);
			DP[i]=MQ.L().x+DIS[i]+ABS[i];
		}
		printf("%d\n",DP[N]);
		if(T)printf("\n");
	}
	return 0;
}
