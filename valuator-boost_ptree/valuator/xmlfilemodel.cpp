//
//  xmlfilemodel.cpp
//  valuator
//
//  Created by Oleksandr Hryhorchuk on 9/23/14.
//  Copyright (c) 2014 Oleksandr Hryhorchuk. All rights reserved.
//
#include <iostream>

#include "xmlfilemodel.h"

static const std::string k_additionExprName = "addition";
static const std::string k_multiplicationExprName = "multiplication";
static const std::string k_subtractionExprName = "subtraction";
static const std::string k_divisionExprName = "division";
static const std::string k_mainTag = "expressions";

int XMLFileModel::evaluateSimpleExpression( const ptree::value_type &aNode )
{
    int expressionResult;
    AbstractExpression* currentExprEvaluator;
    
    if (aNode.first == k_additionExprName) {
        // Addition expression evaluation
        currentExprEvaluator = new additionExpression();
        BOOST_FOREACH(const ptree::value_type & additionNode, aNode.second){
            std::string itemVal = additionNode.second.data();
            ((additionExpression*)currentExprEvaluator)->addVal( atoi(itemVal.c_str()) );
        }
        expressionResult = currentExprEvaluator->evalExpr();
        
    } else if (aNode.first == k_multiplicationExprName) {
        // Multiplication expression evaluator
        currentExprEvaluator = new multiplicationExpression();
        BOOST_FOREACH(const ptree::value_type &multNode, aNode.second) {
            std::string itemVal = multNode.second.data();
            if (!itemVal.empty())
                ((multiplicationExpression*)currentExprEvaluator)->addVal( atoi(itemVal.c_str()) );
        }
        expressionResult = currentExprEvaluator->evalExpr();

    } else if (aNode.first == k_subtractionExprName) {
        // Substraction expression evaluator
        currentExprEvaluator = new substractionExpression();
        BOOST_FOREACH(const ptree::value_type &substNode, aNode.second) {
            std::string elTypeName = substNode.first;
            std::string itemVal = substNode.second.data();
            if (elTypeName == "minuend") {
                ((substractionExpression*)currentExprEvaluator)->setMinuend( atoi(itemVal.c_str()) );
            } else if (elTypeName == "subtrahend") {
                ((substractionExpression*)currentExprEvaluator)->setSubtrahend( atoi(itemVal.c_str()) );
            }
        }
        expressionResult = currentExprEvaluator->evalExpr();

    } else if (aNode.first == k_divisionExprName) {
        // Division expression evaluator
        currentExprEvaluator = new divisionExpression();
        BOOST_FOREACH(const ptree::value_type &divNode, aNode.second) {
            std::string elTypeName = divNode.first;
            std::string itemVal = divNode.second.data();
            if ( elTypeName == "dividend" ) {
                ((divisionExpression*)currentExprEvaluator)->setDividend( atoi(itemVal.c_str()) );
            } else if ( elTypeName == "divisor" ) {
                ((divisionExpression*)currentExprEvaluator)->setDivisor( atoi(itemVal.c_str()) );
            }
        }
        expressionResult = currentExprEvaluator->evalExpr();

    }

    if (currentExprEvaluator)
        delete currentExprEvaluator;

    return expressionResult;
}

bool XMLFileModel::isComplex( const ptree::value_type& aNode )
{
    return true;
}

int XMLFileModel::evaluateComplexExpression(  const ptree::value_type &aNode )
{
    // Retrive complexity true or false
    auto id = aNode.second;
    bool complexity;

    try {
        // If there is complex attribute, we'll get no exception and put there value of this attribut
        complexity = id.get<int>("<xmlattr>.complex");
    } catch (std::exception e) {
        // If we have no complex attribute, we'll get an exception and place false to flag of complexity
        complexity = false;
    }

    return complexity;
}