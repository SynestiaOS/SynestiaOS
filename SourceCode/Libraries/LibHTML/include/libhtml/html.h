//
// Created by XingfengYang on 2020/12/19.
//

#ifndef SYNESTIAOS_HTML_H
#define SYNESTIAOS_HTML_H

#include "libc/stdint.h"
#include "libstring/string_ref.h"

typedef struct HTMLAttribute {
    StringRef name;
    StringRef value;
} HTMLAttribute;

typedef struct HTMLElement {
    StringRef name;
    HTMLAttribute *attributes;
    struct HTMLElement *children;
} HTMLElement;


typedef HTMLElement *(*HTMLParserOperationParse)(struct HTMLParser *parser);

typedef struct HTMLParserOperations {
    HTMLParserOperationParse parse;
} HTMLParserOperations;


typedef struct HTMLParser {
    struct HTMLElement *root;
    HTMLParserOperations operations;
    uint32_t pos;
    const char *htmlStr;
} HTMLParser;

HTMLParser *html_parser_create(struct HTMLParser *parser);

#endif //SYNESTIAOS_HTML_H
