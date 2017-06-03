#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
int n;
#define N 125
int gc[N][N],sum1[N][N],sum2[N][N];
LL dp[N][N];



LL fff(int x,int y)//x dots each column, y dots each row
{
	//pick: area = dots inside + dots on side / 2 - 1
	//dots inside = dots on side / 2 - area - 1
	//all=sidedots/2-areas-num
	//(Wrong)=(x+y-2)(gcd(0~x,y)+gcd(0~y-1,x))/4--C(x+y-1,2)
	//sidedots
	//=gcd(0~x-1,y)*(y-1)+gcd(0~y-1,x)*(x-1)
	//+gcd(x,y)*(x-1)+gcd(0~x-1,y)
	//+gcd(x,y)*(y-1)+gcd(0~y-1,x)
	//=gcd(0~x-1,y)*y+gcd(x,y)*y-gcd(x,y)
	//+gcd(0~y-1,x)*x+gcd(y,x)*x-gcd(y,x)
	//=gcd(0~x-1,y)*y+gcd(0~y-1,x)*x-2*gcd(x-1,y-1)_______________________________
	//(third side)+y(y-1)/2+x(x-1)/2+gcd(1~y-1,1)+gcd(1~y-1,2)+...+gcd(1~y-1,x-1)
	//=gcd(0~y-1,0)+gcd(0~x-1,0)+gcd(1~y-1,1~x-1)
	//=gcd(0~x-1,0~y-1)-gcd(0,0)__________________________________________________
	//areas
	//(y-1)(0~x-1)
	if (x>y) swap(x,y);//make x<y
	if (dp[x][y]!=-1) return dp[x][y];
	
	LL s=x*y+2,ss=x*y*2+2,tmp,sss,nowt;
	LL re1=0,re2=0,re3=0;
	//gcd(1,x)+gcd(2,x)+...+gcd(y-1,x)¡÷:dots on each side to down
	// 
	tmp=(sum2[y-1][x]-sum2[0][x])*2+(y-1)*y;
	re1+=(s*(y-1)-tmp)/2;
	//re1==(y-1)((x-1)*y+2)/2-gcd(1~y-1,x)==(x-1)(y-1)y/2+(y-1)-gcd(1~y-1,x)
	//gcd(1,y)+gcd(2,y)+...+gcd(x-1,y)¡õ :dots on each side to right
	tmp=(sum2[x-1][y]-sum2[0][y])*2+(x-1)*x;
	re1+=(s*(x-1)-tmp)/2;
	//re1 added: (x-1)(y-1)x/2+(x-1)-gcd(1~x-1,y)
	//re1==(x-1)(y-1)(x+y)/2+(x+y-2)-gcd(1~y-1,x)-gcd(1~x-1,y)

	LL t=(x-1)*(y-1);
	tmp=(sum2[x-1][y]-sum2[0][y])*(y-1)
		+(sum2[y-1][x]-sum2[0][x])*(x-1)
		+sum1[x-1][y-1]-sum1[0][y-1]-sum1[x-1][0];
	//tmp==gcd(1~x-1,y)*(y-1)+gcd(1~y-1,x)*(x-1)+gcd(0~x-1,0~y-1)-gcd(0,0~y-1)-gcd(0~x-1,0)
	//==gcd(1~x-1,y)*(y-1)+gcd(1~y-1,x)*(x-1)+gcd(1~x-1,1~y-1)
	sss=(x-1)*(y-1)*x*y+x*(x-1)/2*y*(y-1)/2;
	re2+=(ss*t-sss-tmp)/2;
	//re2*2==(2xy+2)(x-1)(y-1)-xy(x-1)(y-1)*5/4-tmp
	//==(x-1)(y-1)(3/4 xy+2)-tmp

	t=0;ss=0,nowt=0;tmp=0;sss=0;
	for (int j=1;j<=y;j++)
	{
		int be=(y*x-j*x)/y+1;
		nowt=x-be+1;
		t+=nowt;
		tmp+=gc[x][y]*nowt;
		tmp+=sum2[x][y-j];
		if (be>0) tmp-=sum2[be-1][y-j];
		tmp+=sum2[x-be][j];
		sss+=j*x*nowt+y*(x+be)*(x-be+1)/2;
	}
	re3+=(-x*y+2)*t;
	re3-=tmp;
	re3+=sss;
	re3/=2;
	dp[x][y]=re1*2+re2*4+re3*4;
	return dp[x][y];
}
int gcd(int a,int b)
{   if (b==0) return a;
	return gcd(b,a%b);
}
LL C4(LL a)//C(a,4)
{   if (a<4) return 0;

	return a*(a-1)*(a-2)/6*(a-3)/4;
}
LL C3(LL a)//C(a,3)
{   if (a<3) return 0;
	return a*(a-1)*(a-2)/6;
}

void doit()
{
	LL ans1=0,ans2=0,x,tmp,q;
	LL tot=(n+1)*(n+1);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			tmp=gc[i][j];
			tmp--;
			q=(n-i+1)*(n-j+1);//ways i*j rect can place
			ans1+=q*tmp;//one on line(i,j)
			ans2+=q*tmp*(tmp-1)/2;//two on line(i,j)
		}
	}
	//ans1: cases three dot place on the same line
	//ans2: cases four dot place on the same line
	LL ans=C4(tot)//four on all
		-C4(n+1)*(n+1)*2//four on the same column||row
		-C3(n+1)*n*(n+1)*(n+1)*2;//three on the same column||row, the other isn't
	ans-=(ans1*(tot-3)-3*ans2)*2;
	//*2: left-tilt & right-tilt
	//ans: cases no three dot on the same line
	for (int i=2;i<=n;i++)
	{
		for (int j=2;j<=n;j++)
		{
			//guess: fff(i,j) is concave quads in i*j area
			ans+=fff(i,j)*2*(n+1-i)*(n+1-j);
		}
	}
	printf("%lld\n",ans);
}

int main()
{
	for (int i=0;i<N;i++) for (int j=0;j<N;j++) dp[i][j]=-1;
	gc[0][0]=0;
	for (int i=0;i<N;i++)
	{
		for (int j=i;j<N;j++)
		{
			if (i||j)
			{
				gc[j][i]=gc[i][j]=gcd(i,j);
			}
		}
	}
	//gc[i][j] is gcd(i,j)
	for (int j=0;j<N;j++)
	{
		sum2[0][j]=gc[0][j];//0
		for (int i=1;i<N;i++)
		{
			//one dot on (0,0), another on (0~i,j), the num of sites that make third dot form a line
			sum2[i][j]=sum2[i-1][j]+gc[i][j];//gcd(0,j)+gcd(1,j)+...+gcd(i,j)
		}
	}
	for (int i=0;i<N;i++)
	{
		sum1[i][0]=sum2[i][0];
	}
	for (int j=1;j<N;j++)
	{
		for (int i=0;i<N;i++)
		{
			//sum1[i][j]=sum2[i][0]+sum2[i][1]+...+sum2[i][j]
			//sum1[i][j]==gcd(0,0)+gcd(1,0)+...+gcd(i,0)+gcd(0,1)+gcd(1,1)...+gcd(i,j)
			sum1[i][j]=sum1[i][j-1]+sum2[i][j];
		}
	}
	for(int i=1;i<5;i++)
	{
		for(int j=1;j<5;j++)
		{
			printf("%lld ",fff(i,j));
		}
		printf("\n");
	}
	while (scanf("%d",&n),n) {printf("%d ",n),doit();}
	return 0;
}
