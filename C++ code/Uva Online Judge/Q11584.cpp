#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int T,n;
char S[1000];
int tmp[1000];
bool skip[2][1000];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",S);
        for(n=0;S[n];n++)
        {
            tmp[n]=1000000000;
            skip0[n]=skip1[n]=true;
        }
        tmp[n-1]=1;
        for(int i=1;i<n;i+=2)
        {
            for(int j=0;j+i<n;j++)
            {
                if(S[j]==S[j+i]&&skip[j+1])
                {
                    skip1[j]=true;
                    if(tmp[j+i]+1<tmp[j]) tmp[j]=tmp[j+i]+1;
                }
                else skip1[j]=false;
            }
        }
        printf("%d\n",tmp[0]);
    }
    return 0;
}
