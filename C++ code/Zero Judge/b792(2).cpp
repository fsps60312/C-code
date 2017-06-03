#include<bits/stdc++.h>
using namespace std;
int main()
{
    //freopen("out.txt","w",stdout);
    int T;
    while((scanf("%d",&T))==1)
    {
        while(T--)
        {
            int cn;int goal;
            scanf("%d%d",&cn,&goal);
            int cv[cn];int dp[goal+1];
            for(int i=0;i<=cn-1;i++)
                scanf("%d",&cv[i]);
            for(int i=0;i<=goal;i++)dp[i]=0;
//            memset(dp,0,sizeof(dp));
			dp[0]=1;
            for(int i=0;i<=cn-1;i++)
            {
                int asdf;
                if(cv[i]) asdf=goal/cv[i];
                else asdf=0;
                while(asdf--)
                {
                    for(int j=0;j<=goal;j++)
                    {
                        if(cv[i]+j>goal) break;
                        else if(dp[j]) dp[cv[i]+j]=1;
                    }
                }
            }
            for(int i=goal;i>=0;i--)
            {
                if(dp[i]!=0) {printf("%d\n",i);break;}
                //printf("%d %d\n",i,dp[i]);
            }
        }
    }
    return 0;
}
