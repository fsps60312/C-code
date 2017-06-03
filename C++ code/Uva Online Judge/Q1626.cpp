#include<cstdio>
#include<cstdlib>
#include<vector>
//#include<iostream>
using namespace std;
int T,n;
char S[101],c;
vector<char> a;
vector<char> b;
int main()
{
    //printf("%d %d %d %d\n",'[',']','(',')');
    scanf("%d",&T);
    gets(S);
    while(T--)
    {
        gets(S);
        gets(S);
        for(n=0;S[n];n++);n--;
        a.clear();
        b.clear();
        for(int i=0;;i++)
        {
            //printf("%d %d\n",i,n);
            switch(S[i])
            {
            case '[':
                {
                    a.push_back('[');
                    if(S[i+1]==']')
                    {
                        a.push_back(']');
                        i++;
                    }
                    else
                    {
                        b.push_back(']');
                        if(S[n]==']') n--;
                    }
                }break;
            case ']':
                {
                    a.push_back('[');
                    a.push_back(']');
                }break;
            case '(':
                {
                    a.push_back('(');
                    if(S[i+1]==')')
                    {
                        a.push_back(')');
                        i++;
                    }
                    else
                    {
                        b.push_back(')');
                        if(S[n]==')') n--;
                    }
                }break;
            case ')':
                {
                    a.push_back('(');
                    a.push_back(')');
                }break;
            }
            if(i>=n)
            {
                for(int i=0;i<a.size();i++) printf("%c",a[i]);
                for(int i=b.size()-1;i>=0;i--) printf("%c",b[i]);
                /*if(S[n]=='[')
                {
                    printf("[]");
                    break;
                }
                else if(S[n]=='(')
                {
                    printf("()");
                    break;
                }*/
                printf("\n");
                if(T) printf("\n");
                break;
            }
        }
    }
    return 0;
}
