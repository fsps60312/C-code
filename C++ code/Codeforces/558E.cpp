#include<cstdio>
#include<cassert>
#include<set>
#include<vector>
using namespace std;
struct Node
{
	int cnt[26],type;
	Node *ch[2];
	Node(const int _v,const int _type):type(_type),ch{NULL,NULL}{for(int i=0;i<26;i++)cnt[i]=(i==_v?1:0);}
}*S[100001],*BEGIN,*END;
int N;
char A[100001];
set<int>LOCS;
void Split(const int loc)
{
	auto it=LOCS.lower_bound(loc);
	if(loc==*it)return;
	const int idx=*(--it);
	printf("idx=%d,loc=%d\n",idx,loc);
	assert(S[loc]==NULL);
	Node* &ans=S[loc]=new Node(-1,S[idx]->type);
	S[loc]->ch[1]=S[idx]->ch[1];
	S[idx]->ch[1]=S[loc],S[loc]->ch[0]=S[idx];
	LOCS.insert(loc);
	const int t=S[idx]->type;
	for(int i=(t==1?0:25),sum=0;;i+=(t==1?1:-1))
	{
		assert(0<=i&&i<=25);
		int &v=S[idx]->cnt[i];
		if(sum+v<loc-idx)ans->cnt[i]+=v,sum+=v,v-=v;
		else{ans->cnt[i]+=loc-idx-sum,v-=loc-idx-sum;break;}
	}
}
void Merge(const int begin,const int end,const int type)
{
	Node *ans=new Node(-1,type);
	assert(S[begin]&&S[end]);
	Node *ln=S[begin]->ch[0],*rn=S[end];
	vector<set<int>::iterator>to_erase;
	for(auto it=LOCS.find(begin),eit=LOCS.find(end);it!=eit;it++)
	{
		to_erase.push_back(it);
		for(int i=0;i<26;i++)ans->cnt[i]+=S[*it]->cnt[i];
		delete S[*it];S[*it]=NULL;
	}
	for(const auto &v:to_erase)LOCS.erase(v);
	ans->ch[0]=ln,ln->ch[1]=ans;
	ans->ch[1]=rn,rn->ch[0]=ans;
	S[begin]=ans;
	LOCS.insert(begin);
}
#include<cstdlib>
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int querycount;
	while(scanf("%d%d",&N,&querycount)==2)
	{
		scanf("%s",A);
		BEGIN=new Node(-1,0),S[N]=END=new Node(-1,0);
		LOCS.clear();LOCS.insert(N);
		for(int i=0;i<N;i++)S[i]=new Node(A[i]-'a',0),LOCS.insert(i);
		for(int i=1;i<N;i++)S[i]->ch[0]=S[i-1],S[i-1]->ch[1]=S[i];
		S[0]->ch[0]=BEGIN,BEGIN->ch[1]=S[0];
		S[N-1]->ch[1]=END,END->ch[0]=S[N-1];
		for(int l,r,k;querycount--;)
		{
			scanf("%d%d%d",&l,&r,&k),l--,r--;
			Split(l),Split(r+1);
			Merge(l,r+1,k);
			auto it=LOCS.begin();
			for(Node *cur=BEGIN->ch[1];cur!=END;cur=cur->ch[1],it++)
			{
				assert(it!=LOCS.end());
//				printf("loc=%d\n",*it);
				const int t=cur->type;
				for(int i=(t==1?0:25);0<=i&&i<=25;i+=(t==1?1:-1))
				{
//					printf("cnt[%d]=%d\n",i,cur->cnt[i]);
					while((cur->cnt[i])>0)putchar('a'+i),(cur->cnt[i])--;
				}
			}
			puts("");
//			system("pause");
		}
	}
	return 0;
}
