/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
// #include <iostream>

SymEntry::SymEntry()
{this->left = NULL;this->right = NULL;this->val = new UnlimitedRational();this->key = "";}
SymEntry::SymEntry(string k, UnlimitedRational *v)
{this->left = NULL;this->right = NULL;this->val = new UnlimitedRational(v->get_p()  ,v->get_q());this->key = k;}
SymEntry::~SymEntry()
{
    if(right){delete this->right;}
    if(left){delete this->left;}
    if(val != NULL){delete val;}
}