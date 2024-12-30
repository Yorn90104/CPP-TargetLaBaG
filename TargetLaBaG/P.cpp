#include "P.h"

// 箇砞篶硑ㄧ计
P::P() : code(""), Rate({ {"Normal", 1} }) {
	for (int i = 0; i < 3; i++) {
		Score[i] = 0;
	}
}

// 盿把计篶硑ㄧ计
P::P(string c, int s[3], map<string, int> r) : code(c), Rate(r) {
	for (int i = 0; i < 3; i++) {
		Score[i] = s[i];
	}
}

// ゑ耕笲衡才更
bool P::operator==(const P& other) const {
	return code == other.code;
}

bool P::operator!=(const P& other) const {
	return code != other.code;
}
