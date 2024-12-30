#include "P.h"

// �w�]�c�y���
P::P() : code(""), Rate({ {"Normal", 1} }) {
	for (int i = 0; i < 3; i++) {
		Score[i] = 0;
	}
}

// �a�Ѽƪ��c�y���
P::P(string c, int s[3], map<string, int> r) : code(c), Rate(r) {
	for (int i = 0; i < 3; i++) {
		Score[i] = s[i];
	}
}

// ����B��ŭ���
bool P::operator==(const P& other) const {
	return code == other.code;
}

bool P::operator!=(const P& other) const {
	return code != other.code;
}
