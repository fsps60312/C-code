#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=100003;
const int mod=1000000007, X=991;
char a[N],b[N];
LL pre[N];
LL hashval(char s[],int n) {
  LL ret=0;
  for(int i=0;i<n;i++)
    ret = (ret*X + s[i]) % mod;
  return ret;
}
void make_pre(int n) {
  for(int i=1;i<=n;i++)
    pre[i] = (pre[i-1]*X + a[i]) %mod;
}
int main() {
  int T;
  scanf("%d",&T);
  while(T--) {
    scanf("%s%s",a+1,b+1);
    int n=strlen(a+1), m=strlen(b+1);
    if(n < m) {puts("0");continue;}
    LL bval=hashval(b+1,m);
    make_pre(n);
    int ans=0;
    LL offset = 1;
    for(int i=0;i<m;i++) offset = (offset*X) % mod;
    for(int i=m;i<=n;i++)
      if((pre[i] - pre[i-m]*offset%mod + mod)%mod == bval)
        ans++;
    printf("%d\n",ans);
  }
}
