#ifndef __Translator_H__
#define __Translator_H__

#include<algorithm>
#include<stdexcept>
#include "tqueue.h"
#include "tstack.h"
#include <string>
#include <limits>

 enum Type
 {
     LEFT_BRACKET,
     RIGHT_BRACKET,
     OPERATION,
     NUMBER,
 };

 static bool isoperation(char c)
 {
     return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
 }
 struct lexema {
     Type type;
     std::string value;
     lexema() = default;
     lexema(const std::string& str)
     {
         value = str;
         if (str[0] == '(') type = LEFT_BRACKET;
         else if (str[0] == ')') type = RIGHT_BRACKET;
         else if (std::isdigit(str[0]) || str.size() >= 2 && str[0] == '-' && std::isdigit(str[1])) type = NUMBER;
         else if (isoperation(str[0])) type = OPERATION;
         else throw std::logic_error("invalid lexema");
     }
     int priority()
     {
         switch (value[0])
         {
         case '*':
         case '/':
             return 4;
         case '%' :
             return 3;
         case '+':
         case '-':
             return 2;
         case '(':
         case ')':
             return 1;
         }
         return -1;
     }
 };

 typedef TDynamicQueue<lexema> q_lexems;
 typedef TDynamicStack<lexema> s_lexems;

 q_lexems string_to_expr(std::string str)
 {
     q_lexems expr;

     if (str.empty()) 
         return expr;

     std::string lex = "";
     str += " ";
     for (char c : str)
     {
         if (c == ' ')
         {
             if(lex != "")
                 expr.push(lex);
             lex = "";
         }
         else lex += c;
     }

     return expr;

 }

 void infix_to_postfix(q_lexems& infix)
 {
     q_lexems post;
     s_lexems stack;
     while (!infix.empty())
     {
         lexema lex = infix.front();
         infix.pop();
         switch (lex.type)
         {
         case Type::OPERATION:
             while (!stack.empty() && stack.top().priority() >= lex.priority())
             {
                 post.push(stack.top());
                 stack.pop();
             }
             stack.push(lex);
             break;
         case Type::NUMBER:
             post.push(lex);
             break;
         case Type::LEFT_BRACKET:
             stack.push(lex);
             break;
         case Type::RIGHT_BRACKET:
             lex = stack.top();
             stack.pop();
             while (lex.type != Type::LEFT_BRACKET)
             {
                 if (stack.empty())
                     throw std::logic_error("invalid expression");

                 post.push(lex);

                 lex = stack.top();
                 stack.pop();
             }
             break;
         }
     }
     while (!stack.empty())
     {
         if (stack.top().type != Type::OPERATION)
             throw std::logic_error("invalid expression");

         post.push(stack.top());
         stack.pop();
     }
     infix = post;
 }

 double solve_post_expr(q_lexems postfix)
 {
     if (postfix.size() == 1)
     {
         auto front = postfix.front();
         if (front.type == NUMBER)
             return stod(front.value);
         else
             throw std::logic_error("invalid expression");
     }

     TDynamicStack< double > out;
     lexema now;
     while (!postfix.empty())
     {

         now = postfix.front();
         postfix.pop();

         if (now.type == NUMBER)
         {
             out.push(stod(now.value));
         }
         else
         {
             if (out.size() <= 1)
                 throw std::logic_error("invalid expression");

             double b = out.top();
             out.pop();

             double a = out.top();
             out.pop();

             double c;

             long long tmp_a = (long long)(a);
             long long tmp_b = (long long)(b);
             switch (now.value[0])
             {
             case '+':
                 c = a + b;
                 break;
             case '-':
                 c = a - b;
                 break;
             case '*':
                 c = a * b;
                 break;
             case '%':
                 if (std::abs(a - tmp_a) > std::numeric_limits<double>::epsilon() || std::abs(b - tmp_b) > std::numeric_limits<double>::epsilon())
                 {
                     throw std::logic_error("invalid expression");
                 }

                 c = ((tmp_a % tmp_b) + tmp_b) % tmp_b;
                 break;
             case '/':
                 if(std::abs(b - 0.0) < std::numeric_limits<double>::epsilon())
                     throw std::logic_error("invalid expression");
                 c = a / b;
                 break;
             }

             out.push(c);
         }
     }


     if (out.size() != 1)
         throw std::logic_error("invalid expression");

     return out.top();
 }

 double solve(const std::string& str)
 {
     q_lexems expr = string_to_expr(str);
     infix_to_postfix(expr);
     return solve_post_expr(expr);
 }




#endif
