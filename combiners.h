#ifndef COMBINERS_H
#define COMBINERS_H

#include "searcheng.h"

/*** Define Derived WebPageSetCombiners (fOrWebPageSetCombiner AndWebPageSetCombiner, OrWebPageSetCombiner, DiffWebPageSetCombiner) classes below ***/
class AndWebPageSetCombiner : public WebPageSetCombiner {
    private:
    public: 
        AndWebPageSetCombiner(){
        }
        ~AndWebPageSetCombiner(){

        }
        WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};
class OrWebPageSetCombiner : public WebPageSetCombiner {
    private:
    public: 
        OrWebPageSetCombiner(){
        }
        ~OrWebPageSetCombiner(){

        }
        WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};
class DiffWebPageSetCombiner : public WebPageSetCombiner {
    private:
    public: 
        DiffWebPageSetCombiner(){
        }
        ~DiffWebPageSetCombiner(){

        }
        WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};


#endif