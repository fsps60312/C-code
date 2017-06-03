#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
vector<int> door[100];
int energy[100];
int main()
{
    while(scanf("%d",&n)==1)
    {
        if(n==-1) break;
        for(int i=0,j,k;i<n;i++)
        {
            scanf("%d%d",&energy[i],&j);
            while(j--)
            {
                scanf("%d",&k);
                door[i].push_back(k);
            }
        }
    }
    return 0;
}
