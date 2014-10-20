//
//  main.cpp
//  valuator
//
//  Created by Oleksandr Hryhorchuk on 9/23/14.
//  Copyright (c) 2014 Oleksandr Hryhorchuk. All rights reserved.
//

#include <iostream>
#include "xmlfilemodel.h"
#include "expressions.h"

#include <boost/lexical_cast.hpp>

static const std::string k_additionExprName = "addition";
static const std::string k_multiplicationExprName = "multiplication";
static const std::string k_subtractionExprName = "subtraction";
static const std::string k_divisionExprName = "division";

int main(int argc, const char * argv[])
{
    // Result Map
    std::map<int, int> resultMap;

    // Result output file stream
    std::ofstream resultFile;
    resultFile.open ("/Users/ohryh/valuator_result.xml", std::ofstream::trunc | std::ofstream::out);
    resultFile << "<expressions>" << std::endl;
   
    using boost::property_tree::ptree;
    ptree wholeTree;

    read_xml("/Users/ohryh/valuator.xml", wholeTree);
    const ptree &expressions = wholeTree.get_child("expressions");

    if (expressions.empty())
        return -1;

    BOOST_FOREACH(const ptree::value_type &currExpr, expressions){
        std::cout << "*";
        int currExprIdNum;
        int nodeResult;

        // Retrive current expression Id
        auto id = currExpr.second;
        currExprIdNum = id.get<int>("<xmlattr>.id");

        // Check whether this expression is complex or not
        if (XMLFileModel::isComplex(currExpr))
            // In case of complexity -> parse it as the complex expression
            nodeResult = XMLFileModel::evaluateComplexExpression( currExpr );
        else
            // Otherwise -> parse it as the simple
            nodeResult = XMLFileModel::evaluateSimpleExpression( currExpr );
        
        // Put the result of current Node evaluation to the output file stream
        resultFile << "<result id=" << currExprIdNum << ">" << nodeResult << "</result>" << std::endl;
        // Map of results, actually we do not need it, just for fun
        resultMap[currExprIdNum] = nodeResult;
    }
    std::cout << std::endl;
    resultFile << "</expressions>";
    resultFile.close();

    return 0;
}

