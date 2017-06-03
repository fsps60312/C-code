#include<cstdio>
#include<cassert>
#include<cmath>
#include<algorithm>
using namespace std;
struct Node
{
	Node *ch[2];
	Node():ch{NULL,NULL}{}
};
Node *Add(Node *o,const int v,const int dep)
{
	if(dep==-1)return new Node();
	Node *ans=new Node();
	const int d=(v>>dep)&1;
	ans->ch[d]=Add(o?o->ch[d]:NULL,v,dep-1);
	ans->ch[d^1]=o?o->ch[d^1]:NULL;
	return ans;
}
int QueryMax(Node *o,const int v,const int dep)
{
	if(dep==-1)return 0;
	const int d=((v>>dep)&1)^1;
	if(o->ch[d])return (1<<dep)^QueryMax(o->ch[d],v,dep-1);
	else return QueryMax(o->ch[d^1],v,dep-1);
}
int N,M,Q,S[15001];
Node *TREE[124][124];
int ANS[124][124];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&Q)==2)
	{
		S[0]=0;
		for(int i=1;i<=N;i++)scanf("%d",&S[i]),S[i]^=S[i-1];//,printf("S[%d]=%d\n",i,S[i]);
		M=max((int)sqrt(N),1);
		for(int i=0;i<=(N-1)/M;i++)
		{
			Node *o=Add(NULL,S[i*M],30);
			int ans=0;
			for(int j=i;j<=(N-1)/M;j++)
			{
				for(int k=j*M+1;k<=(j+1)*M&&k<=N;k++)
				{
					ans=max(ans,QueryMax(o,S[k],30));
					o=Add(o,S[k],30);
				}
//				printf("i=%d,j=%d,from %d to %d\n",i,j,i*M,min((j+1)*M,N));
				ANS[i][j]=ans;
				TREE[i][j]=o;
			}
		}
		for(int l,r;Q--;)
		{
			scanf("%d%d",&l,&r),--l,--r;
			int bl=l/M,br=r/M;
			++bl,--br;
			if(bl<=br)
			{
				int ans=ANS[bl][br];
				Node *o=TREE[bl][br];
//				printf("type1: from %d to %d\n",l,bl*M-1);
				for(int i=l;i<bl*M;i++)ans=max(ans,QueryMax(o,S[i],30)),o=Add(o,S[i],30);
//				printf("type1: from %d to %d\n",(br+1)*M+1,r+1);
				for(int i=r+1;i>(br+1)*M;i--)ans=max(ans,QueryMax(o,S[i],30)),o=Add(o,S[i],30);
				printf("%d\n",ans);
			}
			else
			{
//				printf("type2: from %d to %d\n",l,r+1);
				Node *o=Add(NULL,S[l],30);
				int ans=0;
				for(int i=l+1;i<=r+1;i++)ans=max(ans,QueryMax(o,S[i],30)),o=Add(o,S[i],30);
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
