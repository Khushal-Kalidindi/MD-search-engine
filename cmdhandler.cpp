#include "cmdhandler.h"

#include "util.h"
using namespace std;

// Complete
QuitHandler::QuitHandler() {}

// Complete
QuitHandler::QuitHandler(Handler* next) : Handler(next) {}

// Complete
bool QuitHandler::canHandle(const std::string& cmd) const { return cmd == "QUIT"; }

// Complete
Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    return HANDLER_QUIT;
}

// Complete
PrintHandler::PrintHandler() {}

// Complete
PrintHandler::PrintHandler(Handler* next) : Handler(next) {}

// Complete
bool PrintHandler::canHandle(const std::string& cmd) const { return cmd == "PRINT"; }

// Complete
Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    } catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

// Add code for other handler class implementations below
IncomingHandler::IncomingHandler() {}

IncomingHandler::IncomingHandler(Handler* next) : Handler(next) {}

bool IncomingHandler::canHandle(const std::string& cmd) const { return cmd == "INCOMING"; }
// Complete
Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    string page_name;

    if (!(instr >> page_name)) {
        return HANDLER_ERROR;
    }
    WebPage* page = eng->retrieve_page(page_name);
    if (page == NULL)
        return HANDLER_ERROR;
    display_hits(page->incoming_links(), ostr);
    return HANDLER_OK;
}

OutgoingHandler::OutgoingHandler() {}

OutgoingHandler::OutgoingHandler(Handler* next) : Handler(next) {}

bool OutgoingHandler::canHandle(const std::string& cmd) const { return cmd == "OUTGOING"; }
// Complete
Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    string page_name;

    if (!(instr >> page_name)) {
        return HANDLER_ERROR;
    }
    WebPage* page = eng->retrieve_page(page_name);
    if (page == NULL)
        return HANDLER_ERROR;
    display_hits(page->outgoing_links(), ostr);
    return HANDLER_OK;
}

AndHandler::AndHandler() {}

// Complete
AndHandler::AndHandler(Handler* next) : Handler(next) {}

// Complete
bool AndHandler::canHandle(const std::string& cmd) const { return cmd == "AND"; }

// Complete
Handler::HANDLER_STATUS_T AndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    string term;

    if (!(instr >> term)) {
        return HANDLER_ERROR;
    }
    std::vector<std::string> terms;
    terms.push_back(term);
    while (instr >> term) {
        terms.push_back(term);
    }
    WebPageSetCombiner* andCombiner = new AndWebPageSetCombiner();
    display_hits(eng->search(terms, andCombiner), ostr);
    delete andCombiner;
    return HANDLER_OK;
}

OrHandler::OrHandler() {}

// Complete
OrHandler::OrHandler(Handler* next) : Handler(next) {}

// Complete
bool OrHandler::canHandle(const std::string& cmd) const { return cmd == "OR"; }

// Complete
Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    string term;

    if (!(instr >> term)) {
        return HANDLER_ERROR;
    }
    std::vector<std::string> terms;
    terms.push_back(term);
    while (instr >> term) {
        terms.push_back(term);
    }
    WebPageSetCombiner* orCombiner = new OrWebPageSetCombiner();
    display_hits(eng->search(terms, orCombiner), ostr);
    delete orCombiner;
    return HANDLER_OK;
}

DiffHandler::DiffHandler() {}

// Complete
DiffHandler::DiffHandler(Handler* next) : Handler(next) {}

// Complete
bool DiffHandler::canHandle(const std::string& cmd) const { return cmd == "DIFF"; }

// Complete
Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    string term;

    if (!(instr >> term)) {
        return HANDLER_ERROR;
    }
    std::vector<std::string> terms;
    terms.push_back(term);
    while (instr >> term) {
        terms.push_back(term);
    }
    WebPageSetCombiner* diffCombiner = new DiffWebPageSetCombiner();
    display_hits(eng->search(terms, diffCombiner), ostr);
    delete diffCombiner;
    return HANDLER_OK;
}