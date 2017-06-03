#include<cstdio>
#include<map>
#include<cassert>
using namespace std;
map<int,bool>DP;
int GetMaxDay(const int y,const int m)
{
	switch(m)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:return 31;
		case 4:
		case 6:
		case 9:
		case 11:return 30;
		default:
		{
			assert(m==2);
			if(y%400==0)return 29;
			if(y%100==0)return 28;
			if(y%4==0)return 29;
			return 28;
		}
	}
}
bool Win(const int year,const int month,const int day)
{
//	printf("(%d,%d,%d)\n",year,month,day);
	assert(month>=1&&month<=12&&day>=1&&day<=GetMaxDay(year,month));
	auto it=DP.find(year*10000+month*100+day);
	if(it!=DP.end())return it->second;
	bool &dp=DP[year*10000+month*100+day];
	if(year>2001)return dp=true;
	else if(year==2001)
	{
		if(month>11)return dp=true;
		else if(month==11)
		{
			if(day>4)return dp=true;
			else if(day==4)return dp=false;
		}
	}
	int y=year,m=month+1;
	if(m>12)m=1,y++;
	const int maxday=GetMaxDay(year,month);
	if(day<maxday){if(!Win(year,month,day+1))return dp=true;}
	else
	{
		assert(day==maxday);
		if(!Win(y,m,1))return dp=true;
	}
	if(day<=GetMaxDay(y,m)&&!Win(y,m,day))return dp=true;
	return dp=false;
}
int main()
{
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		static int y,m,d;scanf("%d%d%d",&y,&m,&d);
		puts(Win(y,m,d)?"YES":"NO");
	}
	return 0;
}
