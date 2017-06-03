#include<cstdio>
#include<vector>
#define LL long long
#define abs(x) (x>=0?x:-(x))
using namespace std;
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
int T,N,hN;
char INPUT[1000000];
struct Point
{
	int x,y;
	Point(){}
	Point(int x,int y):x(x),y(y){}
	Point Trans(int t)
	{
		switch(abs(t))
		{
			case 2:return t>0?Point(y,N-1-x):Point(N-1-y,x);
			case 3:return Point(N-1-x,y);
			case 4:return y<hN?(*this):Point(N-1-x,y);
			case 5:return y<hN?(*this):Point(x,N-1-(y-hN));
			case 6:return t>0?Point(x,(y>>1)+(y&1)*hN):Point(x,((y%hN)<<1)+(y>=hN));
			case 7:return t>0
				?Point(((x%hN)<<1)+(y&1),(y>>1<<1)+(x>=hN))
				:Point((x>>1)+(y&1)*hN,(y>>1<<1)+(x&1));
			default:termin();break;
		}
	}
	bool operator==(Point &p)const{return x==p.x&&y==p.y;}
}MAT[1<<10][1<<10];
int VIS[1<<10][1<<10];
vector<int> TRAN;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
LL lcm(LL a,LL b){return a/gcd(a,b)*b;}
LL GetCycle(Point p)
{
	Point m=MAT[p.x][p.y];
	for(LL ans=1LL;;ans++,m=MAT[m.x][m.y])
	{
		VIS[m.x][m.y]=1;
		if(m==p)return ans;
	}
}
LL solve()
{
	for(int i=0,j;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			VIS[i][j]=0;
			Point &m=MAT[i][j]=Point(i,j);
			for(int k=0;k<TRAN.size();k++)m=m.Trans(TRAN[k]);
		}
	}
	LL ans=1LL;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(VIS[i][j])continue;
			LL b=GetCycle(Point(i,j));
			ans=lcm(ans,b);
		}
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	gets(INPUT);
	sscanf(INPUT,"%d",&T);
	while(T--)
	{
		gets(INPUT),gets(INPUT);
		sscanf(INPUT,"%d",&N);
		hN=(N>>1);
		gets(INPUT);
		//id: nothing
		//rot: counterclockwise
		//sym: flip horizontal
		//bhsym: lower half flip horizontal
		//bvsym: lower half flip vertical
		//div: even->upper half, odd->lower half
		//mix: foreach (n/2)*(2): left->even row, right->odd row
		TRAN.clear();
		for(int i=0;INPUT[i];i++)
		{
			if(INPUT[i]==' ')continue;
			switch(INPUT[i])
			{
				case'i':TRAN.push_back(1);i+=2;break;
				case'r':TRAN.push_back(2);i+=3;break;
				case's':TRAN.push_back(3);i+=3;break;
				case'b':TRAN.push_back(INPUT[i+1]=='h'?4:5);i+=5;break;
				case'd':TRAN.push_back(6);i+=3;break;
				case'm':TRAN.push_back(7);i+=3;break;
				default:termin();break;
			}
			int &t=TRAN[TRAN.size()-1];
			if(INPUT[i]=='-')
			{
				t*=-1;
				i++;
			}
			else if(t==1||t==-1)TRAN.pop_back();
			i--;
		}
		printf("%lld\n",solve());
		if(T)puts("");
	}
}
