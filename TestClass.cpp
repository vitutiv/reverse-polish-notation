#include "Expression.cpp"
int main()
{
     //Expression e("2 + 3");
     //string exp;
     //cout << "Insira a expressao abaixo: ";
     //cin >> exp;
     Expression e("3/2/2");
     //Expression e("4 * (2 + 3)");
     cout << "INFIX..: |" << e.getInfix() << "|"
          << endl;
     cout << "POSTFIX..: |" << e.getPostfix() << "|"
          << endl;
     cout << "VALUE..: " << e.getValue()
          << endl;
}