/**
 * \class BigNumber
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#ifndef BIGNUMBER_HPP
#define BIGNUMBER_HPP

#include <iostream>
#include <list>
#include <cfloat> // FLT_MIN
#include <cmath> // abs
#include <algorithm>
#include <vector>
#include <string>
//#include <memory>
#include <utility>
#include <type_traits>

class BigNumber{
  public:
    explicit BigNumber() : mValue{"0"} {
        
    }

    template<typename T>
    explicit constexpr BigNumber(T&& value)
    requires (std::is_constructible<std::string, T>::value) : mValue{std::forward<T>(value)} {
        // check if this is power of ten
        std::string powOfTenTo = "powerOfTenTo"; // prefix
        if (mValue.find(powOfTenTo) != std::string::npos) {
	    std::string str = mValue;
            str.erase(str.begin(),str.begin()+powOfTenTo.length()); // cut prefix
	    mValue = "1";
	    std::size_t numberOfZeros = std::stoi(str);
	    for (std::size_t i=0; i<numberOfZeros; ++i) {
                mValue += "0";
	    }
        }
    }

    template<typename T>
    explicit constexpr BigNumber(const T value)
    requires (std::is_arithmetic<T>::value) : mValue{std::to_string(value)} {
        
    }

    BigNumber& operator=(const BigNumber &rhs) {
        if (this == &rhs) {
            return *this;
	}
        mValue = rhs.mValue;
	return *this;
    }

    BigNumber(const BigNumber& value) : mValue{value.mValue} {
    }

    BigNumber(BigNumber&& value) : mValue{std::move(value.mValue)} {
    }

    ~BigNumber() {
        mValue = "0"; //FIXME: Is it really needed?
    }

    void setmValue(std::string str);
    std::string getmValue() const;
    const BigNumber operator+(const BigNumber&) const;
    BigNumber& operator+=(const BigNumber&);
    const BigNumber operator-(const BigNumber&) const;
    BigNumber& operator-=(const BigNumber&);
    const BigNumber operator*(const BigNumber&) const;
    BigNumber& operator*=(const BigNumber&);
    const BigNumber operator/(const BigNumber&) const;
    BigNumber& operator/=(const BigNumber&);
    BigNumber operator%(const BigNumber&);
    bool operator==(const BigNumber&);
    bool operator>(const BigNumber&);
    bool operator<(const BigNumber&);
    bool operator>=(const BigNumber&);
    bool operator<=(const BigNumber&);
    std::vector<int> createVector() const;
  private:
    std::string mValue;
};

#endif // BIGNUMBER_HPP

