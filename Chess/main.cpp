#include <iostream>
#include <string>
using namespace std;

const char column[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
const char row[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
const string currentDirection[] = {"nw", "ne", "se", "sw"};
const int MIN_COL_VAL = 65;
const int MAX_COL_VAL = 72;
const int MIN_ROW_VAL = 1;
const int MAX_ROW_VAL = 8;

class linkedList
{
public:
	string location;
	linkedList *next;

	// Constructor
	linkedList(): next(NULL) {}

	// Destructor
	~linkedList() {}
	
	// Append to list
	void append(const string &position)
	{
		linkedList *list = this;
		linkedList *temp = new linkedList;
		
		// Runs down to the last element of the list
		while (list -> next != NULL)
		{
			list = list -> next;
		}

		// Adds new position and tacks on sentinel block
		list -> location = position;
		list -> next = temp;
	}

	void printList()
	{
		linkedList *temp = this;

		while (temp -> next != NULL)
		{
			cout << temp -> location << endl;
			temp = temp -> next;
		}

		temp = NULL;
	}

	void clear()
	{
		linkedList *temp = next;

		while(temp != NULL)
		{
			this -> next = temp -> next;
			delete temp;
			temp = next;
		}

		return;
	}
};

bool validateMovement(const int &currentRow, const int &currentCol);
void findPositions(linkedList *currentList, const int &row, const int &col);
string compareLists(linkedList *lhs_list, linkedList *rhs_list, const string &end);

int main()
{
	linkedList *startingPositions = new linkedList;
	linkedList *endingPositions = new linkedList;

	int num_cases;
	string input;
	char positions[4];
	int characterCounter;
	string startPos, endPos, result;

	cin >> num_cases;
	cin.get();

	for (int i = 0; i < num_cases; i++)
	{
		characterCounter = 0;
		endPos.clear();
		getline(cin, input);

		for (int j = 0; j < input.length(); j++)
		{
			if (!isspace(input[j]))
			{
				positions[characterCounter] = input[j];
				characterCounter++;
			}
		}

		if (positions[0] == positions[2] && positions[1] == positions[3])
			cout << "0 " << positions[0] << " " << positions[1] << endl;
		else
		{
			endPos.push_back(positions[2]);
			endPos.push_back(positions[3]);

			findPositions(startingPositions, int(positions[0]), (int(positions[1])-48));
			findPositions(endingPositions, int(positions[2]), (int(positions[3])-48));

			result = compareLists(startingPositions, endingPositions, endPos);
		
			if (result == endPos)
			{	
				cout << "1 " << positions[0] << " " << positions[1] << " " <<
					positions[2] << " " << positions[3] << endl;
			}
			else if (result == "Impossible")
				cout << "Impossible" << endl;
			else
			{
				cout << "2 " << positions[0] << " " << positions[1] << " " <<
					result[0] << " " << result[1] << " " << positions[2] << " " <<
					positions[3] << endl;
			}
		}

		// De-allocates memory
		startingPositions -> clear();
		endingPositions -> clear();
	}
	
	// De-allocates memory
	delete startingPositions;
	delete endingPositions;

	return 0;
}

void findPositions(linkedList *currentList, const int &col, const int &row)
{
	int currentRow, currentCol;
	string position;
	bool valid;

	// Iterates 4 times to check each direction the bishop can possibly go
	for (int i = 0; i < 4; i++)
	{
		currentRow = row;
		currentCol = col;
		valid = true;

		if (currentDirection[i] == "nw")
		{
			while (valid)
			{
				currentCol--;
				currentRow++;
				position = static_cast<char>(currentCol) + to_string(currentRow);
				valid = validateMovement(currentRow, currentCol);

				if (valid)
					currentList -> append(position);
				else
					valid = false;
			}
		}

		else if (currentDirection[i] == "ne")
		{
			while (valid)
			{
				currentCol++;
				currentRow++;
				position = static_cast<char>(currentCol) + to_string(currentRow);
				valid = validateMovement(currentRow, currentCol);

				if (valid)
					currentList -> append(position);
				else
					valid = false;
			}
		}

		else if (currentDirection[i] == "se")
		{
			while (valid)
			{
				currentCol++;
				currentRow--;
				position = static_cast<char>(currentCol) + to_string(currentRow);
				valid = validateMovement(currentRow, currentCol);

				if (valid)
					currentList -> append(position);
				else
					valid = false;
			}
		}

		else //(currentDirection[i] == "sw")
		{
			while (valid)
			{
				currentCol--;
				currentRow--;
				position = static_cast<char>(currentCol) + to_string(currentRow);
				valid = validateMovement(currentRow, currentCol);

				if (valid)
					currentList -> append(position);
				else
					valid = false;
			}
		}
	}
}

bool validateMovement(const int &currentRow, const int &currentCol)
{
	if (currentCol > MAX_COL_VAL || currentCol < MIN_COL_VAL || currentRow > MAX_ROW_VAL || currentRow < MIN_ROW_VAL)
		return false;
	else
		return true;
}

// Returns match found is there is one, otherwise returns "Impossible"
string compareLists(linkedList *lhs_list, linkedList *rhs_list, const string &end)
{
	linkedList *left_list = lhs_list;
	linkedList *right_list = rhs_list;
	bool match_found = false;
	string temp_location;

	while (left_list -> next != NULL)
	{
		while (right_list -> next != NULL)
		{
			if (left_list -> location == end)
				return end;
			
			// Used in the case that the end position hasn't been matched yet
			if (left_list -> location == right_list -> location)
			{
				temp_location = left_list -> location;
				match_found = true;
			}

			right_list = right_list -> next;
		}

		left_list = left_list -> next;

		// Resets right_list
		right_list = rhs_list;
	}

	if (match_found)
		return temp_location;
	else
		return "Impossible";
}