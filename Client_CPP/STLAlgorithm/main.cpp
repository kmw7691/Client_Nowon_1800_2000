#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Player {
public:
	string nickName;
	int score;

	Player(string nickName, int score){
		this->nickName = nickName;
		this->score = score;

	bool operator < (Player& player) {
		return this->score < player.score;
	}

	bool operator <= (Player& player) {
		return this->score <= player.score;
	}

	bool operator >= (Player& player) {
		return this->score >= player.score;
	}

	bool operator > (Player& player) {
		return this->score > player.score;
};

int main() {
	int arr[];

	vector<int> vec1;
	for (int i = 9; i >= 0; i--)
		vec1.push_back


	return 0;
}