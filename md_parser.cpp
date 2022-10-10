#include "md_parser.h"

#include "util.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

// To be completed
void MDParser::parse(
        std::istream& istr, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks) {

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();

    // Complete your code below
    // Initialize the current term and link as empty strings.
    std::string term = "";
    std::string link = "";

    char c = istr.get();

    while (!istr.fail()) {
        switch (this->currState) {
        case NORMALTEXT:
            switch (c) {
            case '[':
                forcePushTerm(term, allSearchableTerms);
                changeState(LINKTEXT);
                break;
            default:
                buildTerm(c, term, allSearchableTerms);
                break;
            }
            break;
        case LINKTEXT:
            switch (c) {
            case ']':
                forcePushTerm(term, allSearchableTerms);
                changeState(ISLINK);
                break;
            default:
                buildTerm(c, term, allSearchableTerms);
                break;
            }
            break;
        case ISLINK:
            switch (c) {
            case '(':
                changeState(LINKURL);
                break;
            case '[':
                forcePushTerm(term, allSearchableTerms);
                changeState(LINKTEXT);
                break;
            default:
                changeState(NORMALTEXT);
                break;
            }
            break;
        case LINKURL:
            switch (c) {
            case ')':
                forcePushLink(link, allOutgoingLinks);
                changeState(NORMALTEXT);
                break;
            default:
                buildLink(c, link, allOutgoingLinks);
                break;
            }
            break;
        default:
            break;
        }
        c = istr.get();
    }
    // Since the last term in the file may not have punctuation, there may be a valid term in
    // the "term" variable, so we need to insert it into the allSearchableTerms set.
    if (term != "") {
        term = conv_to_lower(term);
        allSearchableTerms.insert(term);
    }
}

// To be completed
std::string MDParser::display_text(std::istream& istr) {
    std::string retval;

    std::string term = "";
    std::string link = "";

    char c = istr.get();

    while (!istr.fail()) {
        switch (this->currState) {
        case NORMALTEXT:
            switch (c) {
            case '[':
                retval += c;
                changeState(LINKTEXT);
                break;
            default:
                retval += c;
                break;
            }
            break;
        case LINKTEXT:
            switch (c) {
            case ']':
                retval += c;
                changeState(ISLINK);
                break;
            default:
                retval += c;
                break;
            }
            break;
        case ISLINK:
            switch (c) {
            case '(':
                changeState(LINKURL);
                break;
            default:
                changeState(NORMALTEXT);
                break;
            }
            break;
        case LINKURL:
            switch (c) {
            case ')':
                // forcePushLink(link, allOutgoingLinks);
                changeState(NORMALTEXT);
                break;
            default:
                // buildLink(c, link, allOutgoingLinks);
                break;
            }
            break;
        default:
            break;
        }
        c = istr.get();
    }
    // Since the last term in the file may not have punctuation, there may be a valid term in
    // the "term" variable, so we need to insert it into the allSearchableTerms set.
    // if(term != "")
    // {
    //     term = conv_to_lower(term);
    //     allSearchableTerms.insert(term);
    // }
    return retval;
}

void MDParser::buildTerm(char c, std::string& term, std::set<std::string>& termSet) {
    if (!isalnum(c)) {
        if (term != "") {
            term = conv_to_lower(term);
            termSet.insert(term);
        }
        term = "";
    } else
        term += c;
}
void MDParser::forcePushTerm(std::string& term, std::set<std::string>& termSet) {
    if (term != "") {
        term = conv_to_lower(term);
        termSet.insert(term);
        term = "";
    }
}

void MDParser::buildLink(char c, std::string& link, std::set<std::string>& linkSet) { link += c; }
void MDParser::forcePushLink(std::string& link, std::set<std::string>& termSet) {
    if (link != "") {
        link = conv_to_lower(link);
        termSet.insert(link);
        link = "";
    }
}
