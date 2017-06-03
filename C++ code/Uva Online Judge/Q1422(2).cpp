#include<cstdio>
#include<cstdlib>
#include<vector>
struct pairtype
{
	int a,b;
};
struct inputtype
{
	int a,b,c;
};
using namespace std;
int T,n,site;
vector<pairtype> v;
inputtype input[100000];
vector<pairtype> S[200000];
void add(int a,int b)
{
	pairtype c;
	c.a=a,c.b=b;
	//sort by c.b
	int Min=0,Max=v.size(),mid;
	while(Min<Max)
	{
		mid=(Min+Max)/2;
		if(v[mid].b>b) Min=mid+1;
		else Max=mid;
	}
	if(Max==v.size()) v.push_back(c);
	else if(v[Max].b==b) v[Max].a+=c.a;
	else//v[Max]<b
	{
		v.push_back(c);
		for(int i=v.size()-1;i>Max;i--)
		{
			v[i]=v[i-1];
		}
		v[Max]=c;
	}
	//for(int i=0;i<v.size();i++) printf(" %d",v[i].b);printf("\n");
}
bool consume(int a,int b)//b is deadline
{
	if(v.size()==0) return true;
	int c=v.size()-1;
	if(b>=v[c].b) return false;
	while(1)
	{
		if(v[c].a<=a)
		{
			a-=v[c].a;
			v.pop_back();
			if(v.size()==0) return true;
		}
		else
		{
			v[c].a-=a;
			return true;
		}
		c--;
	}
}
bool check(int a)
{
	v.clear();
	for(int i=0;i<=site;i++)
	{
		if(S[i].size()>0)//to add
		{
			for(int j=S[i].size()-1;j>=0;j--)
			{
				add(S[i][j].a,S[i][j].b);
			}
		}
		if(!consume(a,i)) return false;
	}
	for(int i=site+1;;i++)
	{
		if(!consume(a,i)) return false;
		if(v.size()==0) return true;
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		int Max=0,Min=2147483647;
		for(int i=0;i<n;i++)
		{
			scanf("%d%d%d",&input[i].a,&input[i].b,&input[i].c);
			if(input[i].a<Min) Min=input[i].a;
			if(input[i].b>Max) Max=input[i].b;
		}
		site=Max-Min;
		for(int i=0;i<=site;i++)
		{
			S[i].clear();
		}
		for(int i=0,j;i<n;i++)
		{
			j=input[i].a-Min;
			pairtype c;
			c.a=input[i].c;
			c.b=input[i].b-Min;
			S[j].push_back(c);
		}
		//for(int i=0;i<=site;i++) printf("%d %d\n",S[i].a,S[i].b);
		Min=1,Max=10000000;
		int mid;
		while(Min<Max)
		{
			mid=(Min+Max)/2;
			if(!check(mid)) Min=mid+1;
			else Max=mid;
		}
		printf("%d\n",Max);
	}
	return 0;
}
