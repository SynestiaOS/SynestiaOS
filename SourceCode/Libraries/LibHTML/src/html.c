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
        if (!(parser->htmlStr[parser->pos + i]) || (parser->htmlStr[parser->pos + i] != str.str[str.pos + i])) {
            parser->pos++;
        }
    }
}

bool isAlpha(char ch) {
    if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
        return true;
    }
    return false;
}

StringRef html_parser_parse_tag_name(struct HTMLParser *parser) {
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

void html_parser_consume_while_char(struct HTMLParser *parser, char ch) {
    while (parser->htmlStr[parser->pos] && (parser->htmlStr[parser->pos] == ch)) {
        parser->pos++;
    }
}

void html_parser_consume_whitespace(struct HTMLParser *parser) {
    html_parser_consume_while_char(parser, ' ');
}

HTMLAttribute *html_parser_parse_attributes(struct HTMLParser *parser) {
    // TODO:
}

StringRef html_parser_parse_str(struct HTMLParser *parser) {
    // TODO:
}

HTMLDOM *html_parser_parse_element(struct HTMLParser *parser) {
    if (html_parser_match_char(parser, '<')) {
        html_parser_consume_char(parser, '<');

        StringRef tagName = html_parser_parse_tag_name(parser);
        html_parser_consume_str(parser, tagName);

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
        StringRef content = html_parser_parse_str(parser);
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
        printf("root is null");
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
