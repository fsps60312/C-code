#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
int R,C,H[100][100],V[100][100];
bool VIS[100][100][4];
struct Point
{
	int r,c;
};
Point SP,EP;
struct Trip
{
	int r,c,d,len;//up,right,down,left
	bool operator<(Trip a)const{return len>a.len;}
};
void getmin(int &a,int b){if(b<a||a==-1)a=b;}
int mod(int a){return (a%4+4)%4;}
int getHV(int r,int c,int d)
{
	int ans;
	switch(d)
	{
		case 0:
		case 3:break;
		case 1:c--;break;
		default:r--;break;
	}
	if(r<0||c<0||r==R||c==C)return 0;
	switch(d)
	{
		case 0:
		case 2:return V[r][c];
		default:return H[r][c];
	}
}
int solve()
{
	priority_queue<Trip> pq;
	for(int i=0;i<4;i++)if(getHV(SP.r,SP.c,mod(i+2)))pq.push((Trip){SP.r,SP.c,i,getHV(SP.r,SP.c,mod(i+2))});
	int ans=-1;
	while(!pq.empty())
	{
		Trip t=pq.top();pq.pop();
		if(VIS[t.r][t.c][t.d])continue;
		VIS[t.r][t.c][t.d]=true;
		if(t.r==EP.r&&t.c==EP.c)getmin(ans,t.len+getHV(t.r,t.c,t.d+2));
		printf("(%d,%d)%d:%d\n",t.r,t.c,t.d,t.len);
		if(!getHV(t.r,t.c,mod(t.d+2)))continue;
		switch(t.d)
		{
			case 0:t.r--;break;
			case 1:t.c++;break;
			case 2:t.r++;break;
			default:t.c--;break;
		}
		if(t.r<0||t.c<0||t.r==R||t.c==C)continue;
		int d=mod(t.d-1);
		pq.push((Trip){t.r,t.c,d,t.len+getHV(t.r,t.c,t.d)+getHV(t.r,t.c,mod(d+2))*2});
		d++,d%=4;
		pq.push((Trip){t.r,t.c,d,t.len+getHV(t.r,t.c,mod(d+2))});
		d++,d%=4;
		pq.push((Trip){t.r,t.c,d,t.len+getHV(t.r,t.c,t.d)+getHV(t.r,t.c,mod(d+2))*2});
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d%d",&R,&C)==2&&(R||C))
	{
		scanf("%d%d%d%d",&SP.r,&SP.c,&EP.r,&EP.c);
		SP.r--,SP.c--,EP.r--,EP.c--;
		for(int r=0;;r++)
		{
			for(int c=0;c<C;c++)
			{
				for(int k=0;k<4;k++)VIS[r][c][k]=false;
			}
			for(int c=0;c<C-1;c++)
			{
				scanf("%d",&H[r][c]);
			}
			if(r==R-1)break;
			for(int c=0;c<C;c++)
			{
				scanf("%d",&V[r][c]);
			}
		}
		int ans=solve();
		printf("Case %d: ",kase++);
		if(ans==-1)printf("Impossible\n");
		else printf("%d\n",ans);
	}
	return 0;
}
