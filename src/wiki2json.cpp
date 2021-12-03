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

void print_unknow_option(const char *unknown) {
    std::cout << "Unknown option: " << unknown << std::endl;
}

void print_usage(const char *program) {
        std::cout
            << "Usage: " << program << " /a/path/to/wiki.txt [--html|tyokiie|text] [--protocol http] [--host localhost] [--path /]"
            << std::endl
            ;
}

int main(int argc, char** argv) {

    WikiEntityVariables::html_head = "<!-- Created with wiki2json by Eric Tang@TYO Lab, https://tyo.com.au) -->\n \
                    <!-- Follow me: https://twitter.com/_e_tang) -->\n \
					<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\"/>\n \
                    <script src=\"js/jquery-3.6.0.min.js\"></script> \
                    <script src=\"js/tyokiie.js\"></script>";

    if (argc > 1) {
        string file_name = argv[1];
        int to_what = 0;

        const char *unknown = NULL;
        for (int i = 2; i < argc; ++i) {
            const char *cmd = argv[i];
            int len = strlen(cmd);
            if (len < 2 || (cmd[0] == '-' && cmd[1] != '-')) {
                unknown = cmd;
                break;
            }

            if (!strcmp(argv[i], "--html")) {
                to_what = 1;
            }
            else if (!strcmp(argv[i], "--text")) {
                to_what = 2;
            }
            else if (!strcmp(argv[i], "--tyokiie")) {
                to_what = 3;
            }                        
            else if (!strcmp(argv[i], "--protocol")) {
                ++i;
                if (i < argc)
                    WikiEntityVariables::protocol = argv[i];
            }
            else if (!strcmp(argv[i], "--host")) {
                ++i;
                if (i < argc)
                    WikiEntityVariables::host = argv[i];                
            }            
            else if (!strcmp(argv[i], "--path")) {
                ++i;
                if (i < argc)
                    WikiEntityVariables::path = argv[i];                
            }
            else
                unknown = cmd;
        }

        if (unknown) {
            print_unknow_option(unknown);
            print_usage(argv[0]);
            exit(-1);
        }

        std::cerr
            << "Parsing "
            << file_name << endl;
        FileStream<> file_stream(file_name.c_str());
        Atom::max_id = 2 * (file_stream.end() - file_stream.begin()) + 1;

        parser_type parser(file_stream.begin(), file_stream.end());
        parser_type::document_type& doc = parser.parse();

        std::cerr << "Total nodes: " << doc.size() << std::endl;

        if (!to_what) {    
            // convert text to html rather than json
            std::cout << doc.to_json();
        }
        else if (to_what == 1) {
            std::cout << doc.to_html();
        }
        else if (to_what == 2) {
            std::cout << doc.to_text();
        }
        else if (to_what == 3) {
            std::cout << doc.to_tyokiie();
        }                
        else {
            std::cerr << "I don't know what format you what" << std::endl;
            print_usage(argv[0]);
        }
    }
    else {
        print_usage(argv[0]);

        return -1;
	}
    return 0;
}