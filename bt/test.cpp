#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

struct point {

	int x;
	int y;
};

class Square {

public:
	point topLeft;
	int side;

public:

	Square(point _topLeft, int _side) {
		topLeft = _topLeft;
		side = _side;
	}

	void changeSquare(point _topLeft, int _side) {

		topLeft = _topLeft;
		side = _side;
	}

	void makeSquareArr(int** squareArr) {

		for (int i = topLeft.x; i < topLeft.x + side; i++) {
			for (int j = topLeft.y; j < topLeft.y + side; j++) {

				squareArr[i][j] = 1;
			}
		}
	}

	void deleteSquareArr(int** squareArr) {

		for (int i = topLeft.x; i < topLeft.x + side; i++) {
			for (int j = topLeft.y; j < topLeft.y + side; j++) {

				squareArr[i][j] = 0;
			}
		}
	};

	friend void print(vector <Square> sq, int coeff);
};

void print(vector <Square> sq, int coeff) {

	cout << sq.size() << endl;
	for (unsigned int i = 0; i < sq.size(); i++) {

		cout << sq[i].topLeft.x * coeff << ' ' << sq[i].topLeft.y * coeff << ' ' << sq[i].side * coeff << endl;
	}
}

class mainSquare : public Square {

public:
	int min;
	int count;
	int** squareArr;
	vector <Square> sq;
	vector <Square> minSq;

public:

	mainSquare(point _topLeft, int _side) : Square(_topLeft, _side) {

		min = side * side;
	}

	void makeArr() {

		squareArr = new int *[side];
		for (int i = 0; i < side; i++) {
			squareArr[i] = new int[side];
			for (int j = 0; j < side; j++)
				squareArr[i][j] = 0;
		}
	}

	bool trySquare(int size) {

		if (topLeft.x + size > side || topLeft.y + size > side)
			return false;

		for (int i = topLeft.x; i < topLeft.x + size; i++) {
			for (int j = topLeft.y; j < topLeft.y + size; j++)

				if (squareArr[i][j] == 1)
					return false;
		}

		return true;
	}

	point findTopLeft() {

		for (int j = side / 2; j < side; j++) {
			for (int i = side / 2; i < side; i++)
				if (squareArr[i][j] == 0)
					return { i,j };
		}
		return { side,side };
	}
	
	void backtracking() {

		if (count >= min) {

			return;
		}

		if (topLeft.x == side && topLeft.y == side) {

			if (count < min) {

				min = count;
				minSq.clear();
				minSq = sq;
			}
			return;
		}

		for (int size = side / 2; size > 0; size--) {

			if (trySquare(size)) {

				count++;
				Square s(topLeft, size);
				sq.push_back(s);
				sq.back().makeSquareArr(squareArr);
				topLeft = findTopLeft();

					backtracking();

				count--;
				sq.back().deleteSquareArr(squareArr);
				sq.pop_back();
				topLeft = findTopLeft();
			}
		}
	}
};

int main() {

	int _side, coeff = 1;
	cin >> _side;
	mainSquare mS({ 0,0 }, _side);
	Square s({ 0,0 }, 0);

	if (mS.side < 2 || mS.side > 40) {

		return 0;
	}

	if (!(mS.side % 2)) {

		mS.makeArr();

		s.changeSquare({ 0,0 }, mS.side / 2);
		mS.sq.push_back(s);
		mS.sq.back().makeSquareArr(mS.squareArr);
		s.changeSquare({ mS.side / 2,0 }, mS.side / 2);
		mS.sq.push_back(s);
		mS.sq.back().makeSquareArr(mS.squareArr);
		s.changeSquare({ 0,mS.side / 2 }, mS.side / 2);
		mS.sq.push_back(s);
		mS.sq.back().makeSquareArr(mS.squareArr);
		s.changeSquare({ mS.side / 2,mS.side / 2 }, mS.side / 2);
		mS.sq.push_back(s);
		mS.sq.back().makeSquareArr(mS.squareArr);

		print(mS.sq, coeff);
		return 0;
	}

	if (!(mS.side % 3)) {

		coeff = mS.side / 3;
		mS.side = 3;
	}
	else if (!(mS.side % 5)) {

		coeff = mS.side / 5;
		mS.side = 5;
	}

	mS.makeArr();

	mS.count = 3;

	s.changeSquare(mS.topLeft, (mS.side + 1) / 2);
	mS.sq.push_back(s);
	mS.sq.back().makeSquareArr(mS.squareArr);
	mS.topLeft = { (mS.side + 1) / 2, 0 };

	s.changeSquare(mS.topLeft, mS.side / 2);
	mS.sq.push_back(s);
	mS.sq.back().makeSquareArr(mS.squareArr);
	mS.topLeft = { 0, (mS.side + 1) / 2 };

	s.changeSquare(mS.topLeft, mS.side / 2);
	mS.sq.push_back(s);
	mS.sq.back().makeSquareArr(mS.squareArr);
	mS.topLeft = { (mS.side + 1) / 2, mS.side / 2 };

	mS.backtracking();

	print(mS.minSq, coeff);
	return 0;
}
