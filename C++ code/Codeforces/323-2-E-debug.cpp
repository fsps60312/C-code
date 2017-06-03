#include <bits/stdc++.h>
using namespace std;
int S[200000],N,CNT[200000],GG[200000];
bool U[200000];
int Inc(int v){return (v+1==N)?0:(v+1);}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int main()
{
    scanf("%d",&N);
    for(int i=0;i<N;++i)scanf("%d",&S[i]);
    for(int i=0;i<N;++i)GG[i]=gcd(i+1,N);
    long long res=0LL;
    for(int f=1;f<N;++f)
	{
        if(N%f!=0)continue;
        for(int i=0;i<N;++i)U[i]=false,CNT[i]=0;
        for(int i=0;i<f;++i)
		{
            int mx=-1;
            for(int j=i;j<N;j+=f)mx=max(mx,S[j]);
            for(int j=i;j<N;j+=f)if(S[j]==mx)U[j]=true;
        }
        bool any=false;
        for(int l=0;l<N;)
		{
            int r=Inc(l);
            if(U[l]){l++;continue;}
            any=true;
            int len=0;
            while(U[r])len++,r=Inc(r);
            for(int i=0;i<len;++i)CNT[i]+=len-i;
            if(r<=l)break;
            l=r;
        }
        if(!any)for(int i=0;i<N;++i)CNT[i]+=N;
        for(int i=0;i<N;++i)if(GG[i]==f)res+=CNT[i];
    }
    cout<<res<<endl;
    return 0;
}
