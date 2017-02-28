#ifndef EXPR_H
#define EXPR_H
#inlcude<list>
#include<string>


using namespace std;
typedef struct expr_val* exp;
struct expr_val
{
	char* str;
	int num;
    float num;
};

extern exp mk_int(int item);
extern exp mk_str(char* item);
extern exp mk_float(float item);
class class_signature{}
class class_body{}
class program
{
protected:
list<quack_class*> classes*;
list<statement *> statements*;
public:
program(list<quack_class*> *c,list<statement*> *s);
void evaluate();
}
class quack_class 
{
protected:  
 class_signature* sign;
   class_body* body;
public:
quack_class(class_signature* s,class_body* b);
}

class  statement
{

}

class expr_node
{
protected:
	
public:
	expr();
	virtual  expr_val evaluate() = 0;
}

class operator_node : public expr_node
{
protected:

public:
	virtual expr_val evaluate() = 0;

}

class plus_node: public operator_node
{
	public:
		plus_node(expr_node *l,expr_node* r);

}
class minus_node: public operator_node
{
public:
	minus_node(expr_node *l,expr_node* r);

}

class times_node: public operator_node
{
public:
	times_node(expr_node *l,expr_node* r);

}

class divide_node: public operator_node
{
public:
	divide_node(expr_node *l,expr_node* r);

}

class int_node: public expr_node
{
	protected:
		int num;
	public:
		int_node(int n);
		int evaluate();
}
class str_node:public expr_node
{
protected:
	string val;
public:
	str_node(char* s);
	string evaluate();
}

#endif
