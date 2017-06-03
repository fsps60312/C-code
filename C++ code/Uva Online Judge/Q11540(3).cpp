#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
const LL MOD=1000000007;
const unsigned long long HASH1=10058333,HASH2=10058371;
char INPUT[1000000];
int T;
LL C;
bool Digit(char &c){return c>='0'&&c<='9';}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
void exgcd(LL a,LL b,LL &g,LL &x,LL &y)
{
	if(b)
	{
		exgcd(b,a%b,g,y,x);
		//(a%b)x+by==g
		//ax-(a/b)*bx+by==g
		//ax+b(y-a/b*x)==g
		y-=a/b*x;
	}
	else
	{
		g=a;
		x=1LL,y=0LL;
	}
}
LL inv(LL a)
{
	LL x,y,g;
	exgcd(a,MOD,g,x,y);
	if(g!=1LL){printf("g!=1LL\n");termin();}
	if(a*x+MOD*y!=1LL){printf("a x + MOD y != 1 %d*%d+%d*%d!=1\n",a,x,MOD,y);termin();}
//	a=(a%MOD+MOD)%MOD;
	return x=(x%MOD+MOD)%MOD;
//	return x;
//	return a*x%MOD;
}
struct Node
{
	vector<Node*> ch;
	unsigned long long hash;
	LL cnt;
	unsigned long long rearngch()
	{
		unsigned long long ha=HASH2,mx=0,tmp=0;
		int sz=ch.size(),ans=-1;
		for(int i=0;i<sz;i++,ha=HASH2,tmp=0)
		{
			for(int j=0;j<sz;j++,ha*=HASH2)
			{
				tmp+=(*ch[(i+j)%sz]).hash*ha;
			}
			if(tmp>=mx)mx=tmp,ans=i;
		}
		if(ans==-1){printf("ans==%d\n",ans);termin();}
		vector<Node*> tch;
		for(int i=0;i<sz;i++)tch.push_back(ch[(ans+i)%sz]);
		ch=tch;
		return mx;
	}
	LL GetEqual(LL dis)
	{
		LL sz=ch.size();
		LL n=gcd(sz,dis);
		LL u=sz/n;
//		printf("(%lld,%lld)",n,u);
		LL ans=1LL;
		for(LL i=0;i<n;i++)
		{
			for(LL j=1;j<u;j++)if((*ch[j*n+i]).hash!=(*ch[i]).hash)return 0LL;
			ans*=(*ch[i]).cnt;
			ans%=MOD;
		}
		return ans;
	}
	void init(int l,int r)
	{
//		printf("l=%d,r=%d\n",l,r);
		hash=HASH1;
		ch.clear();
		l++,r--;
		if(l==r+1)
		{
			cnt=C;
			return;
		}
		else if(l>=r){printf("l>=r:%d>=%d\n",l,r);termin();}
		int brack=1;
		for(int i=l+1;i<=r;i++)
		{
			if(INPUT[i]==']')brack--;
			else if(INPUT[i]=='[')brack++;
			if(brack<0){printf("brack<0:%d<0\n",brack);termin();}
			if(brack==0)
			{
				Node *n=new Node();
				(*n).init(l,i);
				ch.push_back(n);
				l=i+1;
				if(INPUT[l]!=',')
				{
					if(l!=r+1){printf("l!=r+1:%d!=%d\n",l,r+1);termin();}
					break;
				}
				else l++,i=l-1;
			}
		}
		if(brack!=0){printf("brack==%d\n",brack);termin();}
		if(!ch.size()){printf("ch.size()==%d\n",ch.size());termin();}
		hash+=rearngch();
		//count cnt not finished......
//		showhash();
		cnt=0LL;
		LL sz=ch.size();
		LL iv=0LL;
		for(LL i=1,v;i<=sz;i++)
		{
			v=GetEqual(i);
			if(!v)continue;
			iv++;
			cnt+=v;
			cnt%=MOD;
//			printf(" %lld",GetEqual(i));
		}
		if(!cnt){printf("!cnt\n");termin();}
//		puts("");
		cnt*=C;
		cnt%=MOD;
		cnt*=inv(iv);
		cnt%=MOD;
	}
	void showhash()
	{
		printf(" %llu:",hash);
		for(int i=0;i<ch.size();i++)printf(" %llu",(*ch[i]).hash);
		puts("");
	}
}ROOT;
int main()
{
//	freopen("in.txt","r",stdin);
	gets(INPUT);
	sscanf(INPUT,"%d",&T);
	int kase=1;
	while(T--)
	{
		gets(INPUT);
		C=0;
		int l=-1,r=-1;
		for(int i=0;INPUT[i];i++)
		{
			if(Digit(INPUT[i]))C=C*10+(INPUT[i]-'0');
			if(INPUT[i]==']')r=i;
			if(l==-1&&INPUT[i]=='[')l=i;
		}
		if(!C){printf("!C\n");termin();}
//		printf("C==%lld\n",C);
//		printf("kase %d\n",kase);
		ROOT.init(l,r);
		printf("Case #%d: %lld\n",kase++,ROOT.cnt);
	}
	return 0;
}
