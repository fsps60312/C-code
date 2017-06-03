#include<cstdio>
#include<cassert>
#include<vector>
#include<string>
using namespace std;
struct Node
{
	char V;
	Node *CH[26];
	long long SZ;
	Node(const char _V):V(_V),SZ(1){for(int i=0;i<26;i++)CH[i]=NULL;}
};
//void Print(Node *o,string now)
//{
//	if(!o)return;
//	now+=o->V;
//	printf("%s\n",now.c_str());
//	for(int i=0;i<26;i++)Print(o->CH[i],now);
//	now.pop_back();
//}
long long Sz(Node *a){return a?a->SZ:0;}
void Maintain(Node *a){a->SZ=1;for(int i=0;i<26;i++)a->SZ+=Sz(a->CH[i]);}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	assert(a->V==b->V);
	Node *ans=new Node(a->V);
	for(int i=0;i<26;i++)ans->CH[i]=Merge(a->CH[i],b->CH[i]);
	Maintain(ans);
	delete a;delete b;
	return ans;
}
int N,C[300000];
char V[300001];
vector<int>ET[300000];
long long ANS1;
int ANS2;
Node *Dfs(const int u,const int parent)
{
	Node *ans=new Node(V[u]);
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		const int v=V[nxt]-'a';
		ans->CH[v]=Merge(ans->CH[v],Dfs(nxt,u));
	}
	Maintain(ans);
	const long long v=C[u]+ans->SZ;
//	printf("dif(%d)=%d+%lld\n",u+1,C[u],ans->SZ);
//	Print(ans,"");
	if(v>ANS1)ANS1=v,ANS2=1;
	else if(v==ANS1)ANS2++;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		scanf("%s",V);
		for(int i=0;i<N;i++)ET[i].clear(); 
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		ANS1=0;
		Dfs(0,-1);
		printf("%lld\n%d\n",ANS1,ANS2);
	}
	return 0;
}
