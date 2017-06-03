#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
int W;
vector<char>S;
vector<int>NEXT_BRACKET;
struct Node
{
	char o;
	Node *lch,*rch;
	bool IsVar(const char c){return 'A'<=c&&c<'A'+W;}
	Node(int _l,int _r)
	{
		while(NEXT_BRACKET[_l]==_r)++_l,--_r;
		const int l=_l,r=_r;
		if(l==r)
		{
			assert(IsVar(o=S[r]));
			return;
		}
		else
		{
			for(int t=0;t<2;t++)
			{
				for(int i=l;i<=r;i++)
				{
					if(S[i]=='(')i=NEXT_BRACKET[i];
					else if(S[i]==(t==0?'o':'a'))
					{
						o=S[i];
						lch=new Node(l,i-1);
						rch=new Node(i+1,r);
						return;
					}
				}
			}
//			printf("(%d,%d)\n",l,r);
			assert((o=S[l])=='n');
			lch=new Node(l+1,r);
			return;
		}
		assert(0);
	}
	bool GetValue(const int v)
	{
		if(IsVar(o))return (v&(1<<(o-'A')))>0;
		switch(o)
		{
			case'n':return !lch->GetValue(v);
			case'a':return lch->GetValue(v)&rch->GetValue(v);
			case'o':return lch->GetValue(v)|rch->GetValue(v);
			default:assert(0);return false;
		}
	}
}*ROOT;
void BuildNextBracket()
{
	NEXT_BRACKET.clear();
	NEXT_BRACKET.resize(S.size(),-1);
	vector<int>stk;
	for(int i=(int)S.size()-1;i>=0;i--)
	{
		if(S[i]==')')stk.push_back(i);
		if(S[i]=='(')
		{
			assert(!stk.empty());
			NEXT_BRACKET[i]=stk.back();
			stk.pop_back();
		}
	}
	assert(stk.empty());
}
bool WIN[1<<20],VIS[1<<20];
bool Win(const int v,const int remain,const bool player)
{
	bool &win=WIN[(v<<W)|remain];
	if(VIS[(v<<W)|remain])return win;
	VIS[(v<<W)|remain]=true;
	if(remain==0)
	{
//		printf("%d->%d\n",v,ROOT->GetValue(v));
		return win=ROOT->GetValue(v);
	}
	const bool oppo=player^true;
	for(int i=0;i<W;i++)if(remain&(1<<i))
	{
		const int nxtr=remain-(1<<i);
		if(Win(v,nxtr,oppo)!=oppo||Win(v|(1<<i),nxtr,oppo)!=oppo)return win=player;
	}
	return win=oppo;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;
	scanf("%d",&testcount);
	int nxtW;
	for(scanf("%d",&nxtW);testcount--;)
	{
		W=nxtW;
		S.clear();
		for(char str[100];scanf("%s",str)==1&&sscanf(str,"%d",&nxtW)!=1;)S.push_back(str[0]);
		BuildNextBracket();
//		for(const char c:S)putchar(c);puts("");
		ROOT=new Node(0,(int)S.size()-1);
		for(int i=0;i<(1<<(W*2));i++)VIS[i]=false;
		puts(Win(0,(1<<W)-1,true)?"Cook":"Levin");
	}
	return 0;
}
