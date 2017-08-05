/**
 * \class BigNumber
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "BigNumber.hpp"

BigNumber::BigNumber(std::string value) {
    mValue = value;
}

BigNumber::BigNumber(int value) {
    mValue = std::to_string(value);
}

const BigNumber BigNumber::operator+(const BigNumber& rhs) const{
    BigNumber result = *this;
    result += rhs;
    return result;
}

BigNumber& BigNumber::operator+=(const BigNumber& rhs) {
    auto lhsVec = createVector();
    const auto rhsVec = rhs.createVector();
    int carry{};
    int lhsLength = this->mValue.length();
//    int rhsLength = rhs.mValue.length();
    std::vector<int> resVec{};
    for (int i=0; i<lhsLength; ++i) {
	int tmp = lhsVec[i] + rhsVec[i];
        resVec.push_back(tmp%10 + carry);
	/*
	if (tmp >= 10) {
            carry = 1;
        } else {
            carry = 0;
	}
	*/
	carry = (tmp >= 10) ? 1 : 0;
    }
    if (carry == 1) {
        resVec.push_back(carry);
    }   
    for (const auto& i : resVec) {
        std::cout << i << ", ";
    }
    this->mValue = "";
    while (resVec.size() > 0) {
	std::string tmp = std::to_string(resVec.back());
        this->mValue += tmp;
	resVec.pop_back();
    }
    return *this;
}

std::vector<int> BigNumber::createVector() const {
    int stringLength = mValue.length();
    std::vector<int> vec{};
    vec.reserve(stringLength);

    for (int i = stringLength-1; i>=0; --i) {
	int tmp = mValue.at(i) - '0';
        vec.push_back(tmp);
    }
    return vec;
}
