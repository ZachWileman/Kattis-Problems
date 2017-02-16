#include <iostream>
#include <string>
using namespace std;

int main()
{
    string input;
    char currentStateOfSeat;
    int numberOfSeatChanges;

    getline(cin, input);

    for (int i=0; i < 3; i++)
    {
        currentStateOfSeat = input[0];
        numberOfSeatChanges = 0;

        switch(i)
        {
            case 0:
                for (int j = 1; j < input.length(); j++)
                {
                    if (currentStateOfSeat != input[j])
                    {	
                        if (currentStateOfSeat == 'U')
                            numberOfSeatChanges += 2;
                        else
                            numberOfSeatChanges++;
                    }

                    if (j == 1)
                    {
                        if (currentStateOfSeat == 'D' && input[j] == 'D')
                            numberOfSeatChanges++;

                        currentStateOfSeat = 'U';
                    }
                }
                break;

            case 1:
                for (int j = 1; j < input.length(); j++)
                {
                    if (currentStateOfSeat != input[j])
                    {	
                        if (currentStateOfSeat == 'D')
                            numberOfSeatChanges += 2;
                        else
                            numberOfSeatChanges++;
                    }

                    if (j == 1)
                    {
                        if (currentStateOfSeat == 'U' && input[j] == 'U')
                            numberOfSeatChanges++;

                        currentStateOfSeat = 'D';
                    }
                }
                break;

            case 2:
                    for (int j = 1; j < input.length(); j++)
                    {
                        if (currentStateOfSeat != input[j])
                        {
                            numberOfSeatChanges++;
                            currentStateOfSeat = input[j];
                        }
                    }
                    break;
        }

        cout << numberOfSeatChanges << endl;
    }

    return 0;
}