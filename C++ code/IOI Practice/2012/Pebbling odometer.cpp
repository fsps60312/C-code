#include<cstdio>
#include<cassert>
#include<vector>
#include<string>
#include<map>
using namespace std;
bool Valid(const int y,const int x){return !(x<0||x>255||y<0||y>255);}
bool Valid(const int y,const int x,const int n){return Valid(x,y)&&!(n<0||n>15);}
vector<string>COMMAND;
map<string,int>LABEL;
int GRID[255][255];
int Label(const string &str)
{
	assert(LABEL.find(str)!=LABEL.end());
	return LABEL[str]; 
}
int id;
bool no_effected;
void ManageNoEffectCode()
{
	printf("no effect: %s\n",COMMAND[id].c_str());
	no_effected=true;
	assert(0);
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<255;i++)for(int j=0;j<255;j++)GRID[i][j]=0;
	for(static char _str[1000],buf[1000];scanf("%s",_str)==1;)
	{
		printf("%s",_str);
		string str=_str;
		if(str=="#assert1")
		{
			COMMAND.push_back(str);
			int n;
			assert(scanf("%s%d",buf,&n)==2);
			sprintf(_str,"%s %d",buf,n);
			COMMAND.push_back(_str);
			printf("assert(%d)\n",n);
		}
		if(str=="#assert2")
		{
			COMMAND.push_back(str);
			int y,x;
			assert(scanf("%s%d%d",buf,&y,&x)==3);
			sprintf(_str,"%s %d %d",buf,y,x);
			COMMAND.push_back(_str);
			printf("assert(%d,%d)\n",y,x);
		}
		else if(str=="##")
		{
			gets(_str);
			printf("comment: %s\n",_str);
		}
		else if(str=="#")
		{
			int y,x,n;
			scanf("%d%d%d",&y,&x,&n);
			printf(" (%d,%d)=%d\n",y,x,n);
			if(!Valid(y,x,n))
			{
				printf("Invalid\n");
				assert(0);
			}
			GRID[y][x]=n;
		}
		else if(str=="left"||str=="right"||str=="move"||str=="get"||str=="put"||str=="halt")
		{
			COMMAND.push_back(str);
			puts("");
		}
		else if(str=="jump"||str=="border"||str=="pebble")
		{
			COMMAND.push_back(str);
			scanf("%s",_str);
			COMMAND.push_back(_str);
			printf(" %s\n",_str);
		}
		else
		{
			puts("");
			if(!str.empty()&&str[str.size()-1]==':')
			{
				str.pop_back();
				if(LABEL.find(str)!=LABEL.end())
				{
					printf("duplicated label: %s\n",str.c_str());
					assert(0);
				}
				LABEL[str]=(int)COMMAND.size();
			}
			else
			{
				printf("command=%s\n",_str);
				assert(0);
			}
		}
	}
	puts("\n\ncompiled");
	puts("***********************************************");
	int d=0,y=0,x=0;
	static int ds[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
	no_effected=false;
	for(id=0;;)
	{
		static char buf[1000];
		printf("%s(R=%d,C=%d)\n",(d==0?"¡ô":(d==1?"¡÷":(d==2?"¡õ":"¡ö"))),y,x);
		if(id==(int)COMMAND.size())
		{
			puts("reached end");
			assert(0);
			goto terminated;
		}
		printf("%s\n",COMMAND[id].c_str());
		if(COMMAND[id]=="#assert1")
		{
			int a;sscanf(COMMAND[id+1].c_str(),"%s%d",buf,&a);
			if(d!=a)
			{
				printf("%s: d expected to be %d, but it's %d\n",buf,a,d);
				assert(0);
			}
			id+=2;
		}
		else if(COMMAND[id]=="#assert2")
		{
			int a,b;sscanf(COMMAND[id+1].c_str(),"%s%d%d",buf,&a,&b);
			if(y!=a||x!=b)
			{
				printf("%s: (y,x) expected to be (%d,%d), but it's (%d,%d)\n",buf,a,b,y,x);
				assert(0);
			}
			id+=2;
		}
		else if(COMMAND[id]=="left")(d+=3)%=4,++id;
		else if(COMMAND[id]=="right")(d+=1)%=4,++id;
		else if(COMMAND[id]=="move")
		{
			if(Valid(y+ds[d][0],x+ds[d][1]))y+=ds[d][0],x+=ds[d][1];
			else ManageNoEffectCode();
			++id;
		}
		else if(COMMAND[id]=="get")
		{
			if(Valid(y,x,GRID[y][x]-1))GRID[y][x]-=1;
			else ManageNoEffectCode();
			++id;
		}
		else if(COMMAND[id]=="put")
		{
			if(Valid(y,x,GRID[y][x]+1))GRID[y][x]+=1;
			else ManageNoEffectCode();
			++id;
		}
		else if(COMMAND[id]=="halt")
		{
			goto terminated;
		}
		else if(COMMAND[id]=="jump")
		{
			id=Label(COMMAND[id+1]);
		}
		else if(COMMAND[id]=="border")
		{
			if(!Valid(y+ds[d][0],x+ds[d][1]))id=Label(COMMAND[id+1]);
			else id+=2;
		}
		else if(COMMAND[id]=="pebble")
		{
			if(GRID[y][x]>0)id=Label(COMMAND[id+1]);
			else id+=2;
		}
		else
		{
			printf("Unexpected command: %s\n",COMMAND[id].c_str());
			assert(0);
		}
	}
	assert(0);
	terminated:;
	puts("\n\nterminated");
	for(int i=0;i<255;i++)for(int j=0;j<255;j++)if(GRID[i][j]>0)printf("(%d,%d,%d)",i,j,GRID[i][j]);puts("");
	puts("***********************************************");
	if(no_effected)puts("sume commands have no effect!");
	return 0;
}
