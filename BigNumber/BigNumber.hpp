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

class BigNumber{
  public:
    BigNumber(std::string value = "0");
    BigNumber(int value = 0);
    const BigNumber operator+(const BigNumber&) const;
    BigNumber& operator+=(const BigNumber&);
    const BigNumber operator*(const BigNumber&) const;
    BigNumber& operator*=(const BigNumber&);
    std::vector<int> createVector() const;
    std::string mValue;
};

#endif // BIGNUMBER_HPP

