#include "Header.h"
//using namespace std;

void selectionSort(MyString s[], int size, bool ascending) {

	MyString minString;
	int minIndex;

	for (int start = 0; start < (size - 1); start++) {

		minIndex = start;
		minString = s[start];

		for (int index = start + 1; index < size; index++) {
			if (ascending) {
				if (s[index] < minString) {

					minString = s[index];
					minIndex = index;

				}
			}
			else {
				if (s[index] > minString) {
					minString = s[index];
					minIndex = index;
				}
			}
		}

		swap(s[minIndex], s[start]);

	}
}

int linearSearch(MyString s[], MyString key, int size) {
	for (int i = 0; i < size; i++) {
		if (s[i] == key)
			return i;
	}
	return -1;
}


int main() {
	
	const int NTERMS = 9000;
	const int NWORDS = 5;

	string ifileName, ofileName;
	
	ifstream fin;
	ofstream fout;

	MyString txt[NTERMS];
	MyString word[NWORDS];

	// int size = 0;
	int n;
	
	cout << "Input data file name: ";
	cin >> ifileName;
	cout << "Number of adjacent words [1-5]: ";
	cin >> n;
	cout << "Output word-frequency file name: ";
	cin >> ofileName;
	fout.open(ofileName);
	int x = 0;
	int y = 0;
	int index;

	fin.open(ifileName); //create the term lookup and define its size, basically how many words you want to find the frequency of
	while ((!fin.eof()) && (y < (n - 1))) {
		
		fin >> word[y];
		y += 1;
	}
	//tried to account for special characters with no luck :(
	while (!fin.eof()) { 

		MyString key;
		fin >> word[y];
		
		for (int x = 0; x < n; x++)
			key = key + word[x];
		key.ToUpper();
		
		index = linearSearch(txt, key, x); //return the index if found creates it in txt
		if (index < 0) {
			txt[x] = key;
			x += 1;
		}
		else
			txt[index]++;

		for (int i = 1; i < n; i++) { //go to the next word, ie "coronavirus live" would be "live updates" now into arr word
			
			word[i - 1] = word[i];

		}
	}
	fin.close();
	selectionSort(txt, x, false); //sort the txt array before printing it out
	for (int i = 0; i < x; i++) {

		fout << txt[i] << endl;
	//	word[y] = word[y + 1];

	}
	fout.close();
	return 0;
}