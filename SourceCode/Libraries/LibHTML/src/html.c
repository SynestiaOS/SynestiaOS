//
// Created by XingfengYang on 2020/12/19.
//

#include "libhtml/html.h"
#include "libc/stdbool.h"


bool html_parser_parse_match_char(struct HTMLParser *parser, char ch) {
    if (parser->htmlStr[parser->pos] == ch) {
        return true;
    }
    return false;
}

bool html_parser_parse_match_str(struct HTMLParser *parser, StringRef str) {
    for (uint32_t i = 0; i < str.length; i++) {
        if (!(parser->htmlStr[parser->pos + i]) || (parser->htmlStr[parser->pos + i] != str.str[str.pos + i])) {
            return false;
        }
    }
    return true;
}

bool isAlpha(char ch) {
    if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
        return true;
    }
    return false;
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

HTMLAttribute *html_parser_parse_attributes(struct HTMLParser *parser) {
    // TODO:
}

StringRef html_parser_parse_str(struct HTMLParser *parser) {
    // TODO:
}

HTMLElement *html_parser_parse_element(struct HTMLParser *parser) {
    if (html_parser_parse_match_char(parser, '<')) {
        StringRef name = html_parser_parse_name(parser);
        HTMLAttribute *attributes = html_parser_parse_attributes(parser);
        HTMLElement *children = html_parser_parse_element(parser);
        html_parser_parse_match_str(parser, string_ref("</"));
        html_parser_parse_match_str(parser, name);
        html_parser_parse_match_char(parser, '>');

        // TODO:
    } else {
        StringRef content = html_parser_parse_str(parser);
    }
}

HTMLElement *html_parser_default_parse(struct HTMLParser *parser) {
    return html_parser_parse_element(parser);
}

HTMLParser *html_parser_create(struct HTMLParser *parser) {
    parser->operations.parse = html_parser_default_parse;
    parser->pos = 0;
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
