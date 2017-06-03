#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
struct teachertype
{
	int salary;
	vector<int> subject;
};
int power[9]={1,3,9,27,81,243,729,729*3,729*9};
int state[729*9];
int tmp[9],s,m,n;
int initialcost;
char char1[1000];
void addtotmp(teachertype a)
{
	for(int i=0;i<a.subject.size();i++)
	{
		int j=a.subject[i];
		//printf(" %d",j);
		if(tmp[j]<2) tmp[j]++;
	}
	//printf("\n");
}
int translatetmp()
{
	int ans=0;
	for(int i=1;i<=s;i++)
	{
		ans+=tmp[i]*power[i-1];
	}
	return ans;
}
int merge(int a,teachertype b)
{
	for(int i=1;i<=s;i++)
	{
		tmp[i]=a%3;
		a/=3;
	}
	addtotmp(b);
	return translatetmp();
}
bool isnumber(char a)
{
	return a>='0'&&a<='9';
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&s,&m,&n)==3)
	{
		gets(char1);
		if(s==0&&m==0&&n==0) break;
		initialcost=0;
		for(int i=0;i<power[s];i++) state[i]=1100000000;
		for(int i=1;i<=s;i++) tmp[i]=0;
		for(int i=0;i<m;i++)
		{
			teachertype j;
			int k;
			char c;
			gets(char1);
			int inde;
			for(inde=0;char1[inde];inde++)
			{
				if(isnumber(char1[inde]))
				{
					sscanf(char1+inde,"%d",&j.salary);
					while(isnumber(char1[++inde]));
					inde--;
					break;
				}
			}
			for(inde++;char1[inde];inde++)
			{
				if(isnumber(char1[inde]))
				{
					sscanf(char1+inde,"%d",&k);
					while(isnumber(char1[++inde]));
					inde--;
					j.subject.push_back(k);
				}
			}
			initialcost+=j.salary;
			addtotmp(j);
			//printf("%d\n",i);
		}
		state[translatetmp()]=initialcost;
		//printf("initialcost=%d\n",initialcost);
		for(int i=0;i<n;i++)
		{
			teachertype j;
			int k;
			char c;
			gets(char1);
			int inde;
			for(inde=0;char1[inde];inde++)
			{
				if(isnumber(char1[inde]))
				{
					sscanf(char1+inde,"%d",&j.salary);
					while(isnumber(char1[++inde]));
					inde--;
					break;
				}
			}
			for(inde++;char1[inde];inde++)
			{
				if(isnumber(char1[inde]))
				{
					sscanf(char1+inde,"%d",&k);
					while(isnumber(char1[++inde]));
					inde--;
					j.subject.push_back(k);
				}
			}
			for(int o=power[s]-1;o>=0;o--)
			{
				int l=merge(o,j);
				if(o!=l)
				{
					if(state[o]+j.salary<state[l])
					{
						state[l]=state[o]+j.salary;
						//printf(" %d\n",state[l]);
					}
				}
			}
			//printf("%d\n",i);
		}
		printf("%d\n",state[power[s]-1]);
	}
	return 0;
}
