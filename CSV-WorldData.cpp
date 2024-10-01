#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ctype.h>
using namespace std;
struct COUNTRY
{
	char     Region[64];
	string 	 subRegion;
	char     country_code[16];
	float    p2000_2005;
	bool 	 isCountry;
};
void sort2000(COUNTRY* s[], int r);
int main()
{
	ifstream infile;
	COUNTRY conArr[300];
	COUNTRY* co[300];
	char temp[256];
	int c = 0;
	int tstnum = 0;
	string sub = "";
	infile.open("WPP2015_MORT_F07_1_LIFE_EXPECTANCY_0_BOTH_SEXES.csv", ifstream::in);
	if(infile.is_open())
		{
			//cout << "infile open";
			while(infile.good())	
			{
				infile.getline(temp, 256, ',');
				if(!isdigit(temp[0]))
				{
					infile.getline(temp, 256, '\n');
					continue;
				}
				else
				{
					char cnum[16];
					for(int j = 0; j < 16; j++)
					{
						if(j == 1)
						{
							infile.getline(temp, 256, '"');
							infile.getline(conArr[c].Region, 256, '"');
							infile.getline(temp, 256, ',');
						}
						else if(j == 3)
						{
							infile.getline(conArr[c].country_code, 256, ',');
							if(atoi(conArr[c].country_code) > 900)
							{
								sub = conArr[c].Region;
							}
							if(atoi(conArr[c].country_code) < 900 && atoi(conArr[c].country_code) != 158)
							{
								conArr[c].isCountry = true;
							}
							else 
							{
								conArr[c].isCountry = false;
							}
						}
						else if(j == 14)
						{
							infile.getline(cnum, 256, ',');
							conArr[c].p2000_2005 = atof(cnum);
						}
						else if(j < 14)
						{
							infile.getline(temp, 256, ',');
						}
						else
						{
							infile.getline(temp, 256, '\n');
							continue;
						}
					}
					conArr[c].subRegion = sub;
					c++;
				}
			}
			infile.close();
		}
		int r = 0;
		for(int y = 0; y < c; y++)
		{
			if(conArr[y].isCountry)
			{
			co[r] = &conArr[y];
			r++;
			}
		}
			//cout << tstnum << "\n";
			//cout << r;
		sort2000(co, r);
		ofstream file("p2000_2005.csv");
		for(int x = 0; x < r; x++){
		if(co[x] ->isCountry)
			file << co[x] -> Region << ", " << co[x] -> subRegion << ", " << co[x] -> p2000_2005 << "\n";
		}
		   //for(int k = 0; k< 100; k++)
	       // cout << conArr[k].Region << " ";
	return 0;
}
void sort2000(COUNTRY* s[], int r)
{
	COUNTRY* t;
	for (int i=0; i < r - 1; i++)
	{
	for (int j=i; j < r; j++)
		{
		if (s[i]->p2000_2005 < s[j]->p2000_2005)
		{
			//swap pointer to record i with pointer to record j;
			t = s[i];
			s[i] = s[j];
			s[j] = t;
	    }
		}
	}
}