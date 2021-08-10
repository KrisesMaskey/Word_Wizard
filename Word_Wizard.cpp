#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<regex>
#include "Vector.h"
#include "map.h"
#include "Heap.h"
using namespace std;

//Class HashNode
class HashNode
{
	public:
		string key;			//Key-Value pairs to store entry 
		int value;
	public:
		HashNode(){}		//Constructor
		HashNode(string key, int value)
		{
			this->key = key;
			this->value = value;
		}
	friend class HashTable;
};

//Class HashTable
class HashTable
{
	private:
		AVL<HashNode> *buckets;							// Array of lists of type Hash Nodes
		Heap<HashNode> heap = Heap<HashNode>(100);		// Initialization of Heap to sort Data and find max
		int size;					    				// Current Size of HashTable
		int capacity;				    				// Total Capacity of HashTable
		int collisions;									// Total Number of Collisions
		int unique_words;								// Total Number of Unique Words
		int hash_choice;								// Choice of HashFunction
	public:
		HashTable(int capacity);							//Constructor
		unsigned long Poly_hashCode(const string key);		//Polynomial Hash Function
		unsigned long Reverse_Poly(const string key);		//Reverse Polynomial Hash Function
		unsigned long DJB2_hashCode(const string key);		//DJB2 Hash Function
		unsigned long Cyclic_hashCode(const string key);	//Cyclic Shift Hash Function
		unsigned long switch_hashFunc(const string key);	//Function to Switch Hash Funciton
		void set_hashfunc(int& input);						//Function sets Hash Function according to user input
		void insert(const string key, const int value);		//Insert entry
		void heap_insert(Vector<string>& v);				//Insert in heap to sort data
		void find_freq(string key);							//Display Value of entered Key
		int getSize();										//Returns Size of Hashtable
		int getCollisions();								//Returns the number of collisions
		int getUnique();									//Returns the number of unique words
		HashNode find_max();								//Returns the entry with max frequency
		~HashTable();										//Destructor
};
//============================================================

HashTable::HashTable(int capacity)
{
	buckets = new AVL<HashNode>[capacity];			//Create an array of size capacity. Each locaiton of Array is a list/chain
	this->capacity = capacity;						//Set Capacity
	this->size = 0;									//Initialize size to 0
	this->unique_words = 0;							//Initialize unique words to 0
	this->hash_choice = 4;							//Initialize the default hash function to Polynomial Hash Function
	this->collisions = 0;							//Initialize collision to 0
}
//============================================================
unsigned long HashTable::Poly_hashCode(const string key)	//Polynomial Hash Funciton
{	
	unsigned long sum = 0;
	unsigned long a = 769;
	for (int i = 0; i < key.length(); ++i)
	{
		char temp = key.at(i);
		//Horners method for faster computation
		sum = (unsigned long)((sum * a) + (unsigned int)(temp));
	}
	return sum;
}
//============================================================
unsigned long HashTable::Reverse_Poly(const string key)		//Reverse Polynomial Hash Function
{
	unsigned long sum = 0;
	unsigned long a = 769;
	for (int i = key.length() - 1; i > -1; i--)
	{
		char temp = key[i];
		//Horners method for faster computation
		sum = (unsigned long)((sum * a) + (unsigned int)(temp));
	}
	return sum;
}
//============================================================
unsigned long HashTable::Cyclic_hashCode(const string key){	//Cyclic Shift Hash Function
	unsigned int sum = 0;
 	for (int i = 0; i < key.length(); i++) {
    	sum = (sum << 5 | sum>>27); // 5-bit cyclic shift of the running sum
    	sum += (unsigned int)(key.at(i)); // add in next character
  }
  return long(sum);
}
//============================================================
unsigned long HashTable::DJB2_hashCode(const string key){	//DJB2 Hash Function
	unsigned long hash;
    unsigned int c;
    hash = 5381;
    for (auto x: key)	//Iterate through all characters
    {
        c = x;
        hash = ((hash << 5) + hash) + c; //Multiply by 33 and add ASCII calue
    }
    return hash;
}
//============================================================
void HashTable::insert(const string key, const int value)	//Insert Method
{
	//TODO
	HashNode node = HashNode(key, 1);
	int index = switch_hashFunc(key) % capacity;
	size++;	
	
	if(buckets[index].empty()){
		//Increment unique words only if not found in bucket
		unique_words++;
		buckets[index].insert(node);
	}else{
		HashNode temp = buckets[index].search(key);
	    if(temp.key == key){	
	    	//Increment frequency of already present word
	    	buckets[index].increment(key);
	    }else{
	    	//Increment Collision if new word collides with already filled bucket
	    	collisions++;
	    	unique_words++;
	    	buckets[index].insert(node);
		}
 	}
}
//============================================================
void HashTable::find_freq(string key)	//Find frequency method
{
	int index = switch_hashFunc(key) % capacity;
	HashNode test = buckets[index].search(key);
	if(test.value == -1){
		cout<<key<<": "<<0<<endl; return;
	}
	cout<<test.key<<": "<<test.value<<endl;
}
//============================================================
int HashTable::getSize()		//Method to return Size
{
	return this->size;
}
//============================================================
int HashTable::getCollisions()	//Method to return collisions
{
	return this->collisions;
}
//============================================================
int HashTable::getUnique()		//Method to return No. Unique Words
{
	return this->unique_words;
}
//============================================================
HashTable::~HashTable()			//Destructor
{
	delete[] buckets;
}
//============================================================
//Method to switch Hash Function
unsigned long HashTable::switch_hashFunc(string key){	
	switch(hash_choice){
		case 1:
			return Reverse_Poly(key);
			break;
		case 2:
			return DJB2_hashCode(key);
			break;
		case 3:
			return Cyclic_hashCode(key);
			break;
		case 4:
			return Poly_hashCode(key);;
			break;
		default:
			return Poly_hashCode(key);
			break;
	}
}
//=============================================================
//Setter method to set Hash Function according to user input
void HashTable::set_hashfunc(int& input){ 
	hash_choice = input;
}
//=============================================================
//Method to insert entries into a heap and find the max entry
void HashTable::heap_insert(Vector<string>& vec){	
	while(!vec.empty()){
		string s = vec.back();
		int i = switch_hashFunc(s) % capacity;
		HashNode temp = buckets[i].search(s);
		heap.insert(temp);
		vec.pop_back();
	}
}
//=============================================================
//Method to return the entry with the max frequency
HashNode HashTable::find_max(){ 
	return heap.getMax();
}
//=============================================================

