#include <bits/stdc++.h>
using namespace std;
char s[10];
vector<string>rd[8];
int dic[1000 + 10][26],ch[26];
int dfs(int len , int cnt , vector<int> S)
{
    if(cnt == len+1) return 1;
    if((int)S.size() <= 1) return 0;
    for(int i = 0; i < 26; i++)
	{
        if(ch[i]) continue;
        ch[i] = 1;
        int tmp = 0;
        vector<int> TS[8];
        for(int j = 0; j < (int)S.size(); j++)
		{
            int x = S[j];
            if(dic[x][i] == -1) TS[len].push_back(x);
            else TS[dic[x][i]].push_back(x);
        }
        if((int)TS[len].size() == (int)S.size())
		{
            ch[i] = 0;
            continue;
        }
        for(int j = 0; j < len && !tmp; j++)
		{
            if((int)TS[j].size()) tmp |= dfs(len , cnt , TS[j]);
        }
        if(!tmp) tmp |= dfs(len , cnt+1 , TS[len]);
        ch[i] = 0;
        if(!tmp) return 0;
    }
    return 1;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
	{
        int n;
        scanf("%d",&n);
        for(int i = 1; i < 7; i++) rd[i].clear();
        while(n--) scanf("%s",s) , rd[strlen(s)].push_back(static_cast<string>(s));
        int ans = 0;
        for(int i = 1; i < 7 && !ans; i++)
		{
            memset(dic , -1 , sizeof(dic));
            vector<int> S;
            for(int j = 0; j < (int)rd[i].size(); j++)
			{
                S.push_back(j);
                for(int k = 0; k < i; k++) dic[j][rd[i][j][k]-'A'] = k;
            }
            if(!S.empty()) ans |= dfs(i , 0 , S);
        }
        puts(ans ? "Yes" : "No");
    }
}
