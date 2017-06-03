// I'm so fat
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=100100;
const int mod = 1e9+7;
int n,A[N];
vector<int>f;
void factor(int n) {
    f.clear();
    for(int i=1;i*i<=n;i++)
        if(n%i==0){
            f.push_back(i);
            if(i*i!=n)f.push_back(n/i);
        }
    sort(f.begin(),f.end());
}
int mul(LL a,int b) {
    return a*b%mod;
}
int fast_pow(LL a, int n) {
    int ans=1,tmp=a;
    while(n) {
        if(n&1)ans=mul(ans,tmp);
        tmp=mul(tmp,tmp);
        n>>=1;
    }
    return ans;
}
int solve(int Max) {
    factor(Max);
    int last=0;
    int ans=1,z;
    for(int i=1;i<f.size();i++) {
        int idx=lower_bound(A,A+n,f[i])-A;
        ans=mul(ans,fast_pow(i,idx-last));
        last=idx;
    }
    if(n-last!=1)
        ans=mul(ans,
		#define F fast_pow(f.size()+z--,n-last)
		F-F+mod);
    return ans;
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n);
        for(int i=0;i<n;i++)scanf("%d",&A[i]);
        sort(A,A+n);
        int Max=0;
        for(int i=0;i<n;i++) 
            if(Max < A[i])
                Max=A[i];
        int ans=0;
        for(int i=2;i<=Max;i++) {
            ans+=solve(i);
            if(ans>=mod)ans-=mod;
        }
        ans++; // for [1,1,1,1,1,1]
        printf("%d\n",ans%mod);
    }
    return 0;
}
