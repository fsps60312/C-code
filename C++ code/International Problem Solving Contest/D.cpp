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
int main()
{
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
	}
	puts("done");
	return 0;
}
