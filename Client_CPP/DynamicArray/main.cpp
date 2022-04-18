#include <iostream>
#include "DynamicArray.h"
using namespace std;

int main() {

	DynamicArray da;
	da.Add(1);
	da.Add(2);
	
	cout << "1을 찾을수 있나요?" << endl << da.IsExist(1) << endl;

	da.Remove(1);

	da.Delete();

	return 0;
}