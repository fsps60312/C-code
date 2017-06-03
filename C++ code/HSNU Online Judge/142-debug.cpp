#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int Maxn = 50000 + 10;
const int Maxm = 200000*2 + 10;
struct Edge
{
    int u , v;
    Edge( int _u , int _v ) : u(_u) , v(_v) {}
};
vector<Edge> edges;
vector<int> G[Maxn];
bool IsBridge[Maxm];
int DFS_Clock , PreClock[Maxn];
inline int DFS( int u , int Father )
{
    int lowu = PreClock[u] = ++DFS_Clock , Child = 0;
    for( int i = 0; i < G[u].size(); i++ )
    {
        int v = edges[G[u][i]].v;
        if( !PreClock[v] )
        {
            Child++;
            int lowv = DFS( v , u );
            lowu = min( lowv , lowu );
            if( lowv > PreClock[u] )
                IsBridge[G[u][i]] = true;
        }
        else if( PreClock[v] < PreClock[u] && v != Father )
            lowu = min( lowu , PreClock[v] );
    }
    return lowu;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
    int n , m;
    while(scanf("%d%d",&n,&m)==2)
    {
	    for(int i=1;i<=n;i++)G[i].clear();
	    edge.clear();
	    while( m-- )
	    {
	        int a , b;
	        scanf("%d%d",&a,&b);
	        edges.push_back( Edge( a , b ) );
	        G[a].push_back( edges.size()-1 );
	        edges.push_back( Edge( b , a ) );
	        G[b].push_back( edges.size()-1 );
	    }
	    memset( IsBridge , 0 , sizeof(IsBridge) );
	    memset( PreClock , 0 , sizeof(PreClock) );
	    DFS_Clock = 0;
	    for( int i = 1; i <= n; i++ )
	        if( !PreClock[i] )
	            DFS( i , -1 );
	    int Answer = 0;
	    for( int i = 0; i < edges.size(); i++ )
	        if( IsBridge[i] )
	            Answer++;
	    printf("%d\n",Answer);
	}
    return 0;
}
