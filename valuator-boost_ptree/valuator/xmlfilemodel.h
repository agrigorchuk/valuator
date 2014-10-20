//
//  xmlfilemodel.h
//  valuator
//
//  Created by Oleksandr Hryhorchuk on 9/23/14.
//  Copyright (c) 2014 Oleksandr Hryhorchuk. All rights reserved.
//

#ifndef __valuator__xmlfilemodel__
#define __valuator__xmlfilemodel__

#include <string>

#include <boost/container/vector.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include "expressions.h"

    using boost::property_tree::ptree;
    // Single tone which Models work with file

    class XMLFileModel
    {
    public:
        XMLFileModel() : m_rootNode() {}
        
        ~XMLFileModel()
        {
            m_rootNode.clear();
        }
        
        // Method populates m_rootNode from m_inFileName
        bool populateTree(const std::string& aInFileName);
        bool evaluateTree(const std::string& aOutFileName);
        
        static int evaluateSimpleExpression( const ptree::value_type& aNode );
        static int evaluateComplexExpression(  const ptree::value_type& aNode );
        
        static bool isComplex( const ptree::value_type& aNode );
    private:
        ptree m_rootNode;
        std::ofstream m_resultFileStrem;
    };


#endif /* defined(__valuator__xmlfilemodel__) */
