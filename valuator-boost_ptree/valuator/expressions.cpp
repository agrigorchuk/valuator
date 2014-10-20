//
//  expressions.cpp
//  valuator
//
//  Created by Oleksandr Hryhorchuk on 9/23/14.
//  Copyright (c) 2014 Oleksandr Hryhorchuk. All rights reserved.
//
#include <cmath>
#include <cfenv>
#pragma STDC FENV_ACCESS ON

#include "expressions.h"

int additionExpression::evalExpr() const
{
    int result = 0;
    for (auto currElement = m_values.begin(); currElement < m_values.end(); ++currElement) {
        result += *currElement;
    }
    return result;
}

int substractionExpression::evalExpr() const
{
    return (m_minuend-m_subtrahend);
}

int multiplicationExpression::evalExpr() const
{
    int result = 1;
    for (auto currElement = m_factors.begin(); currElement < m_factors.end(); ++currElement) {
        result *= *currElement;
    }
    return result;
}

int divisionExpression::evalExpr() const
{
    return (m_dividend/m_divisor);
}