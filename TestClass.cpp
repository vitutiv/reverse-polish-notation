#include "Expression.cpp"
int main()
{
    //Expression e("2 + 3");
    //string exp;
    //cout << "Insira a expressao abaixo: ";
    //cin >> exp;
    Expression e("4-");
    //Expression e("4 * (2 + 3)");

    cout << "INFIX..: " << e.getInfix() << "\n";
    cout << "POSTFIX..: " << e.getPostfix() << "\n";
    cout << "VALUE..: " << e.getValue() << "\n";
}