// Nomes: Victor Pereira Moura e Vinicius Cruz Menezes
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

// pre: operation recebe um operador valido (^ , * , / , % , + , - )
// pos: retorna o valor de precedencia da operacao
int getPrecedence(char operation)
{
  switch (operation)
  // Avaliar a precedencia de caractereNoTopoDaPilha
  {
  case '^':
    return 2;
  case '*':
  case '/':
  case '%':
    return 1;
    break;
  default:
    return 0;
    break;
  }
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
  string expressaoInfix = this->getInfix();
  for (size_t position = 0; position < expressaoInfix.length(); position++)
  // Percorrer por todos os caracteres da expressao;
  {
    char caractereAtual = expressaoInfix[position]; // caractereAtual eh o caractere na posiçao 'i' da expressaoInfix
    if (isdigit(caractereAtual))
    // Se o caractere for um operando, transferir para a pos-fixa;
    {
      postfix += caractereAtual;
    }
    else if (caractereAtual == '(')
    // Se o caractere for um parentese esquerdo, transferir para a pilha;
    {
      if (!S.full())
      {
        S.push(caractereAtual);
      }
      else
      {
        abort();
      }
    }
    else if (caractereAtual == ')')
    // Se o caractere eh um parentese direito, retirar os caracteres da pilha e transferi-los para posfixa ate encontrar um parentese esquerdo. Retirar o parentese esquerdo da pilha e descarta-lo.
    {
      while (!S.empty())
      // Remover todos os itens da pilha ateh encontrar um parentese esquerdo
      {
        char caracterePilha;
        S.pop(caracterePilha); // caracterePilha eh o ultimo caractere removido da pilha
        if (caracterePilha == '(')
        // SE caracterePilha for parentese esquerdo, ENTÃO parar e descartar.
        {
          break;
        }
        postfix += caracterePilha;
      }
    }
    else if (caractereAtual == '^' || caractereAtual == '%' || caractereAtual == '+' || caractereAtual == '-' || caractereAtual == '*' || caractereAtual == '/')
    // SE for operador, transferir para a pilha
    {
      while (!S.empty()) // Repetir enquanto houver itens na pilha
      {
        char caractereTopo;
        S.getTop(caractereTopo); // caractereTopo eh elemento no topo da pilha.

        // Variaveis que armazenam a precedencia de caractereTopo e de caractereAtual, respectivamente.
        int precedenciaCaractereTopo = getPrecedence(caractereTopo);
        int precedenciaCaractereAtual = getPrecedence(caractereAtual);

        if (precedenciaCaractereTopo < precedenciaCaractereAtual || caractereTopo == '(')
        // SE precedencia de t for menor que a de Ui OU t for parentese esquerdo, ENTAO parada
        {
          break;
        }
        // SENAO, ENTAO transferir da pilha para a pos-fixa
        S.pop(caractereTopo);
        postfix += caractereTopo;
      }
      if (!S.full())
      // Inserir caractereAtual na pilha
      {
        S.push(caractereAtual);
      }
      else
      {
        abort();
      }
    }
  }
  // Transferir os caracteres restantes da pilha para o postfix
  while (!S.empty())
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

  for (size_t position = 0; position < postfix.length(); position++)
  // Percorrer a expressao postfix
  {
    char caractereAtual = postfix[position];
    if (isdigit(caractereAtual))
    // SE for um operando, converter para inteiro e transferir para a pilha
    {
      int caractereAtualPostFixInteiro = caractereAtual - '0';
      if (!S.full())
      {
        S.push(caractereAtualPostFixInteiro);
      }
      else
      {
        abort();
      }
    }
    else if (caractereAtual == '^' || caractereAtual == '%' || caractereAtual == '+' || caractereAtual == '-' || caractereAtual == '*' || caractereAtual == '/')
    // SENAO (SE for um operador), retirar da pilha os dois ultimos operandos, realizar a operaçao e enviar para a pilha o resultado.
    {
      int operand1;
      int operand2;
      // Retirar da pilha os dois ultimos operandos (Last In, First Out)
      if (!S.empty())
      {
        S.pop(operand2);
        if (!S.empty())
        {
          S.pop(operand1);
          // Calcular soma, subtraçao, multiplicaçao, dividisao, potencia, ou resto da divisao dos dois valores dependendo do operador encontrado, e inserir o resultado na pilha.
          if (caractereAtual == '+')
          {
            S.push(operand1 + operand2);
          }
          else if (caractereAtual == '-')
          {
            S.push(operand1 - operand2);
          }
          else if (caractereAtual == '*')
          {
            S.push(operand1 * operand2);
          }
          else if (caractereAtual == '/')
          {
            S.push(operand1 / operand2);
          }
          else if (caractereAtual == '^')
          // Se o operando for expoente, realizar o calculo a partir do bloco abaixo:
          {
            int tempValue = 1; // x^0 = 1
            for (int vez = 1; vez <= operand2; vez++)
            // Multiplicar tempValue por operand1, operand2 vezes (ex: 2^3 = 1 * (2*2*2) = 8). Se operand2 = 0, o loop nao sera executado, e tempValue sera 1.
            {
              tempValue *= operand1;
            }
            // Ao final, transferir resultado (tempValue) para a pilha
            S.push(tempValue);
          }
          else
          // (%)
          {
            S.push(operand1 % operand2);
          }
        }
      }
    }
    else
    {
      cout << "Caractere '" << caractereAtual << "' invalido. \n";
      value = 0;
    }
  }
  // Por fim, transferir o resultado da expressao para value
  if (!S.empty())
  {
    S.pop(value);
  }
}
