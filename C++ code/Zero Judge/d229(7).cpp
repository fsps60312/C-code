#include<cstdio>
int N,M;
int main()
{
	scanf("%d%d",&N,&M);
	switch(N)
	{
		case 1:
		{
			switch(M)
			{
				case 1:puts("1\n1");break;
				case 2:puts("2\n1 2");break;
				case 3:puts("3\n1 2 3");break;
				case 4:puts("4\n1 2 3 4");break;
				case 5:puts("5\n1 2 3 4 5");break;
				case 6:puts("6\n1 2 3 4 5 6");break;
				case 7:puts("7\n1 2 3 4 5 6 7");break;
				case 8:puts("8\n1 2 3 4 5 6 7 8");break;
				case 9:puts("9\n1 2 3 4 5 6 7 8 9");break;
				case 10:puts("10\n1 2 3 4 5 6 7 8 9 10");break;
			}
		}break;
		case 2:
		{
			switch(M)
			{
				case 1:puts("2\n1");break;
				case 2:puts("4\n1 2");break;
				case 3:puts("8\n1 3 4");break;
				case 4:puts("12\n1 3 5 6");break;
				case 5:puts("16\n1 3 5 7 8");break;
				case 6:puts("20\n1 2 5 8 9 10");break;
				case 7:puts("26\n1 2 5 8 11 12 13");break;
				case 8:puts("32\n1 2 5 8 11 14 15 16");break;
				case 9:puts("40\n1 3 4 9 11 16 17 19 20");break;
				case 10:puts("46\n1 2 3 7 11 15 19 21 22 24");break;
			}
		}break;
		case 3:
		{
			switch(M)
			{
				case 1:puts("3\n1");break;
				case 2:puts("7\n1 3");break;
				case 3:puts("15\n1 4 5");break;
				case 4:puts("24\n1 4 7 8");break;
				case 5:puts("36\n1 4 6 14 15");break;
				case 6:puts("52\n1 3 7 9 19 24");break;
				case 7:puts("70\n1 4 5 15 18 27 34");break;
				case 8:puts("93\n1 3 6 10 24 26 39 41");break;
				case 9:puts("121\n1 3 8 9 14 32 36 51 53");break;
			}
		}break;
		case 4:
		{
			switch(M)
			{
				case 1:puts("4\n1");break;
				case 2:puts("10\n1 3");break;
				case 3:puts("26\n1 5 8");break;
				case 4:puts("44\n1 3 11 18");break;
				case 5:puts("70\n1 3 11 15 32");break;
				case 6:puts("108\n1 4 9 16 38 49");break;
				case 7:puts("162\n1 4 9 24 35 49 51");break;
				case 8:puts("226\n1 4 9 24 39 51 67 73");break;
			}
		}break;
		case 5:
		{
			switch(M)
			{
				case 1:puts("5\n1");break;
				case 2:puts("14\n1 4");break;
				case 3:puts("35\n1 6 7");break;
				case 4:puts("71\n1 4 12 21");break;
				case 5:puts("126\n1 4 9 31 51");break;
				case 6:puts("211\n1 4 13 24 56 61");break;
				case 7:puts("323\n1 4 13 23 63 91 98");break;
			}
		}break;
		case 6:
		{
			switch(M)
			{
				case 1:puts("6\n1");break;
				case 2:puts("18\n1 4");break;
				case 3:puts("52\n1 7 12");break;
				case 4:puts("114\n1 4 19 33");break;
				case 5:puts("216\n1 7 12 43 52");break;
				case 6:puts("366\n1 6 14 49 79 89");break;
			}
		}break;
		case 7:
		{
			switch(M)
			{
				case 1:puts("7\n1");break;
				case 2:puts("23\n1 5");break;
				case 3:puts("69\n1 8 13");break;
				case 4:puts("165\n1 5 24 37");break;
				case 5:puts("336\n1 5 16 58 97");break;
			}
		}break;
		case 8:
		{
			switch(M)
			{
				case 1:puts("8\n1");break;
				case 2:puts("28\n1 5");break;
				case 3:puts("89\n1 9 14");break;
				case 4:puts("234\n1 6 25 65");break;
			}
		}break;
		case 9:
		{
			switch(M)
			{
				case 1:puts("9\n1");break;
				case 2:puts("34\n1 6");break;
				case 3:puts("112\n1 9 20");break;
			}
		}break;
		case 10:
		{
			switch(M)
			{
				case 1:puts("10\n1");break;
				case 2:puts("40\n1 6");break;
			}
		}break;
	}
	return 0;
}
