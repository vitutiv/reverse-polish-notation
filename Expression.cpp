#include "Expression.h"
using namespace std;

// pre: nenhuma
// pos: Dada expressao infixa s, converte-a na notacao posfixa e encontra seu valor
Expression::Expression(string s)
{
  setInfix(s);
}

// pre: nenhuma
// pos: Dada expressao infixa s, converte-a na notacao posfixa e encontra seu valor
void Expression::setInfix(string s)
{
  infix = s;
  infixToPostfix();
  evalPostfix();
}

// pre: objeto criado
// pos: retorna a expressao na notacao infixa
string Expression::getInfix()
{
  return infix;
}

// pre: objeto criado
// pos: retorna a expressao na notacao posfixa (RPN)
string Expression::getPostfix()
{
  return postfix;
}

// pre: objeto criado
// pos: retorna o valor da expressao na notacao posfixa (RPN)
int Expression::getValue()
{
  return value;
}

// pre: infix contem uma expressao aritmetica valida, contendo operadores e digitos na notacao infixa
// pos: postfix contem a mesma expressao dada por infix, convertida na notacao pos-fixada (RPN)
void Expression::infixToPostfix()
{ // Implemente o Algoritmo 1 aqui
  // Ao final, o campo postfix do objeto deve conter a expressao na notacao RPN
  // Remova ou altere qualquer linha seguinte, de acordo com a necessidade do Algoritmo 1
  postfix = "";
  // Para declarar uma pilha usando templates, associe o tipo de dado colocado na mesma
  Stack<char> S; // um pilha de caracteres
  Stack<int> Q;  // um pilha de inteiros
  string expression = this->getInfix();
  for (int i = 0; i < expression.length(); i++)
  // Percorrer por todos os caracteres da expressão;
  {
    char charI = expression[i]; //charI eh o caractere na posição 'i' da expressão
    if (isdigit(charI))
    // Se o caractere for um operando, transferir para a pós-fixa;
    {
      postfix += charI;
    }
    else if (charI == '(')
    // Se o caractere for um parêntese esquerdo, transferir para a pilha;
    {
      S.push(charI);
    }
    else if (charI == ')')
    // Se o caractere eh um parêntese direito, retire caracteres da pilha e transfira-os para posfixa ateh encontrar um parêntese esquerdo. Retire o parêntese esquerdo da pilha e descarte - o.
    {
      while (S.size() > 0)
      // Remover todos os itens da pilha
      {
        char charStack; //charStack eh o último caractere removido da pilha
        S.pop(charStack);
        if (charStack == '(')
        // Se for parêntese esquerdo, descartar e parar loop
        {
          break;
        }
        else
        // Senão, transferir charStack para a pos-fixa
        {
          postfix += charStack;
        }
      }
    }
    else if (charI == '+' || charI == '-' || charI == '*' || charI == '/')
    // Se for operador, transferir para a pilha
    {
      S.push(charI);
    }
    else if (charI == ' ')
    // Ignorar espaços
    {
    }
    else
    // Caractere invalido encontrado
    {
      cout << "EXITEM CARACTERES INVALIDOS NA EXPRESSÃO!";
      postfix = "";
      break;
    }
  }
  //Enquanto houver simbolos restantes na pilha, transferi-los para pós-fixa
  while (S.size() > 0)
  {
    char charX;
    S.pop(charX);
    postfix += charX;
  }
}

// pre: postfix contem a expressao na notacao posfixa
// pos: retorna o valor da expressao, utilzando Algoritmo 2
void Expression::evalPostfix()
{ // Implemente o Algoritmo 2 aqui
  // Ao final, o campo value do objeto deve conter o valor da expressao postfix
  // Remova ou altere qualquer linha seguinte, de acordo com a necessidade do Algoritmo 2
  // caso postfix nao tenha caracteres (string vazia) ou apenas espacos, retorne zero
  value = 0;
  // Para declarar uma pilha usando templates, associe o tipo de dado colocado na mesma
  Stack<int> S; // um pilha de inteiros
  for (int i = 0; i < postfix.length(); i++)
  // Percorrer a expressão postfix
  {
    char charI = postfix[i];
    if (isdigit(charI))
    // Se for um operando, converter para inteiro e transferir para a pilha
    {
      int charToInt = charI - '0';
      S.push(charToInt);
    }
    else
    // Senão (se for um operador), retirar da pilha os dois últimos operandos, realizar a operação e enviar para a pilha o resultado.
    {

      // retirar da pilha os dois últimos operandos (Last In, First Out)
      int operand1, operand2;
      S.pop(operand2);
      S.pop(operand1);

      if (charI == '+')
      // Somar, subtrair, multiplicar ou dividir os dois valores dependendo do operador encontrado
      {
        S.push(operand1 + operand2);
      }
      else if (charI == '-')
      {
        S.push(operand1 - operand2);
      }
      else if (charI == '*')
      {
        S.push(operand1 * operand2);
      }
      else if (charI == '/')
      {
        S.push(operand1 / operand2);
      }
    }
  }
  // Por fim, retirar da pilha o resultado da expressão
  S.pop(value);
}
