#include <bits/stdc++.h>
//#define Np2
using namespace std;

typedef long long LL;
template<LL P,LL root,int MAXN>
struct NTT
{
    static LL bigmod(LL a,LL b){
        LL res=1;
        for(LL bs=a; b; b>>=1, bs=(bs*bs)%P){
            if(b&1) res=(res*bs)%P;
        }
        return res;
    }
    static LL inv(LL a,LL b) {
        if(a==1) return 1;
        return (((LL)(a-inv(b%a,a))*b+1)/a)%b;
    }
    LL omega[MAXN+1];
    NTT() {
        omega[0]=1;
        LL r=bigmod(root,(P-1)/MAXN);
        for(int i=1;i<=MAXN;i++)
            omega[i]=(omega[i-1]*r)%P;
    }
    void tran(int n,LL a[],bool inv_ntt=false) {
        int basic=MAXN/n;
        int theta=basic;
        for(int m=n;m>=2;m>>=1) {
            int mh=m>>1;
            for(int i=0;i<mh;i++) {
                LL w=omega[i*theta%MAXN];
                for(int j=i;j<n;j+=m) {
                    int k=j+mh;
                    LL x=a[j]-a[k];
                    if(x<0) x+=P;
                    a[j]+=a[k];
                    if(a[j]>P) a[j]-=P;
                    a[k]=(w*x)%P;
                }
            }
            theta=(theta*2)%MAXN;
        }
        int i=0;
        for(int j=1;j<n-1;j++) {
            for(int k=n>>1;k>(i^=k);k>>=1);
            if(j<i) swap(a[i],a[j]);
        }
        if(inv_ntt) {
            LL ni=inv(n,P);
            reverse(a+1,a+n);
            for(i=0;i<n;i++)
                a[i]=(a[i]*ni)%P;
        }
    }
    void operator() (int n,LL a[],bool inv_ntt=false) {
        tran(n,a,inv_ntt);
    }
};

const LL P=2013265921, root=31;
const int MAXN=4194304/8;
NTT<P,root,MAXN> ntt;
void Sq(int n,LL s[])
{
	#ifdef Np2
	static LL a[MAXN];
	for(int i=0;i<n;i++)a[i]=0;
	for(int i=0;i<n;i++)if(s[i])for(int j=0;j<n;j++)if(s[j])a[i+j]+=s[i]*s[j];
	for(int i=0;i<n;i++)s[i]=a[i];
	return;
	#endif
	ntt(n,s,false);
	for(int i=0;i<n;i++)s[i]=NTT<P,root,MAXN>::bigmod(s[i],2);
	ntt(n,s,true);
}
int N;
LL *CNT=(new LL[MAXN])+50000;
unsigned Rand()
{
	static unsigned seed=20170210;
	seed*=0xdefaced,seed+=173114;
	return seed+=seed>>20;
}
void gen()
{
	freopen("in.txt","w",stdout);
	printf("10\n");
	for(int i=0;i<10;i++)
	{
		printf("100000\n");
		for(int j=0;j<100000;j++)printf("%d ",-50000+(int)(Rand()%100001));
		puts("");
	}
	exit(0);
}
int main()
{
//	for(int i=0;i<20;i++)printf("%lld\n",NTT<P,root,MAXN>::bigmod(i,2));
//	freopen("in.txt","r",stdin);
//	gen();
	int T;scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=-50000;i<=50000;i++)CNT[i]=0;
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			++CNT[v];
		}
		LL *s=new LL[MAXN];
		for(int i=0;i<MAXN;i++)s[i]=0;
		for(int i=-50000;i<=50000;i++)s[i+50000]=CNT[i];
		Sq(MAXN,s);
		s+=100000;
		LL ans=0;
		for(int i=-50000;i<=50000;i++)ans+=s[i]*CNT[i];
//		printf("ans=%lld\n",ans);
//		for(int i=-50000;i<=50000;i++)if(i!=0)ans-=CNT[0]*CNT[i]*2;//+0+,0++
//		printf("ans=%lld\n",ans);
//		ans-=CNT[0];//000(aaa)
//		printf("ans=%lld\n",ans);
//		ans-=CNT[0]*(CNT[0]-1)/2*3;//000(aab)
//		printf("ans=%lld\n",ans);
		s-=100000;
		printf("%lld\n",ans);
		delete[]s;
	}
	return 0;
}
