#include<cstdio>
#include<cstdlib>
unsigned long long p[20],ans[10000000],tmp[10000000],n;
bool isp[65];
void rangeans(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangeans(a,mid);
	rangeans(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&ans[c]<ans[d]))
		{
			tmp[i]=ans[c];
			c++;
		}
		else
		{
			tmp[i]=ans[d];
			d++;
		}
	}
	for(int i=a;i<=b;i++)
	{
		ans[i]=tmp[i];
	}
}
int main()
{
	for(int i=0;i<=64;i++) isp[i]=false;
	p[0]=2,p[1]=3;
	for(int i=2,j;;i++)
	{
		p[i]=p[i-1];
		do
		{
			p[i]+=2;
			for(j=0;p[j]*p[j]<=p[i];j++)
			{
				if(p[i]%p[j]==0) break;
			}
		}while(p[i]%p[j]==0);
		if(p[i]>=64) break;
	}
	isp[1]=true;
	for(int i=0;p[i]<=64;i++) isp[p[i]]=true;
	ans[0]=1;
	n=0;
	for(int i=2;i<=65536;i++)
	{
		for(unsigned long long j=1,k=1;k<=18446744073709551615llu/i;j++)
		{
			k*=i;
			if(!isp[j])
			{
				ans[++n]=k;
			}
		}
	}
	//for(int i=0;i<=n;i++) printf("%lld\n",ans[i]);
	/*rangeans(0,n);
	for(int i=0;18446744073709551615llu/ans[i]>ans[i];i++)
	{
		for(int j=i+1;18446744073709551615llu/ans[i]>=ans[j];j++)
		{
			ans[++n]=ans[i]*ans[j];
		}
	}*/
	rangeans(0,n);
	for(int i=1;i<=n;i++)
	{
		if(ans[i-1]!=ans[i]) printf("%llu\n",ans[i-1]);
	}
	printf("%llu\n",ans[n]);
	return 0;
}
