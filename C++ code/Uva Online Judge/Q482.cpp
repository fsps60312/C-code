#include<cstdio>
#include<cstdlib>
#include<string>
using namespace std;
struct pairtype
{
	int index;
	string n;
};
pairtype S[1000000],tmp[1000000];
int n,T;
char c[10000];
void range(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	range(a,mid);
	range(mid+1,b);
	int d=a,e=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(e>b||(d<=mid&&S[d].index<S[e].index))
		{
			tmp[i]=S[d];
			d++;
		}
		else
		{
			tmp[i]=S[e];
			e++;
		}
	}
	for(int i=a;i<=b;i++) S[i]=tmp[i];
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		n=0;
		while(scanf("%d%c",&S[n++].index,&c[0])==2&&c[0]!='\n');
		for(int i=0;i<n;i++)
		{
			scanf("%s",c);
			S[i].n=c;
		}
		range(0,n-1);
		for(int i=0;i<n;i++) printf("%s\n",S[i].n.c_str());
		if(T) printf("\n");
	}
	return 0;
}
