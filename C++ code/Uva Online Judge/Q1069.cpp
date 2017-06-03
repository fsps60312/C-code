#include<cstdio>
typedef long long LL;
void getmax(LL &a,LL b){if(b>a)a=b;}
char LINE[1000000];
LL POLY[101],N,D;
bool Digit(char &c){return c>='0'&&c<='9';}
LL ReadNum(int &l)
{
	LL ans=0LL;
	while(Digit(LINE[l]))ans*=10LL,ans+=LINE[l++]-'0';
	return ans;
}
void MoveToDigit(int &l){while(!Digit(LINE[l]))l++;}
bool ReadTerm(int &l)
{
	LL pos=1LL;
	while(!Digit(LINE[l])&&LINE[l]!='n')
	{
		if(LINE[l]=='-')pos=-1LL;
		else if(LINE[l]==')')return false;
		l++;
	}
	LL coe;
	if(LINE[l]=='n')coe=pos;
	else coe=pos*ReadNum(l);
	if(LINE[l]!='n')
	{
		POLY[0]=coe;
		return true;
	}
	LL pow=1LL;
	while(LINE[l]!='+'&&LINE[l]!='-'&&LINE[l]!=')')
	{
		if(LINE[l]=='^')
		{
			MoveToDigit(l);
			pow=ReadNum(l);
			break;
		}
		l++;
	}
	while(N<pow)POLY[++N]=0LL;
	POLY[pow]=coe;
//	printf("Read %d %lldn^%lld\n",l,coe,pow);
	while(LINE[l]!='+'&&LINE[l]!='-'&&LINE[l]!=')')l++;
	return true;
}
void ReadPoly()
{
	N=-1;
	int l=0;
	LL coe=1LL;
	while(LINE[l]!='(')l++;
	while(ReadTerm(l));
	MoveToDigit(l);
	D=0LL;
	while(Digit(LINE[l]))D*=10LL,D+=LINE[l++]-'0';
}
LL pow(LL a,int p)
{
	int ans=1LL;
	while(p)
	{
		if(p&1)
		{
			ans*=a;
			ans%=D;
		}
		a*=a;
		a%=D;
		p>>=1;
	}
	return ans;
}
bool check(LL n)
{
	LL ans=0LL;
	for(int i=0;i<=N;i++)
	{
		LL &p=POLY[i];
		if(!p)continue;
		ans+=p*pow(n,i);
		ans%=D;
	}
	return ans==0LL;
}
bool solve()
{
	for(LL i=0;i<=N+1LL;i++)if(!check(i))return false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int kase=1;
	while(gets(LINE))
	{
		if(LINE[0]=='.')break;
		ReadPoly();
//		for(int i=0;i<=N;i++)printf(" %d:%lld",i,POLY[i]);printf("\n");
		printf("Case %d: %s\n",kase++,solve()?"Always an integer":"Not always an integer");
	}
	return 0;
}
