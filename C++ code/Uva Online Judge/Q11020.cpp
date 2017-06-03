#include<cstdio>
#include<cstdlib>
#include<set>
using namespace std;
struct point
{
    int x,y;
    bool operator<(const point a)const
    {
        if(x!=a.x)return x<a.x;
        return y<a.y;
    }
};
multiset<point> S;
multiset<point>::iterator it;
int T,n;
int main()
{
    scanf("%d",&T);
    int kase=1;
    while(T--)
    {
        scanf("%d",&n);
        S.clear();
        point p;
        printf("Case #%d:\n",kase++);
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&p.x,&p.y);
            it=S.lower_bound(p);
            if(it==S.begin()||(--it)->y>p.y)
            {
                S.insert(p);
                it=S.upper_bound(p);
                while(it!=S.end()&&it->y>=p.y)S.erase(it++);
            }
            printf("%d\n",S.size());
        }
        if(T)printf("\n");
    }
    return 0;
}
