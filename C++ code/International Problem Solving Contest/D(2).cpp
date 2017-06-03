#include<cstdio>
#include<cassert>
#include<string>
#include<vector>
using namespace std;
struct Point
{
	int X,Y;
	Point(){}
	Point(const int _X,const int _Y):X(_X),Y(_Y){}
};
vector<string>DESC[12];
string LOCA[12]=
{
	"73 75",
	"174 77",
	"299 74",
	"499 76",
	"75 175",
	"173 180",
	"295 175",
	"501 175",
	"75 274",
	"174 277",
	"297 275",
	"499 276"
};
vector<string>COLOR;
int KASE;
vector<int>ERROR;
void UpdateDESC()
{
	static int cnt[2][6];
	for(int i=0;i<2;i++)for(int j=0;j<6;j++)cnt[i][j]=0;
	if(KASE>=(int)COLOR.size())return;
	for(int i=0;i<12;i++)
	{
		const int d=i/2%2;
		string s=COLOR[KASE].substr(i*9,9);
		DESC[i][0]="";
			 if(s=="255136000")DESC[i][0]+="orange ",++cnt[d][0];
		else if(s=="255000255")DESC[i][0]+="pink ",++cnt[d][1];
		else if(s=="000000255")DESC[i][0]+="blue ",++cnt[d][2];
		else if(s=="255000000")DESC[i][0]+="red ",++cnt[d][3];
		else if(s=="000255000")DESC[i][0]+="green ",++cnt[d][4];
		else if(s=="255255000")DESC[i][0]+="yellow ",++cnt[d][5];
		else assert(0);
		if(d==0)DESC[i][0]+="square";
		else DESC[i][0]+="wide rectangle";
	}
	for(int i=0;i<2;i++)for(int j=0;j<6;j++)if(cnt[i][j]!=1){ERROR.push_back(KASE);break;}
}
//DESC[0]=vector<string>{"red square"};
//DESC[1]=vector<string>{"yellow square"};
//DESC[2]=vector<string>{"red wide rectangle"};
//DESC[3]=vector<string>{"yellow wide rectangle"};
//DESC[4]=vector<string>{"green square"};
//DESC[5]=vector<string>{"orange square"};
//DESC[6]=vector<string>{"green wide rectangle"};
//DESC[7]=vector<string>{"orange wide rectangle"};
//DESC[8]=vector<string>{"blue square"};
//DESC[9]=vector<string>{"pink square"};
//DESC[10]=vector<string>{"blue wide rectangle"};
//DESC[11]=vector<string>{"pink wide rectangle"};
bool Trim(string &s,const string v)
{
	if(s.size()<v.size())return false;
//	printf("%s\n%s\n",s.substr(0,v.size()).c_str(),v.c_str());
	if(s.substr(0,v.size())==v)
	{
		s=s.substr(v.size(),s.size()-v.size());
		return true;
	}
	return false;
}
int GetDescId(string &line)
{
	for(int i=0;i<12;i++)
	{
		for(const string s:DESC[i])if(Trim(line,s))return i;
	}
	return -1;
}
bool Perform(const string _line)
{
	UpdateDESC();return true;
	string line=_line;
	if(Trim(line,"Click on the "))
	{
		if(true)
		{
			const int id=GetDescId(line);
			if(id==-1)return false;
			else if(Trim(line,"."))
			{
				if(line.empty())
				{
					puts(LOCA[id].c_str());
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(Trim(line," and then click on the "))
			{
				const int ie=GetDescId(line);
				if(ie==-1)return false;
				else if(Trim(line,"."))
				{
					if(line.empty())
					{
						puts(LOCA[id].c_str());
						puts(LOCA[ie].c_str());
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}
void ReadColors()
{
	freopen("color.txt","r",stdin);
	for(char *buf=new char[1000000];scanf("%s",buf)==1;)COLOR.push_back(buf);
}
int main()
{
	ReadColors();
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	DESC[0]=vector<string>{"red square"};
	DESC[1]=vector<string>{"yellow square"};
	DESC[2]=vector<string>{"red wide rectangle"};
	DESC[3]=vector<string>{"yellow wide rectangle"};
	DESC[4]=vector<string>{"green square"};
	DESC[5]=vector<string>{"orange square"};
	DESC[6]=vector<string>{"green wide rectangle"};
	DESC[7]=vector<string>{"orange wide rectangle"};
	DESC[8]=vector<string>{"blue square"};
	DESC[9]=vector<string>{"pink square"};
	DESC[10]=vector<string>{"blue wide rectangle"};
	DESC[11]=vector<string>{"pink wide rectangle"};
	puts(LOCA[0].c_str());
	KASE=0;
	for(char *buf=new char[1000000];gets(buf);)
	{
//		puts(buf);
		puts("next");
		if(!Perform(buf))
		{
			puts("Error!");
			puts(buf);
			exit(1);
		}
		KASE++;
	}
	puts("done");
	printf("ERROR=%d\n",(int)ERROR.size());
	for(const int v:ERROR)printf("%d\n",v);
	return 0;
}
