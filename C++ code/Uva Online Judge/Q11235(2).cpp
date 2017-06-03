#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int n,q,st[100000][20];
struct pairtype{int x,y,z;};
vector<pairtype> S;
pairtype newpair(int a,int b,int d){pairtype c;c.x=a,c.y=b,c.z=d;return c;}
void buildtree()
{
	for(int i=0;i<S.size();i++)st[i][0]=S[i].y;
	for(int j=1;(1<<j)<S.size();j++)
	{
		for(int i=S.size()-1-(1<<j);i>=0;i--)
		{
			int a1=st[i][j-1],a2=st[i+(1<<(j-1))][j-1];
			st[i][j]=a1>a2?a1:a2;
		}
	}
}
int RMQ(int a,int b)
{
	int c=0;
	while((1<<(c+1))<=b-a+1) c++;
	int a1=st[a][c],a2=st[b-(1<<c)+1][c];
	return a1>a2?a1:a2;
}
int fin(int a)
{
	int Min=0,Max=S.size()-1,mid;
	while(Min<Max)
	{
		mid=(Min+Max)/2;
		if(a>S[mid].z) Min=mid+1;
		else Max=mid;
	}
	return Max;
}
int finMax(int a,int b,int c)
{
	if(b>a) a=b;
	if(c>a) a=c;
	return a; 
}
int main()
{
	//freopen("in.txt","r",stdin);freopen("out.txt","w",stdout);
	while(scanf("%d",&n)==1&&n)
	{
		S.clear();
		scanf("%d",&q);
		int a,b=1;
		scanf("%d",&a);
		for(int i=1,j;;i++)
		{
			if(i==n)
			{
				S.push_back(newpair(a,b,i));
				break;
			}
			scanf("%d",&j);
			if(j==a) b++;
			else
			{
				S.push_back(newpair(a,b,i));
				b=1,a=j;
			}
		}
		//for(int i=0;i<S.size();i++) printf(" %d %d %d\n",S[i].x,S[i].y,S[i].z);
		buildtree();
		while(q--)
		{
			scanf("%d%d",&a,&b);
			int c=fin(a),d=fin(b);
			//printf("%d %d c=%d,d=%d\n",a,b,c,d);
			printf("%d\n",c==d?b-a+1:finMax(S[c].z-a+1,c+1<=d-1?RMQ(c+1,d-1):0,d>0?b-S[d-1].z:0));
		}
	}
	return 0;
}
