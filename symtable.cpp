/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
using namespace std;
SymbolTable::SymbolTable(){root = NULL;size = 0;}

SymbolTable::~SymbolTable(){if(root){delete root;}}
void SymbolTable::insert(string k, UnlimitedRational *v)
{
    SymEntry *n1 = new SymEntry(k, v);SymEntry *t = root;SymEntry *p = NULL;
    if (root != NULL)
    {
        while (t != NULL)
        {
            p = t;
            if (k == t->key)
            {
                delete n1;
                return;
            }
            else if (k < t->key)
            {t = t->left;}
            else
            {t = t->right;}
        }
    }
    else
    {root = n1;size = size + 1;
    return;
    }
    if (p->key < k)
    {p->right = n1;size = size + 1;
    return;
    }
    else if (p->key > k)
    {p->left = n1;size = size + 1;
    return;
    }
}

void Remove(SymEntry *&n1, string k)
{
    if (n1 == NULL)
    {return;}
    else if (n1->key > k){return Remove(n1->left, k);}
    else if (n1->key < k){return Remove(n1->right, k);}
    else
    {
        // no child
        if (n1->left == NULL && n1->right == NULL)
        {
            delete n1;
            return;
        }
        // one child
        else if (n1->left == NULL && n1->right != NULL)
        {
            SymEntry *temp = n1->right;
            delete n1;
            n1 = temp;
            return;
        }
        else if (n1->left != NULL && n1->right == NULL)
        {
            SymEntry *temp = n1->left;
            delete n1;
            n1 = temp;
            return;
        }
        // two chiildren; successor
        //  n1->left!=NULL && n1->right!=NULL
        else
        {
            SymEntry *temp = n1->right;
            while (temp->left != NULL)
            {temp = temp->left;}
            n1->key = temp->key;n1->val = temp->val;
            Remove(n1->right, n1->key);
        }
    }
}
void SymbolTable::remove(string k)
{
    Remove(root, k);size = size - 1;
}
UnlimitedRational *Search(SymEntry * n1, string k)
{
    // <<"wait"<< n1->key <<endl;
    // cout<<k<<endl;
    if (n1 == NULL)
    {return NULL;}
    else if (n1->key == k)
    {return n1->val;}
    else if (n1->key > k)
    {return Search(n1->left, k);}
    else
    {return Search(n1->right, k);}
}
UnlimitedRational *SymbolTable::search(string k) { 
    return Search(root, k); 
    
    }
int SymbolTable::get_size() { return size; }
SymEntry *SymbolTable::get_root() { return root; }