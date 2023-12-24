/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode()
{this->val = new UnlimitedRational();this->left = NULL;this->right = NULL;this->id = "";this->type = "";this->evaluated_value = new UnlimitedRational();}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt *v)
{this->val = new UnlimitedRational(v, new UnlimitedInt("1"));this->evaluated_value = new UnlimitedRational(v , new UnlimitedInt("1"));this->left = NULL;this->right = NULL;this->id = "";this->type = t;}
ExprTreeNode::ExprTreeNode(string t, UnlimitedRational *v)
{this->left = NULL;this->right = NULL;val = new UnlimitedRational(v->get_p() , v->get_q());this->id = "";this->type = t;this->evaluated_value = new UnlimitedRational(v->get_p() , v->get_q());}
ExprTreeNode::~ExprTreeNode()
{
    if(right){delete this->right;}
    if(left){delete this->left;}
    if (val != NULL){delete val;}
    if (evaluated_value != NULL){delete evaluated_value;}
}