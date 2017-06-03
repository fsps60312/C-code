#include<cstdio>
#include<stack>
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
using namespace std;
void getmax(int &a,int b){if(b>a)a=b;}
void getmin(int &a,int b){if(b<a)a=b;}
int T,N,M,LIMIT;
char MAP[1000][1001];
int H[2][1000],CNT[1999];
struct Hx
{
	int h,x;
	Hx(){}
	Hx(int h,int x):h(h),x(x){}
};
void solve()
{
	LIMIT=N+M-2;
	for(int n=0;n<=LIMIT;n++)CNT[n]=0;
	int *ph=H[0],*nh=H[1];
	for(int i=0;i<M;i++)ph[i]=-1;
	for(int y=0;y<N;y++)
	{
		for(int x=0;x<M;x++)
		{
			if(MAP[y][x]=='#')nh[x]=-1;
			else nh[x]=ph[x]+1;
		}
		stack<Hx> s;
		for(int x=0;x<M;x++)
		{
			int &h=nh[x];
			if(h<0){s=stack<Hx>();continue;}
			if(!s.empty()&&s.top().h>=h)
			{
				Hx st=s.top();s.pop();getmin(st.h,h);
				while(!s.empty()&&(s.top().h>=h||st.h+st.x<=s.top().h+s.top().x))
				{
					st=s.top();s.pop();getmin(st.h,h);
				}
				s.push(st);
			}
			else if(s.empty())for(int i=0;i<=h;i++)s.push(Hx(i,x));
			else if(h>x-s.top().x+s.top().h)s.push(Hx(h,x));
			int v=x-s.top().x+s.top().h;
			CNT[v]++;
		}
		int *tmp=ph;ph=nh,nh=tmp;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int y=0;y<N;y++)scanf("%s",MAP[y]);
		solve();
		for(int i=0;i<=LIMIT;i++)
		{
			if(!CNT[i])continue;
			printf("%d x %d\n",CNT[i],4+i*2);
		}
	}
	return 0;
}
