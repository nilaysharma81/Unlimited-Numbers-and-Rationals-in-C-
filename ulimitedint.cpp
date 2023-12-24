/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
using namespace std;

UnlimitedInt::UnlimitedInt()
{size = 1;sign = 1;capacity = 1;unlimited_int = new int[size];unlimited_int[0] = 0;}
UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{unlimited_int = new int[sz];capacity = cap;sign = sgn;size = sz;for (int i = 0; i < size; i++){unlimited_int[i] = ulimited_int[i];}}
UnlimitedInt::UnlimitedInt(string s)
{
    int m = s.size();
    if (s[0] == '-'){sign = -1;size = m - 1;}
    else{sign = 1;size = m;}
    capacity = size;unlimited_int = new int[size];
    for (int i = 0; i < size; i++){unlimited_int[i] = s[m - i - 1] - '0';}
}
UnlimitedInt::UnlimitedInt(int i)
{
    if(i == 0)
    {sign =1 ;size = 1;capacity = 1 ;unlimited_int = new int[1] ;unlimited_int[0] = 0;}
    else
    {
    if (i >= 0){sign = 1;}
    else{sign = -1;i = -i;}
    int t = i;size = 0;
    while (t > 0)
    {t = t / 10;size++;}
    capacity = size;unlimited_int = new int[size];
    for (int j = 0; j < size; j++)
    {unlimited_int[j] = i % 10;i = i / 10;}
    }
}
UnlimitedInt::~UnlimitedInt() { delete[] unlimited_int; }
int UnlimitedInt::get_size() { return size; }
int *UnlimitedInt::get_array() { return unlimited_int; }
int UnlimitedInt::get_sign() { return sign; }
int UnlimitedInt::get_capacity() { return capacity; }

