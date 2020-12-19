//
// Created by XingfengYang on 2020/12/19.
//

#ifndef SYNESTIAOS_HTML_H
#define SYNESTIAOS_HTML_H

typedef struct HTMLAttribute {
    char *name;
    char *value;
} HTMLAttribute;

typedef struct HTMLElement {
    char *name;
    struct HTMLAttribute *attributes;
    struct HTMLElement *children;
} HTMLElement;


typedef HTMLElement *(*HTMLParserOperationParse)(struct HTMLParser *parser, const char *htmlStr);

typedef struct HTMLParserOperations {
    HTMLParserOperationParse parse;
} HTMLParserOperations;


typedef struct HTMLParser {
    struct HTMLElement *root;
    HTMLParserOperations operations;
} HTMLParser;

HTMLParser *html_parser_create(struct HTMLParser *parser);

#endif //SYNESTIAOS_HTML_H
