#include <iostream>
#include "HashTable.h"
using namespace std;

int main() {
	HashTable* hashTable = new HashTable();
	hashTable->Add("Ã¶¼ö");
	hashTable->Add("¿µÈñ");
	cout << "Ã¶¼ö ÀúÀåµÇ¾ú³ª¿ä?" << hashTable->ContainsValue("Ã¶¼ö") << endl;

	hashTable->Delete();
	return 0;
}