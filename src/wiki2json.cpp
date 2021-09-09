/******************************************************************************
 * This file is part of the Simple Text Processing Library(STPL).
 * (c) Copyright 2021 TYONLINE TECHNOLOGY PTY. LTD.
 *
 * This file may be distributed and/or modified under the terms of the
 * GNU LESSER GENERAL PUBLIC LICENSE, Version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.LGPL included in the
 * packaging of this file.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 *******************************************************************************
 *
 * @author				Ling-Xiang(Eric) Tang 
 * @twitter				https://twitter.com/_e_tang
 *
 *******************************************************************************/

#include <wiki/stpl_wiki_parser.h>
#include "wiki2json.h"

#include <stpl_stream.h>

#include <map>

using namespace std;
using namespace stpl;
using namespace stpl::WIKI;

typedef WIKI::WikiParser<icstring, FileStream<>::iterator> parser_type;
int Atom::counter = 0;

// static std::map<int, std::string> groups;

string get_entity_info(int group, int type) {
    string value;
    //groups.insert(std::pair<int, std::string>(LAYOUT, "Layout"));
    switch (group)
    {
    case LAYOUT:
        value = "Layout";
        break;
    case TAG:
        value = "Tag";
        break;    
    case LINK:
        value = "Link";
        break;    
    case TBASE:
        if (type == TABLE)
            value = "Table";
        else if (type == TEMPLATE)
            value = "Template";
        else
            value = "TBASE";
        break;    
    
    case COMMENT:
        value = "Comment";
        break;    
    case TEXT:
        value = "Text";
        break;    
    case PROPERTY:
        value = "Property";
        break;    
    default:
        break;
    }
    return value;
}

int main(int argc, char** argv) {
    if (argc == 3 && !strcmp(argv[2], "--html")) {    
        // convert text to html rather than json
        
    }
    else if (argc == 2) {
        
		string file_name = argv[ 1 ];
        std::cout
            << "Parsing "
            << file_name << endl;
		FileStream<> file_stream(file_name.c_str());

		parser_type parser(file_stream.begin(), file_stream.end());
        parser_type::document_type& doc = parser.parse();
        //std::vector<parse_type::document_type::entity_type > nodes = doc->get_nodes();
        parser_type::document_type::container_type& nodes = doc.children();
        std::cout << "Total nodes: " << doc.size() << std::endl;

        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            //std::cout << "Node Info: " << get_entity_info((*it)->get_group(), (*it)->get_type()) << std::endl;
            // std::cout << "Node Type: " << (*it)->get_type() << std::endl;
            //std::cout << "Node Content: " << std::endl;
            std::cout << '(' << (*it)->get_id() << ") ";
            std::cout << (*it)->to_html();
            std::cout << std::endl;
        }
        
		// typedef WIKI::WikiParser<icstring, FileStream<>::iterator>::element_type element_type;
		// typedef WIKI::WikiParser<icstring, FileStream<>::iterator>::tree_type tree_type;
		// tree_type tree = parser.parse_tree();			
		// tree_type::iterator	iner_it = tree.begin();

    }
    else {
        std::cout
            << "Usage: " << argv[0] << " /a/path/to/wiki.txt [--html]"
            // << std::endl
            // << '\t'
            // << argv[ 0 ]
            // << " example.html"
            << std::endl
            ;

        return -1;
	}
    return 0;
}