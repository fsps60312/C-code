#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
void Exgcd(const LL &a,const LL &b,LL &x,LL &y)
{
	if(b==0LL){assert(a==1LL);x=1LL,y=0LL;return;}
	Exgcd(b,a%b,y,x);//by+(a-a/b*b)x=1,ax+b(y-a/b*x)=1
	(y-=a/b*x)%=MOD;
}
LL RevMod(const LL &v)
{
	static LL x,y;
	Exgcd(v,MOD,x,y);
	return (x%MOD+MOD)%MOD;
}
int N;
vector<LL>S;
void Input()
{
	static char str[100001];
	scanf("%s",str);
	S.clear(),S.resize(26,0LL);
	for(int i=0;str[i];i++)
	{
		assert('a'<=str[i]&&str[i]<='z');
		S[str[i]-'a']++;
	}
	sort(S.begin(),S.end(),greater<int>());
	for(int i=25;i>=0&&S[i]==0LL;i--)S.pop_back();
}
LL Solve2()
{
	LL ans=0LL;
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)(ans+=S[i]*S[j])%=MOD;
//	printf("Solve2=%lld\n",ans);
	return ans;
}
LL Solve3()
{
	LL ans=0LL;
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)for(int k=j+1;k<N;k++)(ans+=(S[i]*S[j])%MOD*S[k])%=MOD;
//	printf("Solve3=%lld\n",ans);
	return ans*2LL%MOD;
}
LL Solve4()
{
	LL ans=0LL;
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)for(int k=j+1;k<N;k++)for(int l=k+1;l<N;l++)(ans+=(S[i]*S[j]%MOD)*(S[k]*S[l]%MOD))%=MOD;
//	printf("Solve4=%lld\n",ans);
	return ans*3LL%MOD;
}
LL LEVEL[100001],REVLEV[100001];
int main()
{
//	freopen("in.txt","r",stdin);
	LEVEL[0]=1LL;
	for(int i=1;i<=100000;i++)LEVEL[i]=(LEVEL[i-1]*i)%MOD;
	for(int i=0;i<=100000;i++)REVLEV[i]=RevMod(LEVEL[i]),assert(REVLEV[i]*LEVEL[i]%MOD==1);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		Input();
		N=S.size();
		LL ans=0LL;
		{int sum=0;for(int i=0;i<N;i++)sum+=S[i];ans=LEVEL[sum];}
		for(int i=0;i<N;i++)(ans*=REVLEV[S[i]])%=MOD;
		const LL permutations=ans;
		(ans*=ans)%=MOD;
//		printf("ans=%lld\n",ans);
		(ans-=1LL*permutations)%=MOD;
		(ans-=Solve2()*permutations)%=MOD;
		(ans-=Solve3()*permutations)%=MOD;
		(ans-=Solve4()*permutations)%=MOD;
		printf("%lld\n",(ans%MOD+MOD)%MOD);
	}
	return 0;
}
