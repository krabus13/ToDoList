#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <algorithm>



using namespace std;

void show_menu()
{
	cout << "[1] Add note." << endl;
	cout << "[2] Show all notes." << endl;
	cout << "[3] Find note." << endl;
	cout << "[4] Remove one note." << endl;
	cout << "[5] Remove all notes." << endl;
	cout << "[6] Exit." << endl;
}

void add_note(string& new_node)
{
	cout << new_node;
	ofstream file("notes.txt", ios::app);
	if (!file.is_open())
	{
		cout << "File is not opened";
		exit(EXIT_FAILURE);

	}
	file << new_node << endl;

	file.close();

	cout <<" Node added!" << endl;
}

void see_all_notes()
{
	ifstream  file("notes.txt");
	if (!file.is_open())
	{
		cout << "File has not opened :(" << endl;
		return;
	}
	string one_note;
	cout << "All notes: " << endl;

	for (int i = 1; !file.eof(); i++)
	{
		getline(file, one_note);
		if (one_note.empty()){
			continue;
		}
		cout << "[" << i << "]" << one_note << endl;
		
	}
	file.close();
}


void find_nodes(string &ff)
{
	ifstream file("notes.txt");
	if (!file.is_open())
	{
		cout << "No notes.Add them!" << endl;
	}
	string str;
	vector<string> v1;
	while (getline(file, str))
	{
		v1.push_back(str);
	}
	int count = 1;
	system("cls");
	auto result = find(v1.begin(), v1.end(), ff);
	if (result==v1.end())
	{
		cout << "Not found :(" << endl;
	}
	else {

		auto res = for_each(v1.begin(), v1.end(), [&](string s)
			{
				if (s == ff)
				{
					cout << "[" << count << "]" << "\t" << ff << endl;
					count++;
				}
			}
		);
	}
	file.close();
}

string *all_notes(int &n_count)
{
	ifstream  file("notes.txt");
	string* all_notes = nullptr;
	string* all_notes_ptr = nullptr;
	if (!file.is_open()) 
	{
		cout << "File has not opened :(" << endl;
		exit(EXIT_FAILURE);
	}
	string one_note;
	int count = 0;
	while (!file.eof())
	{
		getline(file, one_note);
		if (one_note.empty()){
			continue;
		}
		count++;
		all_notes_ptr = new string[count];
		for (int i = 0; i < count - 1; i++)
		{
			all_notes_ptr[i] = all_notes[i];
		}
		all_notes_ptr[count - 1] = one_note;
		delete[] all_notes;
		all_notes = all_notes_ptr;
		all_notes_ptr = nullptr;
	}
	n_count = count;
	file.close();
	return all_notes;
}
void remove_one_node(string *all_notes_arr,int count,int choice) {
	ofstream file("notes.txt");
	if (!file.is_open()){
		cout << "File is not opened!" << endl;
		exit(EXIT_FAILURE);
	}
	for (int  i = 0; i < count ; i++){
		if (i==choice-1){
			continue;
		}
		file << all_notes_arr[i] << endl;
	}
	file.close();
}
void remove_all_notes()
{ 
	fstream file("notes.txt", ios::out | ios::trunc);
	if (!file.is_open()) {
		cout << "File is not opened!" << endl;
		exit(EXIT_FAILURE);
	}
	file.close();
}




enum CHOISE
{
	ADD_NOTE = 1, SEE_ALL_NOTES, FIND_ONE_NOTE, REMOVE_ONE_NOTE, REMOVE_ALL_NOTES
};

int main()
{
	while (true)
	{
		show_menu();
		cout << "Your choice:" << endl;
		int choice = 0;
		cin >> choice;
		if (choice == ADD_NOTE){
			system("cls");
			
			string new_note;
			getline(cin, new_note);
			cout << "Note to add";
			getline(cin, new_note);
			add_note(new_note);

			system("pause");
		}
		else if (choice == SEE_ALL_NOTES) {
			system("cls");
			
			see_all_notes();

			system("pause");
		}
		else if (choice == FIND_ONE_NOTE) {
			system("cls");
			string ff;
			cout << "Find nodes: " << endl;
			cin >> ff;
			find_nodes(ff);
			system("pause");
		}
		else if (choice == REMOVE_ONE_NOTE) {
			system("cls");
			int count = 0;
			string * all_notes_arr= all_notes(count);
			cout << "All notes" << endl;
			for (int i = 0; i < count; i++){
				cout << "[" << i + 1 << "]" << all_notes_arr[i] << endl;
			}
			cout << "Select a note to delete" << endl;
			int choice = 0;
			cin >> choice;
			remove_one_node(all_notes_arr,count,choice);
			cout << "Your note removed" << endl;
			delete[] all_notes_arr;
			system("pause");
		}
		else if (choice == REMOVE_ALL_NOTES) {
			system("cls");
			remove_all_notes();
			cout << "All notes removed!:)" << endl;
			system("pause");
		}
		else
			break;


	}

	return 0;
}