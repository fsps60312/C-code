#include<cstdio>
#include<cstdlib>
char S[100002];
int next[100000];
int main()
{
	//freopen("in.txt","r",stdin);
	while(fgets(S,100002,stdin))
	{
		//int start=-1;
		//int *sp=&start,*fp=NULL,*sn=NULL,*fn=NULL;
		int sp=-1,fp=-1,sn=-1,fn=-1;
		int i=0;
		int t=0;
		next[0]=-1;
		while(S[i]!='\n')
		{
			if(S[i]=='[')t=1;
			else if(S[i]==']')t=2;
			else
			{
				if(t==1)//move to front
				{
					next[i]=sp;
					fn=sp;
					sp=i;
					sn=i;
					t=0;
				}
				else if(t==2)//move to end
				{
					(fp==-1?sp:next[fp])=i;
					fp=i;
					fn=-1;
					next[i]=fn;
					sn=i;
					t=0;
				}
				else
				{
					if(sp==-1)sp=sn=i;
					next[sn]=i;
					sn=i;
					next[i]=fn;
					if(fn==-1)fp=i;
				}
			}
			i++;
		}
		//printf("start:%d\n",sp);
		//for(int i=0;S[i];i++)printf(" %c:%d",S[i],next[i]);printf("\n");
		for(int i=sp;i!=-1;i=next[i])printf("%c",S[i]);printf("\n");
	}
	return 0;
}
