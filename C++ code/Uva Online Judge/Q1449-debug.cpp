#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<queue>
#include<set>
using namespace std;
struct node
{
    int count,id;
    struct node *next[26];
    struct node *fail;
    void init()
    {
        int i;
        for(i=0;i<26;i++)
            next[i]=NULL;
        count=0;
        fail=NULL;
        id=-1;
    }
}*root;
void insert(char *str,int id)
{
    int len,k;
    node *p=root;
    len=strlen(str);
    for(k=0;k<len;k++)
    {
        int pos=str[k]-'a';
        if(p->next[pos]==NULL)
        {
            p->next[pos]=new node;
            p->next[pos]->init();
            p=p->next[pos];
        }
        else
            p=p->next[pos];
    }
    p->count++;
    p->id=id;
}
void getfail()
{
    int i;
       node *p=root,*son,*temp;
       queue<struct node *>que;
       que.push(p);
       while(!que.empty())
       {
           temp=que.front();
           que.pop();
           for(i=0;i<26;i++)
           {
               son=temp->next[i];
               if(son!=NULL)
               {
                   if(temp==root) {son->fail=root;}
                   else
                   {
                       p=temp->fail;
                       while(p)
                       {
                           if(p->next[i])
                           {
                               son->fail=p->next[i];
                               break;
                           }
                           p=p->fail;
                       }
                       if(!p)  son->fail=root;
                   }
                   que.push(son);
               }
           }
       }
}
int num[200];
char str[1000000+100];
void query()
{
    int len,i,cnt=0;
    len=strlen(str);
    node *p,*temp;
    p=root;
    for(i=0;i<len;i++)
    {
        int pos=str[i]-'a';
        while(!p->next[pos]&&p!=root)  p=p->fail;
        p=p->next[pos];//
        if(!p) p=root;//
        temp=p;
        /*���n��*temp=*p  �]?*p��ܤ@?node�A��*temp�]��ܤ@?node ���O�Ѥ_*temp?�����t��? �ҥH�O����?��?�Ȫ� ���O�i�H��temp��?�h���Vp*/
        while(temp!=root)
        {
            if(temp->count>=1)
            {
                if(temp->id!=-1)
                   num[temp->id]++;
                  // temp->count=-1;
            }
            temp=temp->fail;
        }
    }
    //printf("%d\n",cnt);
}
char rem[160][100];
int main()
{
	freopen("in.txt","r",stdin);
	freopen("New.txt","w",stdout);
    int cas,n;
    while(scanf("%d",&n)!=EOF)
    {
        if(!n) break;
        root=new node;
        root->init();
        root->fail=NULL;
        int i;
        getchar();

        for(i=0;i<n;i++)
        {
            gets(rem[i]);
            insert(rem[i],i);
        }

        getfail();
        memset(num,0,sizeof(num));

        gets(str);
        query();

        int maxnum=-1;
        for(i=0;i<n;i++)
        {
           // printf("num[%d]=%d\n",i,num[i]);
            if(num[i]>maxnum) maxnum=num[i];
        }
        printf("%d\n",maxnum);
        for(i=0;i<n;i++)
            if(maxnum==num[i])  printf("%s\n",rem[i]);
    }
    return 0;
}

