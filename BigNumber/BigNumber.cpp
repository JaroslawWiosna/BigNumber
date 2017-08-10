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

void BigNumber::setmValue(std::string str) {
    mValue = str;
}

std::string BigNumber::getmValue() const{
    return mValue;
}

const BigNumber BigNumber::operator+(const BigNumber& rhs) const{
    BigNumber result = *this;
    result += rhs;
    return result;
}

BigNumber& BigNumber::operator+=(const BigNumber& rhs) {
    auto lhsVec = createVector();
    auto rhsVec = rhs.createVector();
    int carry{};
    int lhsLength = this->getmValue().length();
    int rhsLength = rhs.getmValue().length();
    unsigned int maxLength = (lhsLength >= rhsLength) ? lhsLength : rhsLength;
    while (lhsVec.size() < maxLength) {
        lhsVec.push_back(0);
    }
    while (rhsVec.size() < maxLength) {
        rhsVec.push_back(0);
    }
    std::vector<int> resVec{};
    for (unsigned int i=0; i<maxLength; ++i) {
	int tmp = lhsVec[i] + rhsVec[i];
        resVec.push_back((tmp + carry)%10);
	carry = ((tmp+carry) >= 10) ? 1 : 0;
    }
    if (carry == 1) {
        resVec.push_back(carry);
    }   
    this->setmValue("");
    while (resVec.size() > 0) {
	std::string tmp = std::to_string(resVec.back());
        this->setmValue(this->getmValue() + tmp);
	resVec.pop_back();
    }
    return *this;
}

const BigNumber BigNumber::operator-(const BigNumber& rhs) const{
    BigNumber result = *this;
    result -= rhs;
    return result;
}

BigNumber& BigNumber::operator-=(const BigNumber& rhs) {
    // TODO: implement operator -=
    auto lhsVec = createVector();
    auto rhsVec = rhs.createVector();
    lhsVec[lhsVec.size()-1] -= 1; // TODO: I know there is a better way, but I don't care right know.
    for (unsigned int i=lhsVec.size()-2; i>0; --i) {
        lhsVec[i] += 10;
	lhsVec[i] -= 1;
    }
    lhsVec[0] += 10;

    for (unsigned int i=0; i<lhsVec.size(); ++i) {
        lhsVec[i] -= (i < rhsVec.size()) ? rhsVec[i] : 0;
    }
    int carry{};
    for (unsigned int i=0; i<lhsVec.size(); ++i) {
	lhsVec[i] += carry;
	carry = 0;
        if (lhsVec[i] >= 10) {
	    lhsVec[i] -= 10;
	    carry = 1;
	}
    }
    this->setmValue("");
    // FIXME: remove leading zeros
    while (lhsVec.size() > 0) {
	std::string tmp = std::to_string(lhsVec.back());
        this->setmValue(this->getmValue() + tmp);
	lhsVec.pop_back();
    }
    return *this;
}
const BigNumber BigNumber::operator*(const BigNumber& rhs) const{
    BigNumber result = *this;
    result *= rhs;
    return result;
}

BigNumber& BigNumber::operator*=(const BigNumber& rhs) {
    // check if any has trailing zeros
    auto lhsVec = createVector();
    auto rhsVec = rhs.createVector();
    // TODO: implement trailing zeros

    int lhsInt = std::stoi(this->getmValue());
    int rhsInt = std::stoi(rhs.getmValue());
    int temp;
    if (__builtin_mul_overflow(lhsInt, rhsInt, &temp)) {
        // TODO: implement for overflow
#if 0
        std::cout << "Overflow detected. Overflow handling not supported yet\n";
	//int m{4};
	//BigNumber powerOfTenToM{static_cast<int>(pow(10,m))};
	BigNumber powerOfTenToM{"powerOfTenTo4"};
	/*
	int lhsHigh = *this%(powerOfTenToM);
	int lhsLow = *this/(powerOfTenToM);
	int rhsHigh = rhs%(powerOfTenToM);
	int rhsLow = rhs/(powerOfTenToM);
	int z2 = lhsHigh * rhsHigh;
	int z0 = lhsLow * rhsLow;
	int z1 = (lhsHigh + lhsLow) * (rhsHigh + rhsLow) - z2 - z0;
	*/
	BigNumber lhsHigh{*this%(powerOfTenToM)};
	BigNumber lhsLow{*this/(powerOfTenToM)};
	BigNumber rhsHigh{rhs%(powerOfTenToM)};
	BigNumber rhsLow{rhs/(powerOfTenToM)};
	BigNumber z2 = lhsHigh * rhsHigh;
	BigNumber z0 = lhsLow * rhsLow;
	BigNumber z1 = (lhsHigh + lhsLow) * (rhsHigh + rhsLow) - z2 - z0;
	BigNumber result{(z2 * powerOfTenToM * powerOfTenToM) + (z1 * powerOfTenToM) + z0};
	this->setmValue(result.getmValue());
	return *this;
#endif
    } else {
        this->setmValue(std::to_string(lhsInt * rhsInt));
    }
    return *this;
}

const BigNumber BigNumber::operator/(const BigNumber& rhs) const{
    BigNumber result = *this;
    result *= rhs;
    return result;
}

BigNumber& BigNumber::operator/=(const BigNumber& rhs) {
    // TODO: implement operator /=
    return *this;
}

BigNumber BigNumber::operator%(const BigNumber& rhs) {
    // Big hack - count number of zeros 
    // since we are using operator% only for powerOfTens
    BigNumber result = *this;
    auto numberOfZeros = rhs.getmValue().length() - 1;

    std::string lhsStr = result.getmValue();
    lhsStr.erase(lhsStr.end()-numberOfZeros,lhsStr.end()); // cut trailing zeros
    result.setmValue(lhsStr);
    return result;
}

bool BigNumber::operator==(const BigNumber& rhs) {
    return (this->mValue == rhs.mValue);
}

bool BigNumber::operator>(const BigNumber& rhs) {
    // TODO: implement >
    return false;
}

bool BigNumber::operator<(const BigNumber& rhs) {
    // TODO: implement <
    return false;
}

bool BigNumber::operator>=(const BigNumber& rhs) {
    return !(*this < rhs);
}

bool BigNumber::operator<=(const BigNumber& rhs) {
    return !(*this > rhs);
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

