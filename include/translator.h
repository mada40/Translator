#ifndef __Translator_H__
#define __Translator_H__

#include<algorithm>
#include<stdexcept>
#include "tqueue.h"
#include "tstack.h"
#include <string>
#include <limits>
#include <iostream>
#include <map>
#include <cmath>

 enum Type
 {
     LEFT_BRACKET,
     RIGHT_BRACKET,
     OPERATION,
     FUNC,
     CONST,
     VAR,
     NUMBER
 };

 static const double PI = 3.14159265359;
 static const double E =  2.71828182846;


 static bool is_operation(const std::string& str)
 {
     char c = str[0];
     return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
 }
 static bool is_func(std::string str)
 {
     for (char& c : str)
         c = tolower(c);

     return str == "sin" || str == "cos" || str == "ln";
 }

 static bool is_const(std::string str)
 {
     for (char& c : str)
         c = tolower(c);

     return str == "e" || str == "pi";
 }

 static bool is_var(const std::string& str)
 {
     for (char c : str)
         if (tolower(c) < 'a' || tolower(c) > 'z') return false;

     return true;
 }


 class Translator
 {
 private:
     std::map<std::string, double> vars;

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
             else if (is_operation(str)) type = OPERATION;
             else if (is_func(str)) type = FUNC;
             else if (is_const(str)) type = CONST;
             else if (is_var(str)) type = VAR;
             else throw std::logic_error("invalid lexema");
         }
         int priority()
         {
             if (type == FUNC) return 5;
             switch (value[0])
             {
             case '*':
             case '/':
                 return 4;
             case '%':
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

     q_lexems expr;
     void string_to_expr(std::string str)
     {
         if (str.empty())
             return;

         std::string lex = "";
         str += " ";
         for (char c : str)
         {
             if (c == ' ')
             {
                 if (lex != "")
                     expr.push(lex);
                 lex = "";
             }
             else lex += c;
         }

     }

     void infix_to_postfix()
     {
         q_lexems post;
         s_lexems stack;
         while (!expr.empty())
         {
             lexema lex = expr.front();
             expr.pop();
             switch (lex.type)
             {
             case Type::FUNC:
                 post.push(lexema("0"));
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
             case Type::CONST:
                 post.push(lex);
                 break;
             case Type::VAR:
                 post.push(lex);
                 vars.insert({ lex.value, 0.0 });
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
             auto t = stack.top().type;
             if (t != Type::OPERATION  && t != Type::FUNC)
                 throw std::logic_error("invalid expression");

             post.push(stack.top());
             stack.pop();
         }
         expr = post;
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
             else if (now.type == CONST)
             {
                 auto tmp = now.value;
                 for (char& c : tmp)
                     c = tolower(c);

                 if (tmp == "e")
                     out.push(E);
                 if (tmp == "pi")
                     out.push(PI);

             }
             else if (now.type == VAR)
             {
                 out.push(vars[now.value]);

             }
             else if (now.type == FUNC)
             {
                 if (out.size() <= 0)
                     throw std::logic_error("invalid func");


                 double b = out.top();
                 out.pop();

                 double a = out.top();
                 out.pop();

                 double c;
                 auto tmp = now.value;
                 for (char& ch : tmp)
                     ch = tolower(ch);

                 if (tmp == "sin") c = std::sin(b);
                 if (tmp == "cos") c = std::cos(b);
                 if (tmp == "ln") c = std::log(b);
                 out.push(c);
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
                     if (std::abs(b - 0.0) < std::numeric_limits<double>::epsilon())
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

     

     void set_vars(const std::map<std::string, double>& tmp)
     {
         auto ptr1 = tmp.begin();
         auto ptr2 = vars.begin();
         if (tmp.size() != vars.size())
         {
             throw std::logic_error("incorrect number of variables");
         }
         while (ptr1 != tmp.end() && ptr2 != vars.end())
         {
             if (ptr1->first != ptr2->first)
             {
                 throw std::logic_error("incorrect variable");
             }
             ++ptr1; ++ptr2;
         }

         vars = tmp;
     }

     public:

     Translator(const std::string& str)
     {
         string_to_expr(str);
     }

     double solve()
     {
         infix_to_postfix();
         return solve_post_expr(expr);
     }

     double solve(const std::map<std::string, double>& tmp)
     {
         infix_to_postfix();
         set_vars(tmp);
         return solve_post_expr(expr);
     }

 };
 




#endif
