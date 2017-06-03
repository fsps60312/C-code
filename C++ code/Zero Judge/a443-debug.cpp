#include<stdio.h>
#include<algorithm>
#include<functional>
using namespace std;
int n,i;
long long sum[1000005],d[1000005];
int main()
{
//	freopen("in.txt","r",stdin);
    while(scanf("%d",&n)==1&&n)
	{
        sum[0]=0;
        for(i=1;i<=n;i++)scanf("%lld",&d[i]);
        sort(d+1,d+n+1,greater<int>());
        for(i=1;i<=n;i++)sum[i]=sum[i-1]+d[i];
        long long left=0,right;
        int ans=0;
        if(sum[n]&1)ans=-1;
        else
        {
	        for(i=1;i<=n;i++)
			{
	            left+=d[i];
	            right=(long long)i*(i-1);
	            int l=1,r=n,m;
	            while(l<r)
				{
	                m=(l+r)>>1;
	                if(d[m]<=i)r=m;
	                else l=m+1;
	            }
	            if(l<=i)right+=sum[n]-sum[i];
	            else right+=sum[n]-sum[l-1]+(long long)i*(l-i-1);
	            if(left > right){ans=-1;break;}
	        }
		}
        if(ans)puts("Not possible");
        else puts("Possible");
    }
    return 0;
}
