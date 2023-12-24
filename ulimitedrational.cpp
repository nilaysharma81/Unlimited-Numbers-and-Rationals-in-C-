/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
using namespace std;

UnlimitedRational::UnlimitedRational(){p = new UnlimitedInt("1");q = new UnlimitedInt("1");}
UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    if (den->to_string() == "0")
    {p = new UnlimitedInt("0");q = new UnlimitedInt("0");}
    else
    {
        // first make sign of denominoator as + isit is -
        UnlimitedInt *temp = new UnlimitedInt("-1");
        string s;
        if (den->get_sign() == 1)
        {p = new UnlimitedInt(num->to_string());q = new UnlimitedInt(den->to_string());}
        else
        {p = UnlimitedInt::mul(num, temp);q = UnlimitedInt::mul(den, temp);delete temp;}
        if (p->get_sign() == 1)
        {s = p->to_string();}
        else
        {s = p->to_string();s = s.substr(1);}
        // now we know that q is positive
        //  now we have to make it to lowest fraction so p=p/gcd(p,q) and q=q/(gcd(p,q))
        UnlimitedInt *tep = new UnlimitedInt(s);UnlimitedInt *temp1 = new UnlimitedInt(q->to_string());UnlimitedInt *g;
        // when temp>tep
        while(tep->to_string() != "0")
        {UnlimitedInt* temp2 = UnlimitedInt::mod(temp1,tep);UnlimitedInt* temp3 = new UnlimitedInt(tep->to_string());
        delete temp1;
        tep = temp2;temp1 = temp3;}
        g = temp1;
        if(g->to_string() != "0"){p = UnlimitedInt::div(p, g);q = UnlimitedInt::div(q, g);}
    }
}
UnlimitedRational::~UnlimitedRational(){if(p){delete p;}if(q){delete q;}}
UnlimitedInt *UnlimitedRational::get_p() { return p; }
UnlimitedInt *UnlimitedRational::get_q() { return q; }
string UnlimitedRational::get_p_str() { return p->to_string(); }
string UnlimitedRational::get_q_str() { return q->to_string(); }
string UnlimitedRational::get_frac_str() { return p->to_string() + "/" + q->to_string(); }
UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    // lowest frac (num1*den2+num2*den1 /(den1*den2))
    UnlimitedInt *num1 = i1->get_p();UnlimitedInt *num2 = i2->get_p();
    UnlimitedInt *den2 = i2->get_q();UnlimitedInt *den1 = i1->get_q();
    UnlimitedInt *firstterm = UnlimitedInt::mul(num1, den2);UnlimitedInt *secondterm = UnlimitedInt::mul(num2, den1);
    UnlimitedInt *den = UnlimitedInt::mul(den1, den2);UnlimitedInt *num = UnlimitedInt::add(firstterm, secondterm);
    UnlimitedRational *res = new UnlimitedRational(num, den);
    return res;
}
UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *num1 = i1->get_p();UnlimitedInt *num2 = i2->get_p();
    UnlimitedInt *den2 = i2->get_q();UnlimitedInt *den1 = i1->get_q();
    UnlimitedInt *firstterm = UnlimitedInt::mul(num1, den2);UnlimitedInt *secondterm = UnlimitedInt::mul(num2, den1);
    UnlimitedInt *den = UnlimitedInt::mul(den1, den2);UnlimitedInt *num = UnlimitedInt::sub(firstterm, secondterm);
    UnlimitedRational *res = new UnlimitedRational(num, den);
    return res;
}
UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *num1 = i1->get_p();UnlimitedInt *num2 = i2->get_p();
    UnlimitedInt *den2 = i2->get_q();UnlimitedInt *den1 = i1->get_q();
    UnlimitedInt *firstterm = UnlimitedInt::mul(num1, num2);UnlimitedInt *secondterm = UnlimitedInt::mul(den2, den1);
    UnlimitedRational *res = new UnlimitedRational(firstterm, secondterm);
    return res;
}
UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{

    UnlimitedInt *num1 = i1->get_p();UnlimitedInt *num2 = i2->get_p();
    UnlimitedInt *den2 = i2->get_q();UnlimitedInt *den1 = i1->get_q();
    if (num2->to_string() == "0")
    {
        UnlimitedInt *firstterm = new UnlimitedInt("0");UnlimitedInt *secondterm = new UnlimitedInt("0");
        UnlimitedRational *res = new UnlimitedRational(firstterm, secondterm);
    }
    else
    {
        UnlimitedInt *firstterm = UnlimitedInt::mul(num1, den2);UnlimitedInt *secondterm = UnlimitedInt::mul(num2, den1);
        UnlimitedRational *res = new UnlimitedRational(firstterm, secondterm);
        return res;
    }
}