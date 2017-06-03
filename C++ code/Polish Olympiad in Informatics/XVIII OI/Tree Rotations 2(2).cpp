#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Bit
{
	int S[1000001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	inline void Add(int i,const int v){while(i<=N)S[i]+=v,i+=i&(-i);}
	inline int Query(int i)const{int ans=0;while(i)ans+=S[i],i-=i&(-i);return ans;}
}BIT;
int CH[2000000][2],VAL[2000000],SZ[2000000],NSZ;
//struct TreeNode
//{
//	TreeNode *ch[2];
//	int v;
//	LL sz;
//	TreeNode(const int _v):v(_v),sz(v?1LL:0LL){ch[0]=ch[1]=NULL;}
//};
int BuildTree()
{
	const int ans=++NSZ;
	scanf("%d",&VAL[ans]);
	if(VAL[ans]==0)
	{
		int *ch=CH[ans];
		ch[0]=BuildTree();
		ch[1]=BuildTree();
		SZ[ans]=SZ[ch[0]]+SZ[ch[1]];
	}
	else SZ[ans]=1;
	return ans;
}
LL ANS;
int S[2000000],SSZ;
void Solve(const int o)
{
	if(SZ[o]==1){S[++SSZ]=VAL[o];BIT.Add(VAL[o],1);return;}
	int *ch=CH[o];
	if(SZ[ch[0]]>SZ[ch[1]])swap(ch[0],ch[1]);
	const int l=SSZ+1;
	Solve(ch[0]);
	const int r=SSZ;
	for(int i=l;i<=r;i++)BIT.Add(S[i],-1);
	Solve(ch[1]);
	LL ta=0LL;
	for(int i=l;i<=r;i++)ta+=BIT.Query(S[i]);
	ANS+=min(ta,(LL)SZ[ch[0]]*SZ[ch[1]]-ta);
	for(int i=l;i<=r;i++)BIT.Add(S[i],1);
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	BIT.Clear(N);
	NSZ=-1;
	const int root=BuildTree();
	SSZ=-1;
	Solve(root);
	printf("%lld\n",ANS);
	return 0;
}
