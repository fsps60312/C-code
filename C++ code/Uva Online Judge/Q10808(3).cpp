#include<cstdio>
#include<vector>
typedef long long LL;
using namespace std;
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
LL T,N,M;
bool VIS[30];
vector<LL> TO[30];
LL abs(LL a){return a>=0?a:-a;}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
struct Fra
{
	LL up,down;
	Fra():up(0LL),down(0LL){}
	Fra(LL v):up(v),down(1LL){}
	Fra(LL u,LL d):up(u),down(d){}
	void carry()
	{
		if(!down&&!up){printf("both zero in fraction\n");termin();}
		if(!down){up=1LL;return;}
		if(!up){down=1LL;return;}
		LL g=gcd(abs(up),abs(down));
		up/=g;
		down/=g;
		if(down<0LL)//{printf("something impossible happened: %lld %lld\n",up,down);termin();}
		{
			down=-down;
			up=-up;
		}
	}
	char* c_str(){char *ans=new char[100];sprintf(ans,"%lld/%lld",up,down);return ans;}
	bool ContainZero(){return !up||!down;}
	bool operator==(Fra f)const{return up==f.up&&down==f.down;}
	bool operator!=(Fra f)const{return !((*this)==f);}
	Fra operator*(Fra f)const{Fra ans=Fra(up*f.up,down*f.down);ans.carry();return ans;}
	Fra operator/(Fra f)const{Fra ans=Fra(up*f.down,down*f.up);ans.carry();return ans;}
	Fra operator+(Fra f)const{Fra ans=Fra(up*f.down+down*f.up,down*f.down);ans.carry();return ans;}
	Fra operator-(Fra f)const{Fra ans=Fra(up*f.down-down*f.up,down*f.down);ans.carry();return ans;}
	Fra operator+=(Fra f){return (*this)=(*this)+f;}
	Fra operator-=(Fra f){return (*this)=(*this)-f;}
	Fra operator/=(Fra f){return (*this)=(*this)/f;}
}RES[30][30],MAT[30][31];
Fra AddRes(Fra a,Fra b){return Fra(1LL)/((Fra(1LL)/a)+(Fra(1LL)/b));}
void initMAT()
{
	for(LL i=0LL;i<N;i++)
	{
		for(LL j=0;j<=N;j++)MAT[i][j]=Fra(0LL);
		for(LL _=0LL;_<TO[i].size();_++)
		{
			LL &j=TO[i][_];
			MAT[i][i]+=Fra(1LL)/RES[i][j];
			MAT[i][j]-=Fra(1LL)/RES[i][j];
		}
	}
}
void Exchange(LL r1,LL r2)
{
	Fra tmp;
	for(LL i=0LL;i<=N;i++)tmp=MAT[r1][i],MAT[r1][i]=MAT[r2][i],MAT[r2][i]=tmp;
}
void Kill(LL r1,LL r2)
{
	if(MAT[r2][r1]==Fra(0LL))return;
	else if(MAT[r2][r1].ContainZero()){printf("encounter infinite when killing: %lld %lld\n",r1,r2);termin();}
	Fra ratio=MAT[r2][r1]/MAT[r1][r1];
	for(LL i=r1;i<=N;i++)MAT[r2][i]-=MAT[r1][i]*ratio;
}
void dfsVIS(LL u)
{
	if(VIS[u])return;
	VIS[u]=true;
	for(LL _=0;_<TO[u].size();_++)
	{
		LL &j=TO[u][_];
		dfsVIS(j);
	}
}
void showGus(char *headline)
{
	puts(headline);
	for(LL i=0LL;i<N;i++)
	{
		for(LL j=0LL;j<=N;j++)printf("%8s",MAT[i][j].c_str());
		puts("");
	}
}
void showRES()
{
	puts("show RES:");
	for(LL i=0LL;i<N;i++)
	{
		for(LL j=0LL;j<N;j++)printf("%8s",RES[i][j].c_str());
		puts("");
	}
}
void solve()
{
	for(LL i=0LL;i<N;i++)
	{
		if(!VIS[i])continue;
		LL c;
		for(c=i;c<N;c++)if(!MAT[i][c].ContainZero())break;
		if(c==N){showGus("error");printf("can't find >0 row at column %lld\n",i);termin();}
		else if(c!=i)Exchange(i,c);
		for(LL j=0LL;j<N;j++)
		{
			if(!VIS[j]||j==i)continue;
			Kill(i,j);
		}
	}
	for(LL i=0LL;i<N;i++)
	{
		if(!VIS[i])continue;
		for(LL j=0LL;j<N;j++)if(VIS[j]&&j!=i&&MAT[i][j]!=Fra(0LL)){printf("find not killed\n");termin();}
		MAT[i][N]/=MAT[i][i];
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lld",&T);
	LL kase=1LL;
	while(T--)
	{
		scanf("%lld%lld",&N,&M);
		for(LL i=0LL;i<N;i++)TO[i].clear();
		for(LL i=0LL;i<N;i++)for(LL j=0LL;j<N;j++)RES[i][j]=i==j?Fra(0LL,1LL):Fra(1LL,0LL);
		for(LL i=0LL,a,b,r;i<M;i++)
		{
			scanf("%lld%lld%lld",&a,&b,&r);
			if(RES[a][b]==Fra(1LL,0LL))
			{
				TO[a].push_back(b);
				TO[b].push_back(a);
			}
			RES[a][b]=AddRes(RES[a][b],Fra(r));
			RES[b][a]=AddRes(RES[b][a],Fra(r));
		}
		LL Q,A,B;scanf("%lld",&Q);
		printf("Case #%lld:\n",kase++);
		while(Q--)
		{
			scanf("%lld%lld",&A,&B);
			initMAT();
//showGus("before init");
			for(LL i=0LL;i<N;i++)
			{
				VIS[i]=false;
				MAT[i][A]=Fra(0LL);
				MAT[i][N]-=MAT[i][B];
				MAT[i][B]=Fra(0LL);
			}
//showGus("after init");
			dfsVIS(A);
			dfsVIS(B);
			VIS[A]=VIS[B]=false;
			solve();
			MAT[A][N]=Fra(0LL);
			MAT[B][N]=Fra(1LL);
			Fra ans_a=Fra(0LL);
			for(LL _=0LL;_<TO[A].size();_++)
			{
				LL &i=TO[A][_];
				Fra current=MAT[i][N]/RES[A][i];
				ans_a+=current;
//printf(" %s,%s,%s",current.c_str(),MAT[i][N].c_str(),MAT[A][N].c_str());
			}
//puts("");
			Fra ans_b=Fra(0LL);
			for(LL _=0LL;_<TO[B].size();_++)
			{
				LL &i=TO[B][_];
				Fra current=(Fra(1LL)-MAT[i][N])/RES[B][i];
				ans_b+=current;
//printf(" %s,%s,%s",current.c_str(),MAT[B][N].c_str(),MAT[i][N].c_str());
			}
//puts("");
			if(ans_a!=ans_b){printf("%s != %s\n",ans_a.c_str(),ans_b.c_str());termin();}
			ans_a=Fra(1LL)/ans_a;
			printf("Resistance between %lld and %lld is %s\n",A,B,ans_a.c_str());
		}
		puts("");
	}
}
