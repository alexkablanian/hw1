#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main (int argc, char *argv[]){
	//declare ifstream variable and open file
	ifstream myFile;
	myFile.open(argv[1]); 
	
	//variables for getline and word counter
	string line;
	char space = ' ';

	//read in number at top of text document
	string firstNumber;
	getline(myFile, firstNumber);

	//string to int conversion
	int numLines = atoi(firstNumber.c_str());

	//dynamically allocate an array of size numlines to store # of words per line
	int *reverseOrder = NULL;
	reverseOrder = new int [numLines];
	int lineCount = 0;

	while (!myFile.eof()){
		int wordCount = 0;
		getline(myFile, line); // pull lines from text file

		int stringSize = line.size();
		char lineArrayFormat [80]; 
		
		//converts strings into char arrays and reads in string 
		for (int i = 0; i < stringSize; i++){
			lineArrayFormat[i] = line[i];
		}

		// check for spaces and up the word counter if a space is detected
		for (int i = 0; i < stringSize; i++){
			if (lineArrayFormat[i] == space){
				wordCount ++;
			}
		}

		//enter wordcount into dynamic array
		reverseOrder[lineCount] = wordCount + 1; 
		lineCount++;
	}

	//play word count array in reverse order 
	for (int i = lineCount -1; i >= 0; i --){
		cout << reverseOrder[i] << endl;
	}

	//delete unused space in dynamic array 
	delete [] reverseOrder;
	reverseOrder = NULL;

	//close file
	myFile.close();
	
	return 0;
}