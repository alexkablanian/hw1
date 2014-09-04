#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){
	// declare ifstream myFile and open file to read in the text
	ifstream myFile;
	myFile.open(argv[1]);

	string fileName = argv[1]; 
	string firstLine;

	//inputting the first line that contains the number of buckets and the number of lines of commands in the .txt
	getline(myFile, firstLine);
	cerr << firstLine << endl;

	//splitting up the first line containing bucket amount and command amounts and entering them into ints
	istringstream iss(firstLine);
	int numBuckets, numCommands;
	iss >> numBuckets;
	iss >> numCommands;

	//dynamically allocate an array of pointers with pointers towards numBuckets amount of int arrays
	int **allMyBuckets = new int* [numBuckets];

	//go through the array of pointers called allMyBuckets and make numBuckets amount of int arrays of variable size 
	for (int i = 1; i < numBuckets+1; i++){
		//cerr << "bucket " << i << endl;
		allMyBuckets[i] = new int[10]; //figure out variable size of each array (default 10 for practice)
		// initialize all to 0 (i think they are default initialized to 0?)
	}

	/*an int array to check if a certain bucket is empty or not. when an empty command is run, that buckets
	location in this array changes from 0 to 1 indicating there is something in the bucket*/
	int *bucketCheck = NULL;
	bucketCheck = new int [numBuckets];

	//setting all buckets initially to empty
	for (int i = 0 ; i < numBuckets; i ++){
		bucketCheck[i] = 0;
	}

	while(!myFile.eof()){
		//get lines and convert the first few operators to formats that we can use in the program
		string lines;
		getline(myFile, lines);
		istringstream iss(lines);
		int buckNUM, itemNUM;
		string commandPrompt;
		iss>> commandPrompt; //command operator (either PUT, OUTPUT<, or EMPTY)
		iss>> buckNUM; //bucket number 
		iss>> itemNUM; //number of terms in the bucket

		if (commandPrompt == "PUT"){
			cout << "PUT " << endl;
			if (bucketCheck[buckNUM] == 1){ //enter argument to check if bucket is empty 
				cout << "Error - bucket " << buckNUM << " is not empty" << endl;
			}
			else{
				for (int i = 0; i< itemNUM; i++){
					string parse4;
					iss>>parse4;
					int placeHolder = atoi (parse4.c_str());
					allMyBuckets[buckNUM][i] = placeHolder;
					bucketCheck[buckNUM] = 1;
				}
			}
		}
		
		// empty function checks if bucket exists. if it exists it will then go through and empty the bucket
		//empty = set all ints to 0? or null? or what?
		else if (commandPrompt == "EMPTY"){
			cout << "EMPTY " <<endl;
			if (buckNUM < 1 || buckNUM > numBuckets){
				cout << "Error - bucket " << buckNUM << " does not exist." <<endl;
			}
			else{
				//enter empty commands here --> run through an array and set all ints to null?
				for(int i =0; i < itemNUM; i++){
					allMyBuckets[buckNUM][i] = 0;
				}
				bucketCheck[buckNUM] = 0;
			}
		}

		else if (commandPrompt=="OUTPUT"){
			cout << "OUTPUT ";
			//cout << "Bucket Number " << buckNUM << endl;
			if (buckNUM < 1 || buckNUM > numBuckets){
				cout << "Error - bucket " << buckNUM << " does not exist" <<endl;
			}
			else if (bucketCheck[buckNUM] == 0){
				cout << "empty" << endl;
			}
			else{
				//output whats in the bucket through a for loop running through the area 
				for(int i=0; i < 4; i++){ //arbitrarily assigning four at the moment
					cout << allMyBuckets[buckNUM][i];
				} 
				cout << endl;
			}
		}

		else{
			cout << "Error, line does not begin with either 'PUT', 'EMPTY', or 'OUTPUT'" << endl;
		}
	}

	//for loop to delete allocated memory for arrays of ints
	/*for (int i = 1; i < numBuckets+1; i++){
		delete [] allMyBuckets[i];
	}
	// delete allocated memory for pointers to buckets
	delete [] allMyBuckets;
	//delete allocated memory for empty bucket checker
	delete [] bucketCheck; */

	myFile.close(); 
	return 0;
}