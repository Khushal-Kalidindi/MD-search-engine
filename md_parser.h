#ifndef MD_PARSER_H
#define MD_PARSER_H

#include <string>
#include <set>

#include "pageparser.h"

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;

class MDParser : public PageParser {
public:
    /**
     * See documentation in PageParser class
     * [TO BE COMPLETED]
     */
    void parse(std::istream& istr,
               std::set<std::string>& allSearchableTerms,
               std::set<std::string>& allOutgoingLinks);

    /**
     * See documentation in PageParser class
     * [TO BE COMPLETED]
     */
    std::string display_text(std::istream& filename);

private:
    // You may add additional private helpers or data members below
    PARSE_STATE_T currState = NORMALTEXT;

    void changeState(PARSE_STATE_T state){
        currState = state;
    }
    void buildTerm(char c, std::string& term, std::set<std::string>& termSet);
    void forcePushTerm(std::string& term, std::set<std::string>& termSet);

    void buildLink(char c, std::string& link, std::set<std::string>& linkSet);
    void forcePushLink(std::string& link, std::set<std::string>& linkSet);

};

#endif