//Function to check if entered path exists or not
void enter_Path(string& path){
	ifstream fin;
	bool flag = true;
	while(flag == true){
		cout<<"Welcome to Word Count Wizard!"<<endl;
		cout<<"Please enter the full path of the file: "; getline(cin, path);
		fin.open(path);
		if((!fin)){
			cout<<"File not Found..."<<endl;
		}else{flag = false; fin.close();}
	}
}
//===========================================================================================
//Function to let user choose the hash function 
int choose_Hash(){
	system("clear");
	string hash_func = "";
	while(hash_func != "1" && hash_func != "2" && hash_func != "3" && hash_func != "4"){
		cout<<"Please choose a Hash Function: "<<endl;
		cout<<"1. Reverse Polynomial Hash Function"<<endl;
		cout<<"2. DJB2 Hash Function"<<endl;
		cout<<"3. Cyclic Shift Hash Function"<<endl;
		cout<<"4. Polynomial Hash Function"<<endl;
		cout<<"----- PRESS ENTER TWICE TO REGISTER INPUT-----"<<endl;
		cout<<"> (Enter number): "; getline(cin, hash_func); cin.ignore();//cin>>hash_func;
			if(hash_func == "")
				return 4;

			try{
				int num = stoi(hash_func);
				return num;
				break;
			}catch(exception e){
				cout<<"Please enter a Number"<<endl;
			}
		system("clear");
	}
}
//===========================================================================================
//Function to remove punctuations from a word
void remove_punct(string& word){
  int len = word.size();
  string temp;
  word.erase(word.find_last_not_of(" \n\r\t")+1);
  for (int i = 0; i < len; i++)
    {
        if (ispunct(word[i]))
        {
            word.erase(i--, 1);
            len = word.size();
        }
    }
    for_each(word.begin(), word.end(), [](char & c) {
        c = ::tolower(c);
    });
}
//==============================================================================================
//Function that outputs the list of available commands
void command_list(){
	cout<<"---------------------------------------------------------------------------"<<endl;
	cout<<"\nList of available Commands:"<<endl
		<<"report         : Display Hashing Result"<<endl
		<<"freq <word>    : Display the frequency of the given word"<<endl
		<<"max            : Display the word with maximum frequency"<<endl
		<<"help           : Display list of command"<<endl
		<<"exit           : Exit the program"<<endl;
}
//===============================================================================================

//Main Function
int main(){
	Vector<string> vec;
	HashTable myHashTable(196613);												//Initialize Hash Table
	string path, input, key; int choice, cnt = -1;
	enter_Path(path);															//Ask for Path
	
	//Check .txt extension
	if(path.find(".txt") == string::npos){
		enter_Path(path);
	}

	choice = choose_Hash();														//Ask for choice of Hash Function
	myHashTable.set_hashfunc(choice);											//Set Hash Function
	
	cout<<"Please wait a few moment......"<<endl;
	ifstream fin;
	fin.open(path);
	
	while(fin >> key){															//Insert Entries into the ordered map
		remove_punct(key); 
		bool alpha = !std::regex_match(key, std::regex("^[A-Za-z]+$"));
		if (alpha == false){
			vec.push_back(key);
			myHashTable.insert(key, 1);
		}
	}

	myHashTable.heap_insert(vec);												//Insert entries into the Heap
	HashNode max = myHashTable.find_max();										

	//Display the Report
	cout<<"\nNumber of Collisions: "<<myHashTable.getCollisions()<<endl;
	cout<<"Number of Unique Words: "<<myHashTable.getUnique()<<endl;
	cout<<"Total Word Count: "<<myHashTable.getSize()<<endl;

	//Display available commands
	command_list();
	string user_input;
	string command;
	string parameter;
	cout<<">"; 
	
	//Loop until exit is entered
	do{
		getline(cin, user_input);
		cnt++;
		command = user_input.substr(0,user_input.find(" "));
		parameter = user_input.substr(user_input.find(" ")+1);

		if(command == "max")
			cout<<"Max frequency: "<<max.key<<" = "<<max.value<<endl;
		else if(command == "freq"){
			cout<<"(Key : Value) = ";
			remove_punct(parameter);
			myHashTable.find_freq(parameter); cout<<endl;
		}
		else if(command =="help")
			command_list();
		else if(command == "report"){
			cout<<"\nNumber of Collisions: "<<myHashTable.getCollisions()<<endl;
			cout<<"Number of Unique Words: "<<myHashTable.getUnique()<<endl;
			cout<<"Total Word Count: "<<myHashTable.getSize()<<endl;
		}else if(command == "exit")
			break;
		else if(cnt != 0)
			cout<<"Invalid input!"<<endl;
		cout<<">";
	}while(command != "exit");	
	
	
	return 0;
}