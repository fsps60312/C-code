#include<cstdio>
#define LL long long
#define abs(x) (x>=0?x:-(x))
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
int T,N,hN,VIS[1<<20],M1[1<<20],M2[1<<20],*NOW=M1,*TMP=M2,*SWAP;
char INPUT[1000000];
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
LL lcm(LL a,LL b){return a/gcd(a,b)*b;}
LL GetCycle(int p)
{
	int m=NOW[p];
	for(LL ans=1LL;;ans++,m=NOW[m])
	{
		VIS[m]=1;
		if(m==p)return ans;
	}
}
LL solve()
{
	LL ans=1LL;
	for(int i=N*N-1;i>=0;i--)
	{
		if(VIS[i])continue;
		ans=lcm(ans,GetCycle(i));
	}
	return ans;
}
void swap(){SWAP=NOW,NOW=TMP,TMP=SWAP;}
void rot(bool &inv)
{
	if(inv)for(int x=0;x<N;x++)for(int y=0;y<N;y++)TMP[y+(N-1-x)*N]=NOW[x+y*N];
	else for(int x=0;x<N;x++)for(int y=0;y<N;y++)TMP[x+y*N]=NOW[y+(N-1-x)*N];
	swap();
}
void sym(bool &inv)
{
	for(int x=0;x<N;x++)for(int y=0;y<N;y++)TMP[(N-1-x)+y*N]=NOW[x+y*N];
	swap();
}
void bhsym(bool &inv)
{
	for(int x=0;x<N;x++)for(int y=0;y<N;y++)TMP[(y<hN?x:(N-1-x))+y*N]=NOW[x+y*N];
	swap();
}
void bvsym(bool &inv)
{
	for(int x=0;x<N;x++)for(int y=0;y<N;y++)TMP[x+(y<hN?y:(N-1-(y-hN)))*N]=NOW[x+y*N];
	swap();
}
void div(bool &inv)
{
	if(inv)for(int x=0;x<N;x++)for(int y=0;y<N;y++)TMP[x+((y>>1)+(y&1)*hN)*N]=NOW[x+y*N];
	else for(int x=0;x<N;x++)for(int y=0;y<N;y++)TMP[x+y*N]=NOW[x+((y>>1)+(y&1)*hN)*N];
	swap();
}
void mix(bool &inv)
{
	if(inv)for(int x=0;x<N;x++)for(int y=0;y<N;y++)TMP[x+y*N]=NOW[((x>>1)+(y&1)*hN)+((y>>1<<1)+(x&1))*N];
	else for(int x=0;x<N;x++)for(int y=0;y<N;y++)TMP[((x>>1)+(y&1)*hN)+((y>>1<<1)+(x&1))*N]=NOW[x+y*N];
	swap();
}
int main()
{
//	freopen("in.txt","r",stdin);
	gets(INPUT);
	sscanf(INPUT,"%d",&T);
	while(T--)
	{
		gets(INPUT),gets(INPUT);
		sscanf(INPUT,"%d",&N);
		hN=(N>>1);
		for(int i=N*N-1;i>=0;i--)VIS[i]=0,NOW[i]=i;
		gets(INPUT);
		//id: nothing
		//rot: counterclockwise
		//sym: flip horizontal
		//bhsym: lower half flip horizontal
		//bvsym: lower half flip vertical
		//div: even->upper half, odd->lower half
		//mix: foreach (n/2)*(2): left->even row, right->odd row
		for(int i=0,t;INPUT[i];i++)
		{
			if(INPUT[i]==' ')continue;
			switch(INPUT[i])
			{
				case'i':t=1;i+=2;break;
				case'r':t=2;i+=3;break;
				case's':t=3;i+=3;break;
				case'b':t=(INPUT[i+1]=='h'?4:5);i+=5;break;
				case'd':t=6;i+=3;break;
				case'm':t=7;i+=3;break;
				default:termin();break;
			}
			bool inv=false;
			if(INPUT[i]=='-')inv=true,i++;
			switch(t)
			{
				case 1:break;
				case 2:rot(inv);break;
				case 3:sym(inv);break;
				case 4:bhsym(inv);break;
				case 5:bvsym(inv);break;
				case 6:div(inv);break;
				case 7:mix(inv);break;
				default:termin();break;
			}
			i--;
		}
		printf("%lld\n",solve());
		if(T)puts("");
	}
}
