#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
const int MAXN=5e4+4;
char A[MAXN],B[MAXN];
int N,M;
const int W=sizeof(unsigned int)*8;
unsigned int MS[26][MAXN/W+1];
unsigned int _[2][MAXN/W+1];
void Solve()
{
    unsigned int *prv=_[0],*cur=_[1];
    for(int i=1;i<=N;i++)
    {
        swap(prv,cur);
        unsigned int ylst=0;
        unsigned int* c=MS[A[i]-'a'];
        for(int j=0;j<M/W+1;j++)
        {
            unsigned int s=c[j]|prv[j];
            unsigned int t=c[j]&~prv[j];
            unsigned int q=s-(t<<1|ylst);
            unsigned int y=(q&~s)|t;
            cur[j]=s&~(y<<1|ylst);
            ylst=y>>(W-1);
        }
    }
    int ans=0;
    for(int j=0;j<M/W+1;j++) for(unsigned int x=cur[j];x;x^=x&-x)
        ans++;
    printf("%d\n",ans);
}
int main()
{
//	printf("W=%d\n",W);
    scanf("%s%s",A+1,B+1);
    N=(int)strlen(A+1);M=(int)strlen(B+1);
    for(int i=1;i<=M;i++) MS[B[i]-'a'][i/W]|=1U<<(i%W);
    Solve();
    return 0;
}
