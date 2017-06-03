#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+10;
set<pair<int,int> > ST;
void insert(const pair<int,int> &p)
{
    ST.insert(p);
    set<pair<int,int> >::iterator it=ST.find(p);
    bool keep=1;
    if(it!=ST.begin())
    {
        it--;
        if(it->second>p.second)keep=0;
        it++;
    }
    if(!keep){ST.erase(it);return;}
    while(1)
    {
        set<pair<int,int> >::iterator it2=it;
        it2++;if(it2==ST.end())break;
        if(it2->second<p.second)ST.erase(it2);
        else break;
    }
}
int N,A[maxn],MI[maxn];
set<int>STI;
bool check()
{
    for(int i=1;i<N;i++)
    {
        if(i==1){STI.insert(A[1]);continue;}
        if(A[i]<(*STI.begin())){STI.insert(A[i]);continue;}
        if(!ST.empty()&& (*ST.begin()).second < A[i])
        {
            set<pair<int,int> >::iterator it=ST.lower_bound(make_pair(A[i],A[i]));
            it--;
            if(MI[i+1]<it->second)return 0;
        }
        set<int>::iterator it=STI.lower_bound(A[i]);it--;
        insert(make_pair(A[i],*it));/// a[i] > *it
        STI.insert(A[i]);
    }
    return 1;
}
int FA[maxn];
int getfa(int x)
{
    return FA[x]==x?x:FA[x]=getfa(FA[x]);
}
vector<int>ET[maxn];
void add_edge(int x,int y)
{
    if(getfa(x)==getfa(y))return;
    ET[x].push_back(y);
    ET[y].push_back(x);
    FA[getfa(x)]=getfa(y);
}
int ANS[maxn];
void dfs(int x)
{
    for(auto i:ET[x])
	{
		if(!ANS[i])ANS[i]=3-ANS[x],dfs(i);
		else assert(ANS[i]==3-ANS[x]);
	}
}
int INV[maxn];
int main()
{
//	freopen("in.txt","r",stdin);
    scanf("%d",&N);
    for(int i=1;i<=N;i++)scanf("%d",&A[i]),INV[A[i]]=i;
    for(int i=N;i>=1;i--)MI[i]=(i==N?A[i]:min(MI[i+1],A[i]));
    assert(STI.empty());
    if(!check()){printf("NIE\n");return 0;}
    STI.clear();
    for(int i=1;i<=N;i++)FA[i]=i;
    for(int i=1;i<N;i++)
    {
        STI.insert(A[i]);
        if(A[i]==(*STI.begin()))continue;
        set<int>::iterator it=STI.lower_bound(A[i]);it--;
        while(*it>MI[i+1])//A[i]>*it, A[i]>*it>A[j], INV[*it]<i<j
        {
            add_edge(INV[*it],i);
            if(A[i]<A[i-1])break;
            if(it==STI.begin())break;
            it--;
        }
    }
    for(int i=1;i<=N;i++)if(!ANS[i])ANS[i]=1,dfs(i);
    printf("TAK\n");
    for(int i=1;i<=N;i++)printf("%d%c",ANS[i]," \n"[i==N]);
}
