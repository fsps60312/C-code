#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;
const LL bound=100000LL;
struct Node
{
	vector<Node*>ch;
	const LL v;
	LL sz;
	Node(const LL _v):v(_v),sz(0LL){}
}
//vector<LL>P;
//void BuildP()
//{
//	bool *isp=new bool[1000001];
//	for(int i=2;i<=1000000;i++)isp[i]=true;
//	for(int i=2;i<=1000000;i++)if(isp[i])
//	{
//		P.push_back(i);
//		for(int j=2;i*j<=1000000;j++)isp[i*j]=false;
//	}
//	delete[]isp;
////	for(int i=0;i<100;i++)printf("%d\n",P[i]);
//}
map<pair<LL,LL>,Node*>S;
Node *GetNode(const pair<LL,LL>&p)
{
	auto it=S.find(p);
	if(it!=S.end())return it->second;
	Node* &ans=S[p]=new Node[p.second];
	if(p.first==0){(ans->sz)=1LL;return ans;}
	vector<LL>stk;
	for(LL i=1LL;i*i<=p.second;i++)if(p.second%i==0LL)
	{
		if((ans->sz)>=BOUND)return;
		Node *ch=GetNode(make_pair(p.first-1LL,i));
		(ans->ch).push_back(ch);
		(ans->sz)+=(ch->sz);
		if(i*i!=p.second)stk.push_back(p.second/i);
	}
	for(int i=(int)stk.size()-1;i>=0;i--)
	{
		if((ans->sz)>=BOUND)return;
		Node *ch=GetNode(make_pair(p.first-1LL,stk[i]));
		(ans->ch).push_back(ch);
		(ans->sz)+=(ch->sz);
	}
}
LL X,K;
int main()
{
//	BuildP();
	while(scanf("%lld%lld",&X,&K)==2)
	{
		if(K>=100000)for(int i=0;i<100000;i++)printf("1%c"," \n"[i==99999]);
		else
		{
			S.clear();
			Node *o=GetNode(make_pair(K,X));
			int cnt=100000;
			vector<LL>ans;
			Print(o,cnt,K,ans);
			for(int i=0;i<(int)ans.size();i++)
			{
				if(i)putchar(' ');
				printf("%lld",ans[i]);
			}
			puts("");
		}
	}
	return 0;
}
