#include<cstdio>
#include<cstdlib>
#include<map>
using namespace std;
map<int,int> M;
map<int,int> IN;
int NOIN;
int findset(int a)
{
	int &ma=M[a];
	return ma==a?a:(ma=findset(ma));
}
bool add(int a,int b)
{
	if(M.find(a)==M.end())M[a]=a,IN[a]=0,NOIN++;
	if(M.find(b)==M.end())M[b]=b,IN[b]=0,NOIN++;
	int fa=findset(a),fb=findset(b);
	if(fa==fb||++IN[b]>1)return false;
	NOIN--;
	M[fa]=fb;
	return true;
}
int main()
{
	//freopen("in.txt","r",stdin);
	int a,b,kase=1;
	while(scanf("%d%d",&a,&b)==2&&!(a==-1&&b==-1))
	{
		M.clear();
		IN.clear();
		NOIN=0;
		bool ans=true;
		if(!(a==0&&b==0))
		{
			ans&=add(a,b);
			while(scanf("%d%d",&a,&b)&&(a||b))
			{
				ans&=add(a,b);
			}
			ans&=(NOIN==1);
			int now=findset(M.begin()->first);
			for(map<int,int>::iterator it=M.begin();it!=M.end();it++)
			{
				if(findset(it->first)!=now)
				{
					ans=false;
					break;
				}
			}
		}
		if(ans)printf("Case %d is a tree.\n",kase++);
		else printf("Case %d is not a tree.\n",kase++);
	}
	return 0;
}
