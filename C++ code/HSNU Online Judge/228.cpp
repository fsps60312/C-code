#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int &b){if(b<a)a=b;}
void getmax(int &a,const int &b){if(b>a)a=b;}
int N,L[100000],R[100000],MN[100000],MX[100000];
void Maintain(const int &a,const int &b){getmin(MN[a],MN[b]),getmax(MX[a],MX[b]);}
int MarkH(const int &u,const int &dep)
{
	assert(u>=0&&u<N);
	MN[u]=INF,MX[u]=-INF;
	int a=0,b=0;
	if(L[u]==-2)getmin(MN[u],dep),getmax(MX[u],dep);
	else
	{
		if((a=MarkH(L[u],dep+1))==-1)return -1;
		Maintain(u,L[u]);
	}
	if(R[u]==-2)getmin(MN[u],dep),getmax(MX[u],dep);
	else
	{
		if((b=MarkH(R[u],dep+1))==-1)return -1;
		Maintain(u,R[u]);
	}
//	printf("%d:(%d,%d)(%d,%d)\n",u+1,MN[u],MX[u],a,b);
	assert(MX[u]>=MN[u]);
	if(MX[u]-MN[u]>1)return -1;
	else if(MX[u]==MN[u])return 0;
	if(L[u]!=-2&&R[u]!=-2)
	{
		bool bl=(MX[L[u]]>MN[L[u]]),br=(MX[R[u]]>MN[R[u]]);
		if(bl&&br)return -1;
		int ans=a+b;
		if(bl&&MX[R[u]]==MX[L[u]])ans++;
		else if(br&&MN[L[u]]==MN[R[u]])ans++;
		else if(!bl&&!br&&MX[L[u]]<MN[R[u]])ans++;
		return ans;
	}
	else if(L[u]!=-2&&R[u]==-2)return a;
	else if(L[u]==-2&&R[u]!=-2)return b+1;
	else assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	assert(N>=1&&N<=100000);
	for(int i=0;i<N;i++)
	{
		scanf("%d%d",&L[i],&R[i]);
		L[i]--,R[i]--;
	}
	int ans=MarkH(0,0);
	printf("%d\n",ans);
	return 0;
}
