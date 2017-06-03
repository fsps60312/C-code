#include<cstdio>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
void getmin(int &a,int b){if(b<a)a=b;}
int T,N,B;
char TYPE[21],NAME[21];
struct Pq
{
    int p,q;
    Pq(int _p,int _q):p(_p),q(_q){}
    bool operator<(Pq a)const
    {
        if(q!=a.q)return q>a.q;
        return p<a.p;
    }
};
map<string,vector<Pq> >CPN;
void getmax(int &a,int b){if(b>a)a=b;}
int price(vector<Pq> v,int q)
{
    int l=0,r=v.size()-1;
    while(l<r)
    {
        int mid=(l+r+1)/2;
        if(v[mid].q<q)r=mid-1;
        else l=mid;
    }
    return v[l].q>=q?v[l].p:-1;
}
bool canfit(int q)
{
    int ans=0;
    for(map<string,vector<Pq> >::iterator it=CPN.begin();it!=CPN.end();it++)
    {
        vector<Pq> &v=it->second;
        int p=price(v,q);
        if(p==-1)return false;
        ans+=p;
    }
    return ans<=B;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&B);
		CPN.clear();
        for(int i=0;i<N;i++)
        {
            int p,q;
            scanf("%s%s%d%d",TYPE,NAME,&p,&q);
            CPN[TYPE].push_back(Pq(p,q));
        }
        for(map<string,vector<Pq> >::iterator it=CPN.begin();it!=CPN.end();it++)
        {
            vector<Pq> &v=it->second;
            sort(v.begin(),v.end());
            for(int i=1;i<v.size();i++)
            {
                getmin(v[i].p,v[i-1].p);
            }
        }
        int l=0,r=1000000000;
        while(l<r)
        {
            int mid=(l+r+1)/2;
            if(canfit(mid))l=mid;
            else r=mid-1;
        }
        printf("%d\n",l);
	}
	return 0;
}
