#include<cstdio>
#include<cstdlib>
#include<vector>
#include<set>
using namespace std;
struct pairtype
{
    long long q;
    vector<long long> r;
};
long long C,S;
//long long pik;
pairtype A[9];
long long tmp1[100],tmp2[10000000],best,pi;
vector<long long> ans;
bool serch(long long a,long long b)
{
	long long Min=0,Max=A[a].r.size()-1,mid;
	while(Min<Max)
	{
		mid=(Min+Max)/2;
		if(A[a].r[mid]<b) Min=mid+1;
		else Max=mid;
	}
	return A[a].r[Max]==b;
}
bool isans(long long a)
{
	for(long long i=0;i<C;i++)
	{
		if(i!=best)
		{
			if(!serch(i,a%A[i].q)) return false;
		}
	}
	return true;
}
void range(long long c,long long a,long long b)
{
	if(a==b) return;
	long long mid=(a+b)/2;
	range(c,a,mid);
	range(c,mid+1,b);
	long long d=a,e=mid+1;
	for(long long i=a;i<=b;i++)
	{
		if(e>b||(d<=mid&&A[c].r[d]<A[c].r[e]))
		{
			tmp1[i]=A[c].r[d];
			d++;
		}
		else
		{
			tmp1[i]=A[c].r[e];
			e++;
		}
	}
	for(long long i=a;i<=b;i++) A[c].r[i]=tmp1[i];
}
void rangeans(long long a,long long b)
{
	if(a==b) return;
	long long mid=(a+b)/2;
	rangeans(a,mid);
	rangeans(mid+1,b);
	long long c=a,d=mid+1;
	for(long long i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&ans[c]<ans[d]))
		{
			tmp2[i]=ans[c];
			c++;
		}
		else
		{
			tmp2[i]=ans[d];
			d++;
		}
	}
	for(long long i=a;i<=b;i++) ans[i]=tmp2[i];
}
long long revrse(long long a,long long b)//b multiply reverse(a,b) mod a equal 1
{
	long long c=0;
	while((++c)*b%a!=1);
	return c;
}
long long china()//tmp1[0]~tmp1[C], tmp2[0]~tmp2[C] (reverse)
{
	long long a=0;
	for(long long i=0;i<C;i++)
	{
		//printf("%lld %lld %lld %lld %lld\n",tmp1[i],A[i].r[tmp1[i]],tmp2[i],pi,A[i].q);
		a+=tmp1[i]*tmp2[i]*pi/A[i].q;
		//printf(" %lld",a);
	}
	//printf(" %lld\n",a%pi);
	return a%pi;
}
void dfs(long long a)
{
	if(a==C)
	{
		ans.push_back(china());
		return;
	}
	for(long long i=0;i<A[a].r.size();i++)
	{
		tmp1[a]=A[a].r[i];
		dfs(a+1);
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
    while(scanf("%lld%lld",&C,&S)==2)
    {
        if(C==0&&S==0) break;
        //pik=1;
        best=0;
        long long limit=1;
        pi=1;
        for(long long i=0;i<C;i++)
        {
            long long x,k;
            scanf("%lld%lld",&x,&k);
			//pik*=k;
			limit*=k;
			pi*=x;
            A[i].q=x;
            A[i].r.clear();
            for(long long j=0;j<k;j++)
            {
                scanf("%lld",&x);
                A[i].r.push_back(x);
            }
            range(i,0,A[i].r.size()-1);
            if(A[i].r.size()*A[best].q<A[best].r.size()*A[i].q) best=i;
        }
        if(limit>10000)
        {
	        long long jend=A[best].r.size();
	        long long iplus=A[best].q;
	        vector<long long> forserch=A[best].r; 
	        for(long long i=0,k;S;i+=iplus)
	        {
	        	for(long long j=0;j<jend;j++)
	        	{
	        		k=forserch[j]+i;
	        		if(k==0) continue;
	        		if(isans(k))
	        		{
	        			printf("%lld\n",k);
	        			S--;
	        			if(!S) break;
					}
				}
			}
			printf("\n");
		}
		else
		{
			//solve by china
        	for(long long i=0;i<C;i++)
        	{
        		tmp2[i]=revrse(A[i].q,pi/A[i].q);//later multiplied by this mod former equal 1
			}
			ans.clear();
			dfs(0);
			rangeans(0,ans.size()-1);
			long long i=0,j=0;
			for(i=0,j=0;i<ans.size();i++)
			{
				if(j==0||ans[i]!=ans[j-1])
				{
					ans[j]=ans[i];
					j++;
				}
			}
			//for(i=0;i<ans.size();i++) printf("%lld\n",ans[i]); printf("\n");
			for(i=j;i<=S;i++)
			{
				if(i==ans.size()) ans.push_back(ans[i-j]+pi);
				else ans[i]=ans[i-j]+pi;
			}
			if(ans[0]) for(i=0;i<S;i++) printf("%lld\n",ans[i]);
			else for(i=1;i<=S;i++) printf("%lld\n",ans[i]);
			printf("\n");
		}
    }
    return 0;
}
