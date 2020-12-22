//
// Created by XingfengYang on 2020/12/19.
//

#include "libhtml/html.h"
#include "libc/stdbool.h"
#include "libc/stdlib.h"

#define nullptr ((void *) 0)


bool html_parser_match_char(struct HTMLParser *parser, char ch) {
    if (parser->htmlStr[parser->pos] == ch) {
        return true;
    }
    return false;
}

void html_parser_consume_char(struct HTMLParser *parser, char ch) {
    if (parser->htmlStr[parser->pos] == ch) {
        parser->pos++;
    }
}

bool html_parser_match_str(struct HTMLParser *parser, StringRef str) {
    for (uint32_t i = 0; i < str.length; i++) {
        if (!(parser->htmlStr[parser->pos + i]) || (parser->htmlStr[parser->pos + i] != str.str[str.pos + i])) {
            return false;
        }
    }
    return true;
}

void html_parser_consume_str(struct HTMLParser *parser, StringRef str) {
    for (uint32_t i = 0; i < str.length; i++) {
        html_parser_consume_char(parser,str.str[str.pos + i]);
    }
}

bool isAlpha(char ch) {
    if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
        return true;
    }
    return false;
}

void html_parser_consume_while_char(struct HTMLParser *parser, char ch) {
    while (parser->htmlStr[parser->pos] && (parser->htmlStr[parser->pos] == ch)) {
        parser->pos++;
    }
}

void html_parser_consume_whitespace(struct HTMLParser *parser) {
    html_parser_consume_while_char(parser, ' ');
}

StringRef html_parser_parse_name(struct HTMLParser *parser) {
    uint32_t index = 0;
    while (parser->htmlStr[parser->pos + index] && isAlpha(parser->htmlStr[parser->pos + index])) {
        index++;
    }
    struct StringRef ref = {
            .pos = parser->pos,
            .length = index,
            .str = parser->htmlStr,
    };
    return ref;
}

StringRef html_parser_parse_str(struct HTMLParser *parser) {
    uint32_t index = 0;
    while (parser->htmlStr[parser->pos + index] && parser->htmlStr[parser->pos + index]!='"') {
        index++;
    }
    struct StringRef ref = {
            .pos = parser->pos,
            .length = index,
            .str = parser->htmlStr,
    };
    return ref;
}

StringRef html_parser_parse_attribute_value(struct HTMLParser *parser){
    if(html_parser_match_char(parser,'"')){
        html_parser_consume_char(parser,'"');
        StringRef attrValue = html_parser_parse_str(parser);
        html_parser_consume_str(parser,attrValue);
        html_parser_consume_char(parser,'"');
        return attrValue;
    }else{
        StringRef attrValue = html_parser_parse_name(parser);
        html_parser_consume_str(parser,attrValue);
        return attrValue;
    }
}

HTMLAttribute *html_parser_parse_attributes(struct HTMLParser *parser) {
    while(!html_parser_match_char(parser,'>')) {
        StringRef attrName = html_parser_parse_name(parser);
        html_parser_consume_str(parser, attrName);

        printf("attrName: ");
        string_ref_print(attrName);
        printf("\n");

        html_parser_consume_whitespace(parser);

        html_parser_match_char(parser, '=');
        html_parser_consume_char(parser, '=');

        html_parser_consume_whitespace(parser);

        StringRef attrValue = html_parser_parse_attribute_value(parser);
        html_parser_consume_str(parser, attrValue);
        printf("attrValue: ");
        string_ref_print(attrValue);
        printf("\n");

        html_parser_consume_whitespace(parser);

        struct HTMLAttribute attribute = {
                .name = attrName,
                .value = attrValue,
        };
    }
    // TODO:
}

StringRef html_parser_parse_content(struct HTMLParser *parser) {
    uint32_t index = 0;
    while (parser->htmlStr[parser->pos + index] && parser->htmlStr[parser->pos + index]!='<') {
        index++;
    }
    struct StringRef ref = {
            .pos = parser->pos,
            .length = index,
            .str = parser->htmlStr,
    };
    return ref;
}

HTMLDOM *html_parser_parse_element(struct HTMLParser *parser) {
    if (html_parser_match_char(parser, '<')) {
        html_parser_consume_char(parser, '<');

        StringRef tagName = html_parser_parse_name(parser);
        html_parser_consume_str(parser, tagName);

        printf("tagName: ");
        string_ref_print(tagName);
        printf("\n");

        html_parser_consume_whitespace(parser);

        HTMLAttribute *attributes = html_parser_parse_attributes(parser);
        html_parser_match_char(parser, '>');
        html_parser_consume_char(parser, '>');

        HTMLDOM *children = html_parser_parse_element(parser);

        html_parser_match_str(parser, string_ref("</"));
        html_parser_consume_str(parser, string_ref("</"));

        html_parser_match_str(parser, tagName);
        html_parser_consume_str(parser, tagName);

        html_parser_match_char(parser, '>');
        html_parser_consume_char(parser, '>');

        HTMLElement element = {
                .name = tagName,
                .attributes = attributes,
                .children = children,
        };

        HTMLDOM htmlElement = {
                .type = HTMLNodeType_Text,
                .element = element,
        };
        // TODO
        // return htmlElement;
    } else {
        StringRef content = html_parser_parse_content(parser);
        html_parser_consume_str(parser,content);
        printf("content: ");
        string_ref_print(content);
        printf("\n");

        struct HTMLDOM htmldom = {
                .type =HTMLNodeType_Text,
                .content = content,
        };
        // TODO
        // return htmldom;
    }
}

HTMLDOM *html_parser_default_parse(struct HTMLParser *parser) {
    HTMLDOM *root = html_parser_parse_element(parser);
    parser->root = root;
    return root;
}

void html_parser_default_print(struct HTMLParser *parser) {
    if (parser->root == nullptr) {
//        printf("root is null");
    } else {

    }
}

HTMLParser *html_parser_create(struct HTMLParser *parser) {
    parser->operations.parse = html_parser_default_parse;
    parser->operations.print = html_parser_default_print;
    parser->pos = 0;
    parser->root = nullptr;
    parser->htmlStr = "<root id=\"rootId\" class=\"root\">"
                      "<div name=\"container\">"
                      "<p>test</p>"
                      "</div>"
                      "<ul>"
                      "<li>li1</li>"
                      "<li>li1</li>"
                      "</ul>"
                      "</root>";
}
