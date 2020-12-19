//
// Created by XingfengYang on 2020/12/19.
//
#include "libhtml/html.h"
#include "libc/stdint.h"

HTMLElement *html_parser_default_parse_element(struct HTMLParser *parser, const char* htmlStr, uint32_t pos){

}

HTMLElement *html_parser_default_parse(struct HTMLParser *parser, const char *htmlStr){
    const char* str = "<root id=\"rootId\" class=\"root\">"
                        "<div name=\"container\">"
                            "<p>test</p>"
                        "</div>"
                        "<ul>"
                            "<li>li1</li>"
                            "<li>li1</li>"
                        "</ul>"
                      "</root>";

    return html_parser_default_parse_element(parser,str,0);
}

HTMLParser* html_parser_create(struct HTMLParser* parser){
    parser->operations.parse = html_parser_default_parse;
}