bool comparer(UnlimitedInt *a, UnlimitedInt *b)
{
    if (a->get_size() > b->get_size()){return true;}
    else if (a->get_size() < b->get_size()){return false;}
    else
    {
        for (int i = a->get_size() - 1; i >= 0; i--)

        {
            if (a->get_array()[i] > b->get_array()[i]){return true;}
            if (a->get_array()[i] < b->get_array()[i]){return false;}
        }
        return true;
    }
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->to_string() == "0")
    {
        UnlimitedInt *ans = new UnlimitedInt(i2->get_array(), i2->get_size(), i2->get_sign(), i2->get_size());
        return ans;
    }
    if (i2->to_string() == "0")
    {
        UnlimitedInt *ans = new UnlimitedInt(i1->get_array(), i1->get_size(), i1->get_sign(), i1->get_size());
        return ans;
    }

    if (i1->get_sign() == i2->get_sign())
    {
        int *p = new int[i1->get_size()];
        int *q = new int[i2->get_size()];
        for (int i = 0; i < i1->get_size(); i++)
        {
            p[i] = i1->get_array()[i];
        }
        for (int i = 0; i < i2->get_size(); i++)
        {
            q[i] = i2->get_array()[i];
        }

        int max_size = max(i1->get_size(), i2->get_size());
        int min_size = min(i1->get_size(), i2->get_size());
        // cout<<"max_size "<<max_size<<endl;
        int *r = new int[max_size + 1];
        int my_carry = 0;
        for (int i = 0; i < max_size; i++)
        {
            // my_carry = 0;
            int current_digit = 0;
            current_digit = current_digit + my_carry;
            if (i < i1->get_size())
            {
                current_digit += p[i];
            }
            if (i < i2->get_size())
            {
                current_digit += q[i] ;
            }
            my_carry = current_digit / 10;
            current_digit = current_digit % 10;
            r[i] = current_digit;
        }

        r[max_size] = my_carry;
        int forward_zero = 0;
        int i = max_size;
        while (i >= 0 && r[i] == 0)
        {
            i--;
            forward_zero++;
        }
        int *s = new int[max_size + 1 - forward_zero];
        for (int i = 0; i < max_size + 1 - forward_zero; i++)
        {
            s[i] = r[i];
        }
        UnlimitedInt *ans = new UnlimitedInt(s, max_size + 1 - forward_zero, i1->get_sign(), max_size + 1 - forward_zero);
        return ans;
    }
    else
    {
        bool compare = true;
        if (i2->get_size() > i1->get_size())
        {
            compare = false;
        }
        else if (i2->get_size() == i1->get_size())
        {
            for (int i = i1->get_size() - 1; i >= 0; i--)
            {
                if (i1->get_array()[i] > i2->get_array()[i])
                {
                    break;
                }
                else if (i1->get_array()[i] < i2->get_array()[i])
                {
                    compare = false;
                    break;
                }
            }
        }

        if (compare)
        {
            int *p = new int[i1->get_size()];
            int *q = new int[i2->get_size()];
            for (int i = 0; i < i1->get_size(); i++)
            {
                p[i] = i1->get_array()[i];
            }
            for (int i = 0; i < i2->get_size(); i++)
            {
                q[i] = i2->get_array()[i];
            }
            int *r = new int[i1->get_size()];
            int my_carry = 0;
            for (int i = 0; i < i1->get_size(); i++)
            {
                int currentdigit = 0;
                currentdigit = currentdigit + my_carry;
                currentdigit = currentdigit + p[i];

                if (i < i2->get_size())
                {
                    currentdigit = currentdigit - q[i];
                }

                if (currentdigit < 0)
                {
                    currentdigit = currentdigit + 10;
                    my_carry = -1;
                }
                else
                {
                    my_carry = 0;
                }
                r[i] = currentdigit;
            }
            int forward_zero = 0;
            int i = i1->get_size()-1;
            // cout<<r[0]<<
            while (i >= 0 && r[i] == 0)
            {
                i--;
                forward_zero++;
            }
            if (forward_zero == i1->get_size())
            {
                UnlimitedInt *ans = new UnlimitedInt();
                return ans;
            }
            int *s = new int[i1->get_size() - forward_zero];
            for (int i = 0; i < i1->get_size() - forward_zero; i++)
            {
                s[i] = r[i];
            }

            UnlimitedInt *ans = new UnlimitedInt(s, i1->get_size() - forward_zero, 1, i1->get_size() - forward_zero);
            return ans;
        }
        else
        {
            int *p = new int[i1->get_size()];
            int *q = new int[i2->get_size()];
            for (int i = 0; i < i1->get_size(); i++)
            {
                p[i] = i1->get_array()[i];
            }
            for (int i = 0; i < i2->get_size(); i++)
            {
                q[i] = i2->get_array()[i];
            }
            int *r = new int[i2->get_size()];
            int my_carry = 0;
            for (int i = 0; i < i2->get_size(); i++)
            {
                int currentdigit = 0;
                currentdigit = currentdigit + my_carry;
                currentdigit = currentdigit + q[i];

                if (i < i1->get_size())
                {
                    currentdigit = currentdigit - p[i];
                }

                if (currentdigit < 0)
                {
                    currentdigit = currentdigit + 10;
                    my_carry = -1;
                }
                else
                {
                    my_carry = 0;
                }
                r[i] = currentdigit;
            }
            int forward_zero = 0;
            int i = i2->get_size()-1;
            while (i >= 0 && r[i] == 0)
            {
                i--;
                forward_zero++;
            }
            if (forward_zero == i2->get_size())
            {
                UnlimitedInt *ans = new UnlimitedInt();
                return ans;
            }
            int *s = new int[i2->get_size() - forward_zero];
            for (int i = 0; i < i2->get_size() - forward_zero; i++)
            {
                s[i] = r[i];
            }

            UnlimitedInt *ans = new UnlimitedInt(s, i2->get_size() - forward_zero, -1, i2->get_size() - forward_zero);
            return ans;
        }
    }
}

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *neg_i2 = new UnlimitedInt(*i2);
    neg_i2->sign *= -1;
    UnlimitedInt *result = add(i1, neg_i2);
    delete neg_i2;
    return result;
}
UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{

    if (i1->to_string() == "0" || i2->to_string() == "0")
    {
        UnlimitedInt *ans = new UnlimitedInt();
        return ans;
    }
    int *p = new int[i1->get_size()];
    int *q = new int[i2->get_size()];
    for (int i = 0; i < i1->get_size(); i++)
    {
        p[i] = i1->get_array()[i];
    }
    for (int i = 0; i < i2->get_size(); i++)
    {
        q[i] = i2->get_array()[i];
    }
    int *r = new int[i1->get_size() + i2->get_size()];
    for (int set_zero = 0; set_zero < i1->get_size() + i2->get_size(); set_zero++)
    {
        r[set_zero] = 0;
    }

    for (int num2dig = 0; num2dig < i2->get_size(); num2dig++)
    {
        int my_carry = 0;
        for (int num1dig = 0; num1dig < i1->get_size(); num1dig++)
        {
            int updation = r[num1dig + num2dig];
            updation = updation + p[num1dig] * q[num2dig] + my_carry;
            my_carry = updation / 10;
            updation = updation % 10;
            r[num1dig+num2dig] = updation ;
        }
        r[i1->get_size() + num2dig] += my_carry;
    }
    
    int forward_zero = 0;
    int i = i2->get_size() + i1->get_size() -1;
    while (i >= 0 && r[i] == 0)
    {
        i--;
        forward_zero++;
    }
    if (forward_zero == i2->get_size() + i1->get_size())
    {
        UnlimitedInt *ans = new UnlimitedInt();
        return ans;
    }
    int *s = new int[i2->get_size() + i1->get_size() - forward_zero];
    for (int i = 0; i < i2->get_size() + i1->get_size() - forward_zero; i++)
    {
        s[i] = r[i];
    }

    UnlimitedInt *ans = new UnlimitedInt(s, i2->get_size() + i1->get_size() - forward_zero, i1->get_sign() * i2->get_sign(), i2->get_size() + i1->get_size() - forward_zero);
    return ans;
}
UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_size() == 1)
    {
        if (i1->to_string()[0] == '0')
        {
            UnlimitedInt *ans = new UnlimitedInt();
            return ans;
        }
    }
    int *p = new int[i1->get_size()];
    int *q = new int[i2->get_size()];
    for (int i = 0; i < i1->get_size(); i++)
    {
        p[i] = i1->get_array()[i1->get_size() - i - 1];
    }
    for (int i = 0; i < i2->get_size(); i++)
    {
        q[i] = i2->get_array()[i2->get_size() - i - 1];
    }
    UnlimitedInt *divisor = new UnlimitedInt(i2->to_string());
    UnlimitedInt *dividend = new UnlimitedInt();
    UnlimitedInt *number10 = new UnlimitedInt(10);
    string quotient = "" ;

    for (int i = 0; i < i1->get_size(); i++)
    {
        UnlimitedInt *temp = UnlimitedInt::mul(dividend, number10);
        UnlimitedInt *temp1 = UnlimitedInt::add(temp, new UnlimitedInt(p[i]));
            int j ;
        for(j = 1; j<=10 ; j++)
        {
            if(!comparer(temp1 , UnlimitedInt::mul(divisor , new UnlimitedInt(j))))
            {
                
                break ;
            }
        }
        j--;
        quotient.push_back((char)(j+'0'));
        delete dividend;
        dividend = UnlimitedInt::sub(temp1 ,UnlimitedInt::mul(divisor , new UnlimitedInt(j)));
        delete temp1;
        delete temp;
    }
    int forward_zero = 0;
    int i = 0 ;
    while(i<quotient.size() && quotient[i] == '0')
    {
        i++;
        forward_zero++;
    }
    if(forward_zero == quotient.size())
    {
        quotient = "0";
    }
    else
    {
        quotient =quotient.substr(forward_zero) ;
    }
    if(i1->get_sign() == i2->get_sign())
    {
        return new UnlimitedInt(quotient) ;
    }
    else
    {
        if(quotient == "0")
        {
            return new UnlimitedInt(-1) ;
        }
        quotient = '-' + quotient ;
        UnlimitedInt* temp = new UnlimitedInt(quotient) ;
        UnlimitedInt* temp1 = UnlimitedInt :: mul(temp , i2) ;
        if(temp1->to_string() == i1->to_string())
        {
            return temp ;
        }
        else
        {
            UnlimitedInt* temp2 = UnlimitedInt::sub(temp , new UnlimitedInt(1));
            return temp2;  
        }
    }
}
UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *result;
    UnlimitedInt *result1 = div(i1, i2);
    UnlimitedInt *result2 = mul(result1, i2);
    UnlimitedInt *result3 = sub(i1, result2);
    // delete result1;
    // delete result2;
    return result3;
}
string UnlimitedInt::to_string()
{
    string res;
    if (sign == 1)
    {
        res = "";
    }
    else
    {
        res = "-";
    }
    for (int i = 0; i < size; i++)
    {
        res = res + std::to_string(unlimited_int[size-i-1]);
    }
    return res;
}