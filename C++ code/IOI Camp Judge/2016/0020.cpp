#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
	puts("1\n139 923415668714480043");return 0;
  int T;
  scanf("%d",&T);
  while(T--) {
    LL a,b;
    scanf("%lld%lld",&a,&b);
    if(a<=1 || b==0) {
      puts("-1");
      continue;
    }
    if(a>1000000000){printf("%d\n",a<=b);continue;}
    int ans=0;
    LL c = 1, lastc;
    while(c<=b) {
      ans++;
      lastc = c;
      c*=a;
      if(c <= lastc || (a>514 && lastc*514>1e18)) break;
    }
    printf("%d\n",ans-1);
  }
}
