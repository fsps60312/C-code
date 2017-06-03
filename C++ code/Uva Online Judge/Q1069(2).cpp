#include<cstdio>
typedef long long LL;
void getmax(LL &a,LL b){if(b>a)a=b;}
char LINE[1000000];
LL POLY[101],N,D;
bool Digit(char &c){return c>='0'&&c<='9';}
void ReadPoly()
{
	N=-1LL,D=0LL;
	LL coe=0LL,pos=1LL;
	int pow=0,key=-1;
	for(int i=0;LINE[i];i++)
	{
		if(Digit(LINE[i]))
		{
			if(key<=0)coe*=10LL,coe+=LINE[i]-'0';
			else if(key==1)pow*=10,pow+=LINE[i]-'0';
			else D*=10LL,D+=LINE[i]-'0';
		}
		else switch(LINE[i])
		{
			case'n':pow=1;break;
			case'^':pow=0,key=1;break;
			case'-':
			case'+':if(key<0){pos=-1LL;break;}
			case')':
				while(N<pow)POLY[++N]=0LL;
				if(!coe)coe=1LL;
				POLY[pow]=coe*pos;
				key=pow=(LINE[i]==')'?2:0);
				coe=0LL,pos=(LINE[i]=='-'?-1LL:1LL);
				break;
		}
	}
}
LL pow(LL a,int p)
{
	LL ans=1LL;
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
	for(LL i=N+1LL;i>=0;i--)if(!check(i))return false;
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
