//
//  expressions.h
//  valuator
//
//  Created by Oleksandr Hryhorchuk on 9/23/14.
//  Copyright (c) 2014 Oleksandr Hryhorchuk. All rights reserved.
//

#ifndef __valuator__expressions__
#define __valuator__expressions__

#include <iostream>
#include <vector>

enum ExpressionType
{
    EXPR_UNKNOWN        = -1,
    EXPR_ADDITION       =  0,
    EXPR_SUBSTRACTION   =  1,
    EXPR_MULTIPLICATION =  2,
    EXPR_DIVISION       =  3
};


class AbstractExpression
{
public:
    AbstractExpression(ExpressionType aType) : m_exprType(aType){}
    virtual ~AbstractExpression() {}
    
    // Evaluates expression (must be overrided by child)
    virtual int  evalExpr() const = 0;

    // Helper methods to make life easier later
    inline void setExprType( ExpressionType aType )
    { m_exprType = aType; }
    
    inline ExpressionType getExprType() const
    { return m_exprType; }
    
    inline void setExprId(int anId)
    { m_id = anId; }
    
    inline int getExprId() const
    { return m_id; }
    
protected:
    ExpressionType m_exprType;
    int m_id;
};

class additionExpression : public AbstractExpression
{
public:
    additionExpression() : AbstractExpression(EXPR_ADDITION)
    { m_values.clear(); }
    
    virtual int evalExpr() const;
    void addVal(int aVal) { m_values.push_back(aVal); }
    
protected:
    std::vector<int> m_values;
};

class substractionExpression : public AbstractExpression
{
public:
    substractionExpression() : AbstractExpression(EXPR_SUBSTRACTION) {}
    virtual int  evalExpr() const;
    
    void setMinuend( int aMinuend ) { m_minuend = aMinuend; }
    void setSubtrahend( int aSubtrahend ) { m_subtrahend = aSubtrahend; }
    
protected:
    int m_minuend;
    int m_subtrahend;
};

class multiplicationExpression : public AbstractExpression
{
public:
    multiplicationExpression() : AbstractExpression(EXPR_MULTIPLICATION)
    { m_factors.clear(); }

    virtual int evalExpr() const;
    void addVal(int aVal) { m_factors.push_back(aVal); }
    
protected:
    std::vector<int> m_factors;
};

class divisionExpression : public AbstractExpression
{
public:
    divisionExpression() : AbstractExpression(EXPR_DIVISION) {}
    
    virtual int evalExpr() const;
    
    void setDividend( int aDividend ) { m_dividend = aDividend; }
    void setDivisor( int aDivisor ) { m_divisor = aDivisor; }
    
protected:
    int m_dividend;
    int m_divisor;
};

#endif /* defined(__valuator__expressions__) */
