#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const int calories_per_gram[] = {9, 4, 4, 4, 7};

int roundIt(double d)
{   
        //double test = 31.5 + 18.5; 
        //cout << floor(test) << endl;
        //cout << "d equals " << d << " and when added with 0.5 equals " << d + 0.5 << ". But when floored equals " << floor(d + 0.5) << endl;
		//cout << "When you floor 50 by adding two numbers you get " << round(test) << endl;
        return int(d + 0.5);
}

int main()
{
	//double test = 31.5;
  	//cout << test << " rounded to the nearest integer equals " << roundIt(test) << endl;
  	//return 0;

	string currentItem;
	bool notDone = true;
	string currentNumber;
	double total_cal = 0;
	double total_fat_cal = 0;
	bool isFat = true;
	int whichNutrient = 0;
	double item_cal = 0;
	double percent = 0;
	char fat_cal_type = ' ';
	double fat_cal_val;
	int dashCount = 0;

	while (notDone)
	{
		isFat = true;
		whichNutrient = item_cal = percent = 0;
		//currentItem.clear();

		getline(cin, currentItem);

		if (currentItem[0] != '-')
		{
			dashCount = 0;

			for(int i = 0; i < currentItem.length(); i++)
			{
				if (!isspace(currentItem[i]))
				{
					if (isdigit(currentItem[i]))
						currentNumber += currentItem[i];
					else
					{
						switch(currentItem[i])
						{
							case 'g':
								item_cal += stoi(currentNumber) * calories_per_gram[whichNutrient];

								if (isFat)
									fat_cal_type = 'g';

								break;
							case 'C':
								item_cal += stoi(currentNumber);

								if (isFat)
									fat_cal_type = 'C';
								
								break;
							case '%':
								percent += stoi(currentNumber);

								if (isFat)
									fat_cal_type = '%';
								
								break; 
						}

						if (isFat)
						{
							fat_cal_val = item_cal;
							//cout << "fat cal val = " << fat_cal_val << endl;
							isFat = false;

							if (fat_cal_type == '%')
								fat_cal_val = percent;
						}

						currentNumber.clear();
						whichNutrient++;
					}
				}
			}

			//cout << "Item Caloric Amount Before = " << item_cal << endl;

			item_cal = ((item_cal / (100 - percent)) * 100);
			total_cal += item_cal;

			//cout << "Item Caloric Amount After = " << item_cal << endl;
			//cout << "Total Caloric Amount = " << total_cal << endl;
			//cout << "Fat Cal Val = " << fat_cal_val << endl;

			switch(fat_cal_type)
			{
				case 'g':
					total_fat_cal += fat_cal_val;
					break;
				case 'C':
					total_fat_cal += fat_cal_val;
					break;
				case '%':
					total_fat_cal += (fat_cal_val / 100) * item_cal;
					break;
			}

			//total_fat_cal = (total_fat_cal);
		}

		else //(currentItem[0] == '-')
		{	
			dashCount++;

			if (dashCount == 2)
				notDone = false;
			else
			{	
				// Used for testing if the user just entered 2 dashes
				if (fat_cal_type != ' ')
				{
					//cout << "total fat calories = " << total_fat_cal << endl;
					//cout << "total calories = " << total_cal << endl;

					// Calculate Calories from Fat percentage
					cout << round((total_fat_cal / total_cal) * 100) << '%' << endl; 

					total_fat_cal = 0;
					total_cal = 0;
				}
			}
		}
	}

	return 0;
 }