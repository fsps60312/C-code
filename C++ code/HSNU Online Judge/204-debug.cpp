#include<bits/stdc++.h>
#define LL long long
using namespace std;
vector<pair<int,int> >TMP;
void get_dif(const vector<LL>&v,map<LL,vector<int> >&mp)
{
    int n=v.size();TMP.clear();
    for(int i=0;i<(1<<n);i++)for(int j=i;;j=((j-1)&i))
    {
        LL sum=0LL;
        for(int k=0;k<n;k++)
        {
            if(j&(1<<k))sum+=v[k];
            else if(i&(1<<k))sum-=v[k];
        }
        if(sum>=0)TMP.push_back(make_pair(i,sum));
        if(j==0)break;
    }
    sort(TMP.begin(),TMP.end());
    TMP.resize(unique(TMP.begin(),TMP.end())-TMP.begin());
    for(auto i:TMP)mp[i.second].push_back(i.first);
}
vector<LL> L,R;
map<LL,vector<int> >MP[2];
bool OK[1050000];
int N;
main()
{
	freopen("in.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;i++)
    {
        LL x;scanf("%I64d",&x);
        if(i%2)L.push_back(x);
        else R.push_back(x);
    }
    get_dif(L,MP[0]);
    get_dif(R,MP[1]);
    for(auto i:MP[0])
    {
        auto it=MP[1].find(i.first);
        if(it!=MP[1].end())
        {
            for(auto j:i.second)for(auto k:it->second)OK[j|(k<<L.size())]=1;
        }
    }
    printf("%d\n",count(OK+1,OK+(1<<N),1));
}

