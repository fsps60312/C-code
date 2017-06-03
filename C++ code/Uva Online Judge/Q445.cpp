#include<cstdio>
#include<cstdlib>
char tmp;
int n;
int main()
{
    //freopen("input.txt","r",stdin);
    n=0;
    while(scanf("%c",&tmp)==1)
    {
        //printf(" %c\n",tmp);
        switch(tmp)
        {
        case '!':
        case '\n':
            {
                printf("\n");
            }break;
        case 'b':
            {
                while(n--) printf(" ");
                n++;
            }break;
        default:
            {
                if(tmp>='0'&&tmp<='9') n+=(tmp-'0');
                else if(tmp!=' ')
                {
                    while(n--) printf("%c",tmp);
                    n++;
                }
            }break;
        }
    }
    return 0;
}
