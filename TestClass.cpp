#include "Expression.cpp"
int main()
{
    //Expression e("2 + 3");
    Expression e("((3 + 5 * 1) / 8) * 7");
    //Expression e("4 * (2 + 3)");

    cout << "INFIX..: " << e.getInfix() << "\n";
    cout << "POSTFIX..: " << e.getPostfix() << "\n";
    cout << "VALUE..: " << e.getValue() << "\n";
}