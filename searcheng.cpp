#include "searcheng.h"

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

// Helper function that will extract the extension of a filename
std::string extract_extension(const std::string& filename);

std::string extract_extension(const std::string& filename) {
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}

// To be updated as needed
SearchEng::SearchEng() {}

// To be completed
SearchEng::~SearchEng() {
    std::map<std::string, PageParser*>::iterator p_del_itr;
    for (p_del_itr = parsers_.begin(); p_del_itr != parsers_.end(); ++p_del_itr) {
        delete p_del_itr->second;
    }
    parsers_.clear();

    std::map<std::string, WebPage*>::iterator f_del_itr;
    for (f_del_itr = page_by_filename_.begin(); f_del_itr != page_by_filename_.end(); ++f_del_itr) {
        delete f_del_itr->second;
    }
    page_by_filename_.clear();
}

// Complete
void SearchEng::register_parser(const std::string& extension, PageParser* parser) {
    if (parsers_.find(extension) != parsers_.end()) {
        throw std::invalid_argument("parser for provided extension already exists");
    }
    parsers_.insert(make_pair(extension, parser));
}

// Complete
void SearchEng::read_pages_from_index(const std::string& index_file) {
    ifstream ifile(index_file.c_str());
    if (ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while (ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

// To be completed
void SearchEng::read_page(const string& filename) {
    // OPENING FILE AND INSITIANSIATING PAGE
    ifstream ifile(filename);
    if (ifile.fail()) {
        throw std::invalid_argument("filename invalid");
    }
    string ext = extract_extension(filename);
    PageParser* tempParser = getParser(ext);
    if (tempParser == NULL)
        throw std::logic_error("no parser registered for extension");
    WebPage* page;
    std::map<std::string, WebPage*>::iterator file_it = page_by_filename_.find(filename);
    if (file_it != page_by_filename_.end())
        page = file_it->second;
    else {
        page = new WebPage(filename);
        page_by_filename_.insert(make_pair(filename, page));
    }
    // PARSING
    std::set<std::string> all_search_terms;
    std::set<std::string> all_out_links;
    tempParser->parse(ifile, all_search_terms, all_out_links);
    page->all_terms(all_search_terms);
    // ADDING TO INDEX
    std::set<std::string>::iterator term_itr;
    for (term_itr = all_search_terms.begin(); term_itr != all_search_terms.end(); ++term_itr) {
        std::map<std::string, std::set<WebPage*>>::iterator index_search_itr = index_.find(*term_itr);
        if (index_search_itr == index_.end()) {
            WebPageSet wps;
            std::map<std::string, std::set<WebPage*>>::iterator new_item
                    = (index_.insert(make_pair(*term_itr, wps))).first;
            new_item->second.insert(page);
        } else {
            index_search_itr->second.insert(page);
        }
    }
    // OUTGOING/INCOMING LINKS
    std::set<std::string>::iterator it;
    for (it = all_out_links.begin(); it != all_out_links.end(); ++it) {
        std::map<std::string, WebPage*>::iterator file_it = page_by_filename_.find(*it);
        if (file_it != page_by_filename_.end()) {
            page->add_outgoing_link(file_it->second);
            file_it->second->add_incoming_link(page);
        } else {
            WebPage* new_page = new WebPage(*it);
            page_by_filename_.insert(make_pair(*it, new_page));
            page->add_outgoing_link(new_page);
            new_page->add_incoming_link(page);
        }
    }
}

// To be completed
WebPage* SearchEng::retrieve_page(const std::string& page_name) const {
    std::map<std::string, WebPage*>::const_iterator file_it = page_by_filename_.find(page_name);
    return file_it != page_by_filename_.end() ? file_it->second : NULL;
}

// To be completed
void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const {
    ifstream ifile(page_name);
    if (ifile.fail())
        throw std::invalid_argument("filename invalid");
    string ext = extract_extension(page_name);
    PageParser* tempParser = getParser(ext);
    if (tempParser == NULL)
        throw std::logic_error("no parser registered for extension");
    ostr << tempParser->display_text(ifile);
}

// To be completed
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const {
    WebPageSet res;
    if (terms.size() == 0) {
        return res;
    } else if (terms.size() == 1) {
        return getSetFromIndex(terms[0]);
    }
    res = combiner->combine(getSetFromIndex(terms[0]), getSetFromIndex(terms[1]));
    for (size_t i = 2; i < terms.size(); ++i) {
        res = combiner->combine(res, getSetFromIndex(terms[i]));
    }
    return res;
}
WebPageSet SearchEng::getSetFromIndex(std::string term) const {
    WebPageSet res;
    std::map<std::string, std::set<WebPage*>>::const_iterator search_itr = index_.find(term);
    if (search_itr != index_.end()) {
        res = search_itr->second;
    }
    return res;
}
// Add private helper function implementations here

PageParser* SearchEng::getParser(std::string ext) const {
    std::map<std::string, PageParser*>::const_iterator it = parsers_.find(ext);
    return it != parsers_.end() ? it->second : NULL;
}
