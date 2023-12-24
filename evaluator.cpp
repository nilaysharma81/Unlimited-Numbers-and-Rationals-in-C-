#include "evaluator.h"
// #include <iostream>
using namespace std;

Evaluator ::Evaluator() { symtable = new SymbolTable(); }
Evaluator ::~Evaluator()
{
    delete symtable;
    for (int i = 0; i < expr_trees.size(); i++)
    {
        delete expr_trees[i];
    }
}
void Evaluator::parse(vector<string> code)
{
    ExprTreeNode *Treemid = new ExprTreeNode("=", new UnlimitedRational());
    ExprTreeNode *Treefirstleft = new ExprTreeNode("VAR", new UnlimitedInt());
    Treefirstleft->id = code[0];
    Treemid->left = Treefirstleft;

    for (int i = 2; i < code.size(); i++)
    {
        if (code[i] == "(")
        {
            continue;
        }
        else if (code[i] == ")")
        {
            ExprTreeNode *third = expr_trees.back();
            expr_trees.pop_back();
            ExprTreeNode *second = expr_trees.back();
            expr_trees.pop_back();
            ExprTreeNode *first = expr_trees.back();
            expr_trees.pop_back();
            second->left = first;
            second->right = third;
            expr_trees.push_back(second);
        }
        else
        {
            ExprTreeNode *temp = new ExprTreeNode();
            if (code[i] == "+")
            {
                temp->type = "ADD";
            }
            else if (code[i] == "-")
            {
                temp->type = "SUB";
            }
            else if (code[i] == "*")
            {
                temp->type = "MUL";
            }
            else if (code[i] == "/")
            {
                temp->type = "DIV";
            }
            else
            {
                bool is_number = true;
                for (int j = 0; j < code[i].size(); j++)
                {
                    if (code[i][j] == '-' || (code[i][j] >= '0' && code[i][j] <= '9'))
                    {
                    }
                    else
                    {
                        is_number = false;
                        break;
                    }
                }
                if (is_number)
                {
                    temp->type = "VAL";
                    UnlimitedInt *digits1 = new UnlimitedInt("1");
                    temp->val = new UnlimitedRational(new UnlimitedInt(code[i]), digits1);
                    temp->evaluated_value = new UnlimitedRational(new UnlimitedInt(code[i]), digits1);
                }
                else
                {
                    temp->type = "VAR";
                    temp->id = code[i];
                }
            }
            expr_trees.push_back(temp);
        }
    }
    Treemid->right = expr_trees.back();
    expr_trees.pop_back();
    expr_trees.push_back(Treemid);
}

void recursive_eval(ExprTreeNode *to_be_eval, SymbolTable *symtable)
{
    if (to_be_eval->type == "VAL")
    {
        return;
    }
    if (to_be_eval->type == "VAR")
    {
        UnlimitedRational *ans = symtable->search(to_be_eval->id);
        to_be_eval->val = new UnlimitedRational(ans->get_p(), ans->get_q());
        to_be_eval->evaluated_value = new UnlimitedRational(ans->get_p(), ans->get_q());
        return;
    }
    recursive_eval(to_be_eval->left, symtable);
    recursive_eval(to_be_eval->right, symtable);

    string to_be_done = to_be_eval->type;
    if (to_be_done == "ADD")
    {
        to_be_eval->val = UnlimitedRational::add(to_be_eval->left->evaluated_value, to_be_eval->right->evaluated_value);
        to_be_eval->evaluated_value = UnlimitedRational::add(to_be_eval->left->evaluated_value, to_be_eval->right->evaluated_value);
        return;
    }
    if (to_be_done == "SUB")
    {
        to_be_eval->val = UnlimitedRational::sub(to_be_eval->left->evaluated_value, to_be_eval->right->evaluated_value);
        to_be_eval->evaluated_value = UnlimitedRational::sub(to_be_eval->left->evaluated_value, to_be_eval->right->evaluated_value);
        return;
    }
    if (to_be_done == "MUL")
    {
        to_be_eval->val = UnlimitedRational::mul(to_be_eval->left->evaluated_value, to_be_eval->right->evaluated_value);
        to_be_eval->evaluated_value = UnlimitedRational::mul(to_be_eval->left->evaluated_value, to_be_eval->right->evaluated_value);
        return;
    }
    if (to_be_done == "DIV")
    {
        to_be_eval->val = UnlimitedRational::div(to_be_eval->left->evaluated_value, to_be_eval->right->evaluated_value);
        to_be_eval->evaluated_value = UnlimitedRational::div(to_be_eval->left->evaluated_value, to_be_eval->right->evaluated_value);
        return;
    }
}

void Evaluator ::eval()
{
    ExprTreeNode *to_eval = expr_trees[expr_trees.size() - 1];
    // cout<<"to_eval->right->type " <<to_eval->right->type<<endl;
    recursive_eval(to_eval->right, symtable);
    to_eval->val = new UnlimitedRational(to_eval->right->evaluated_value->get_p(), to_eval->right->evaluated_value->get_q());
    to_eval->evaluated_value = new UnlimitedRational(to_eval->right->evaluated_value->get_p(), to_eval->right->evaluated_value->get_q());
    to_eval->left->evaluated_value = new UnlimitedRational(to_eval->right->evaluated_value->get_p(), to_eval->right->evaluated_value->get_q());
    to_eval->left->val = new UnlimitedRational(to_eval->right->evaluated_value->get_p(), to_eval->right->evaluated_value->get_q());

    symtable->insert(to_eval->left->id, to_eval->left->evaluated_value);
}