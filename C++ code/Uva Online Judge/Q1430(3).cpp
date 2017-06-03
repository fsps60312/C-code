#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
const int MOD=10007;
int N,K;
LL GetBinary()
{
	LL ans=0LL;
	char c=getchar();
	while(c!='0'&&c!='1')c=getchar();
	for(int i=0;i<N;i++)assert(c=='0'||c=='1'),(ans<<=1)|=(c-'0'),c=getchar();
	return ans;
}
int BitCnt(LL a)
{
	a=((a&0xaaaaaaaaaaaaaaaa)>>1)+(a&0x5555555555555555);
	a=((a&0xcccccccccccccccc)>>2)+(a&0x3333333333333333);
	a=((a&0xf0f0f0f0f0f0f0f0)>>4)+(a&0x0f0f0f0f0f0f0f0f);
	a=((a&0xff00ff00ff00ff00)>>8)+(a&0x00ff00ff00ff00ff);
	a=((a&0xffff0000ffff0000)>>16)+(a&0x0000ffff0000ffff);
	a=((a&0xffffffff00000000)>>32)+(a&0x00000000ffffffff);
	return (int)a;
}
struct Big
{
	vector<LL>s;
	Big(){}
	Big(const LL &v){s.clear(),s.push_back(v);Carry();}
	void RemoveZero(){for(int i=s.size()-1;i>0&&s[i]==0LL;i--)s.pop_back();}
	void Carry()
	{
		for(int i=0;i<s.size();i++)if(s[i]>=10LL)
		{
			if(i+1==s.size())s.push_back(0LL);
			s[i+1]+=s[i]/10LL,s[i]%=10LL;
		}
	}
	Big &operator*=(const LL &a)
	{
		for(int i=0;i<s.size();i++)s[i]*=a;
		Carry();
		return *this;
	}
	void operator+=(const Big &a)
	{
		while(s.size()<a.s.size())s.push_back(0LL);
		for(int i=0;i<a.s.size();i++)s[i]+=a.s[i];
		Carry();
	}
	void operator-=(const Big &a)
	{
		for(int i=0;i<a.s.size();i++)s[i]-=a.s[i];
		for(int i=0;i<s.size();i++)if(s[i]<0LL)s[i]+=10LL,s[i+1]--,assert(s[i]>=0LL);
		RemoveZero();
	}
	Big operator/(const LL &a)
	{
		Big ans;
		ans.s.resize(s.size());
		LL tmp=0LL;
		for(int i=s.size()-1;i>=0;i--)
		{
			(tmp*=10LL)+=s[i];
			ans.s[i]=tmp/a,tmp%=a;
		}
		assert(tmp==0LL);
		ans.RemoveZero();
		return ans;
	}
	void operator/=(const LL &a){(*this)=(*this)/a;}
	void Print(){for(int i=s.size()-1;i>=0;i--)putchar('0'+s[i]);}
};
Big DP[9881][41];
Big EDGE[9881][41][41];
LL C[41][41];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=1;i<=40;i++)
	{
		C[i][0]=C[i][i]=1LL;
		for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	while(scanf("%d%d",&N,&K)==2&&(N||K))
	{
		for(int i=0;i<=K;i++)for(int j=0;j<=N;j++)DP[i][j]=0LL;
		for(int i=0;i<=K;i++)for(int j=0;j<=N;j++)for(int k=0;k<=N;k++)EDGE[i][j][k]=0LL;
		DP[0][0]=1LL;
		for(int i=1;i<=K;i++)for(int j=0;j<=N;j++)
		{
			if(j-3>=0)
			{
				((EDGE[i][j-3][j]=DP[i-1][j-3])*=C[N-(j-3)][3])-=EDGE[i-1][j][j-3];
				DP[i][j]+=EDGE[i][j-3][j];
			}
			if(j-1>=1&&N-(j-1)>=2)
			{
				(((EDGE[i][j-1][j]=DP[i-1][j-1])*=C[j-1][1])*=C[N-(j-1)][2])-=EDGE[i-1][j][j-1];
				DP[i][j]+=EDGE[i][j-1][j];
			}
			if(j+1>=2&&N-(j+1)>=1)
			{
				(((EDGE[i][j+1][j]=DP[i-1][j+1])*=C[j+1][2])*=C[N-(j+1)][1])-=EDGE[i-1][j][j+1];
				DP[i][j]+=EDGE[i][j+1][j];
			}
			if(j+3<=N)
			{
//				printf("DP[i][j]: ");DP[i][j].Print();puts("");
//				printf("DP[i-1][j+1]: ");DP[i-1][j+3].Print();puts("");
//				printf("C[j+3][3]: %lld\n",C[j+3][3]);
//				printf("EDGE[i-1][j][j+3]: ");EDGE[i-1][j][j+3].Print();puts("");
				((EDGE[i][j+3][j]=DP[i-1][j+3])*=C[j+3][3])-=EDGE[i-1][j][j+3];
//				DP[i][j].Print();printf("+=");EDGE[i][j+3][j].Print();puts("");
				DP[i][j]+=EDGE[i][j+3][j];
			}
			DP[i][j]/=(LL)i;
		}
//		puts("pass");
//		continue;
		int cnt=BitCnt(GetBinary()^GetBinary());
		Big ans=DP[K][cnt];
		ans/=C[N][cnt];
//		for(int i=K,d=1;i>=0;i-=2,d*=-1)ans+=DP[i][cnt]*d,printf("%c%d\n",d==1?'+':'-',DP[i][cnt]);
		static int kase=1;
		printf("Case #%d: ",kase++);
		ans.Print();puts("");
	}
	return 0;
}
