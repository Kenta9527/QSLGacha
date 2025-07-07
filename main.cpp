#include <iostream>
#include <random>
#include <string>
#include <vector>

struct QSLCard {
	int star;
	bool isUP;
	std::string name;
};

class QSLGacha {
private:
	std::mt19937 rng;
	int pullCount4Star;
	int pullCount5Star;
	bool guaranteeUP4Star;
	bool guaranteeUP5Star;

	double getRandom() {
		std::uniform_real_distribution<double> dist(0.0, 1.0);
		return dist(rng);
	}

	QSLCard pullOne() {
		QSLCard card;
		double rand = getRandom();

		if (pullCount5Star >= 20 || rand < 0.05) {
			card.star = 5;
			pullCount5Star = 0;

			if (guaranteeUP5Star || getRandom() < 0.5) {
				card.isUP = true;
				guaranteeUP5Star = false;
			}
			else {
				card.isUP = false;
				guaranteeUP5Star = true;
			}
			card.name = card.isUP ? "5-Star UP QSL" : "5-Star Normal QSL";
		}
		else if (pullCount4Star >= 10 || rand < 0.15) {
			card.star = 4;
			pullCount4Star = 0;

		if (guaranteeUP4Star || getRandom() < 0.5) {
			card.isUP = true;
			guaranteeUP4Star = false;
		}
		else {
			card.isUP = false;
			guaranteeUP4Star = true;
		}
		card.name = card.isUP ? "4-Star UP QSL" : "4-Star Normal QSL";
	}
		else {
	card.star = 3;
	card.isUP = false;
	card.name = "3-Star QSL";
		}
		pullCount4Star++;
		pullCount5Star++;
		return card;
	}

public:
	QSLGacha() : pullCount4Star(0), pullCount5Star(0), guaranteeUP4Star(false), guaranteeUP5Star(false) {
		std::random_device rd;
		rng.seed(rd());
	}

	void pull(int n){
		std::vector <QSLCard> results;
		for (int i = 0; i < n; ++i) {
			results.push_back(pullOne());
		}
		
		std::cout << "Pull Results (" << n << " pulls):\n";
		for (const auto& card : results) {
			std::cout << card.name << "(Star: " << card.star << ",UP:" << (card.isUP ? "Yes" : "No") << ")\n";
		}
	}
};

int main() {
	QSLGacha gacha;
	int pulls;

	std::cout << "Enter number of pulls: ";
	std::cin >> pulls;

	if (pulls <= 0) {
		std::cout << "Please enter a positive number of pulls.\n";
		return 1;
	}

	gacha.pull(pulls);
	return 0;
}