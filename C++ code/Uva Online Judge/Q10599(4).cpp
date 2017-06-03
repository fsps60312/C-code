#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
const long long CARRYN=100000000000000000LL;
const long long BIGN=4;
struct Big
{
	long long d[BIGN];
	Big(){}
	Big(int a)
	{
		(*this)=a;
	}
	Big operator+(Big a)
	{
		Big ans;
		for(int i=0;i<BIGN;i++)
		{
			ans.d[i]=d[i]+a.d[i];
		}
		ans.carry();
		return ans;
	}
	Big operator+=(Big a){return (*this)=(*this)+a;}
	Big operator=(int a)
	{
		d[0]=a;
		for(int i=1;i<BIGN;i++)
		{
			d[i]=0;
		}
		return (*this);
	}
	Big operator=(Big a)
	{
		for(int i=0;i<BIGN;i++)
		{
			d[i]=a.d[i];
		}
		return (*this);
	}
	void carry()
	{
		for(int i=1;i<BIGN;i++)
		{
			d[i]+=d[i-1]/CARRYN;
			d[i-1]%=CARRYN;
		}
	}
	void print()
	{
		for(int i=0;i<BIGN-1;i++)
		{
			if(!d[i+1])
			{
				printf("%lld",d[i]);
				return;
			}
			printf("%017lld",d[i]);
		}
		printf("%lld",d[BIGN-1]);
	}
	bool iszero()
	{
		for(int i=0;i<BIGN;i++)
		{
			if(d[i]!=0)return false;
		}
		return true;
	}
};
int R,C,GARBAGE[100][100];
void put_GARBAGE()
{
	for(int r=0;r<R;r++)
	{
		for(int c=0;c<C;c++)
		{
			GARBAGE[r][c]=0;
		}
	}
	int a,b;while(scanf("%d%d",&a,&b)==2&&(a||b))
	{
		GARBAGE[--a][--b]=1;
	}
}
vector<int> TO[10000];
int HEIGHT[10000];
vector<int> ROOT; 
Big WAYS[10000];
void add_TO(int r1,int c1,int r2,int c2)
{
	TO[r1*C+c1].push_back(r2*C+c2);
}
bool IsROOT(int r,int c)
{
	if(!ROOT.size())return true;
	int e=ROOT.size()-1;
	return c<=ROOT[e]%C;
}
void build_TO()
{
	for(int r=0;r<R;r++)
	{
		for(int c=0;c<C;c++)
		{
			int i=r*C+c;
			TO[i].clear();
			HEIGHT[i]=0;
			WAYS[i]=0;
		}
	}
	ROOT.clear();
	for(int r=0;r<R;r++)
	{
		for(int c=0;c<C;c++)
		{
			if(GARBAGE[r][c])
			{
				if(IsROOT(r,c))ROOT.push_back(r*C+c);
				int maX=C-1;
				for(int r1=r;r1<R;r1++)
				{
					int tmax=-1;
					for(int c1=c;c1<=maX;c1++)
					{
						if(r1==r&&c1==c)continue;
						if(GARBAGE[r1][c1])
						{
							add_TO(r,c,r1,c1);
							tmax=c1;
						}
					}
					if(tmax!=-1)maX=tmax;
				}
			}
		}
	}
}
void getmax(int &a,int b){if(b>a)a=b;}
int dfs_HEIGHT(int u)
{
	//printf("u=%d\n",u);
	if(!TO[u].size())return HEIGHT[u]=0;
	if(HEIGHT[u])return HEIGHT[u];
	int &h=HEIGHT[u];
	for(int i=0;i<TO[u].size();i++)
	{
		getmax(h,dfs_HEIGHT(TO[u][i])+1);
	}
	return h;
}
Big dfs_WAYS(int u,int h)
{
	if(h>HEIGHT[u])return 0;
	if(TO[u].size()==0)return WAYS[u]=1;
	if(!WAYS[u].iszero())return WAYS[u];
	for(int i=0;i<TO[u].size();i++)
	{
		WAYS[u]+=dfs_WAYS(TO[u][i],h-1);
	}
	return WAYS[u];
}
void dfs_print(int u,int h)
{
	printf(" %d",u+1);
	for(int i=0;i<TO[u].size();i++)
	{
		int nxu=TO[u][i];
		if(HEIGHT[nxu]!=h-1)continue;
		dfs_print(nxu,h-1);
		return;
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d%d",&R,&C)==2&&!(R==-1&&C==-1))
	{
		put_GARBAGE();
		build_TO();
		int ans1=0;
		for(int i=0;i<ROOT.size();i++)
		{
			getmax(ans1,dfs_HEIGHT(ROOT[i]));
		}
		Big ways=0;
		for(int i=0;i<ROOT.size();i++)
		{
			ways+=dfs_WAYS(ROOT[i],ans1);
		}
		printf("CASE#%d: %d ",kase++,ans1+1);
		ways.print();
		for(int i=0;i<ROOT.size();i++)
		{
			if(HEIGHT[ROOT[i]]==ans1)
			{
				dfs_print(ROOT[i],ans1);
				printf("\n");
				break;
			}
		}
	}
	return 0;
}
