#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int n,q,st[1000000];
struct pairtype{int x,y,z;};
vector<pairtype> S;
pairtype newpair(int a,int b,int d){pairtype c;c.x=a,c.y=b,c.z=d;return c;}
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
void buildtree(int id,int l,int r)
{
	if(l==r)
	{
		st[id]=S[l].y;
		return;
	}
	int mid=(l+r)/2;
	buildtree(id*2,l,mid);
	buildtree(id*2+1,mid+1,r);
	st[id]=st[id*2]>st[id*2+1]?st[id*2]:st[id*2+1];
}
int query(int id,int l,int r,int L,int R)
{
	if(l>=L&&r<=R) return st[id];
	if(l>R||r<L) return 0;
	int mid=(l+r)/2;
	int a=query(id*2,l,mid,L,R),b=query(id*2+1,mid+1,r,L,R);
	return a>b?a:b;
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
		buildtree(1,0,S.size()-1);
		while(q--)
		{
			scanf("%d%d",&a,&b);
			int c=fin(a),d=fin(b);
			//printf("%d %d c=%d,d=%d\n",a,b,c,d);
			printf("%d\n",c==d?b-a+1:finMax(S[c].z-a+1,c+1<=d-1?query(1,0,S.size()-1,c+1,d-1):0,d>0?b-S[d-1].z:0));
		}
	}
	return 0;
}
