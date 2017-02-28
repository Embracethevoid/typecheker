#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "expr.h"

program::program(list<quack_class*> *c,list<statement*> *s) classes(c),statements(s)s
{

}

void program::evaluate()
{

}


quack_class(class_signature* s,class_body* b),sign(s),body(b),
{
}


str_node::str_node(char* s),val(string(s))
{
}

string str_node::evaluate()
{
	return val; 
}


int_node::int_node(int n),num(n)
{

}
int int_node::evaluate()
{
	return num;
}