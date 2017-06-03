#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,C,O,TAG[400000];
bool CNT[400000][30];
void PutDown(const int id)
{
	if(TAG[id]==-1)return;
	TAG[id*2]=TAG[id*2+1]=TAG[id];
	for(int i=0;i<C;i++)CNT[id*2][i]=CNT[id*2+1][i]=(i==TAG[id]);
	TAG[id]=-1;
}
void Maintain(const int id)
{
	for(int i=0;i<C;i++)CNT[id][i]=(CNT[id*2][i]||CNT[id*2+1][i]);
}
void Modify(const int id,const int l,const int r,const int bl,const int br,const int val)
{
	if(r<bl||br<l)return;
	if(bl<=l&&r<=br)
	{
		for(int i=0;i<C;i++)CNT[id][i]=(i==val);
		TAG[id]=val;return;
	}
	PutDown(id);
	const int mid=(l+r)/2;
	Modify(id*2,l,mid,bl,br,val),Modify(id*2+1,mid+1,r,bl,br,val);
	Maintain(id);
}
void Query(const int id,const int l,const int r,const int bl,const int br,bool *cnt)
{
	if(r<bl||br<l)return;
	if(bl<=l&&r<=br)
	{
		for(int i=0;i<C;i++)cnt[i]|=CNT[id][i];
		return;
	}
	PutDown(id);
	const int mid=(l+r)/2;
	Query(id*2,l,mid,bl,br,cnt),Query(id*2+1,mid+1,r,bl,br,cnt);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&C,&O);
	Modify(1,1,N,1,N,0);
	for(int a,b,c;O--;)
	{
		static char type[2];scanf("%s",type);
		if(type[0]=='C')
		{
			scanf("%d%d%d",&a,&b,&c),c--;
			if(a>b)swap(a,b);
			Modify(1,1,N,a,b,c);
		}
		else if(type[0]=='P')
		{
			scanf("%d%d",&a,&b);
			if(a>b)swap(a,b);
			static bool cnt[30];
			for(int i=0;i<C;i++)cnt[i]=false;
			Query(1,1,N,a,b,cnt);
			int ans=0;
			for(int i=0;i<C;i++)if(cnt[i])ans++;
			printf("%d\n",ans);
		}
		else assert(0);
	}
	return 0;
}
