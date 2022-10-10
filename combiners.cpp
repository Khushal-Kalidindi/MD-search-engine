#include "combiners.h"

#include "searcheng.h"

// Complete the necessary code
WebPageSet AndWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB) {
    WebPageSet res;
    WebPageSet::iterator it;
    for (it = setA.begin(); it != setA.end(); ++it) {
        if (setB.find((*it)) != setB.end())
            res.insert(*it);
    }
    return res;
}

WebPageSet OrWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB) {
    WebPageSet res;
    WebPageSet::iterator it;
    for (it = setA.begin(); it != setA.end(); ++it) {
        res.insert(*it);
    }
    for (it = setB.begin(); it != setB.end(); ++it) {
        res.insert(*it);
    }
    return res;
}
WebPageSet DiffWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB) {
    WebPageSet res;
    WebPageSet::iterator it;
    for (it = setA.begin(); it != setA.end(); ++it) {
        if (setB.find((*it)) == setB.end())
            res.insert(*it);
    }
    return res;
}