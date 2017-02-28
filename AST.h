#ifndef AST_H
#define AST_H
#include<map>
#include<string>
#include<vector>
#include<iostream>
#include<stdio.h>
#include<unordered_map>
#include<unordered_set>
#include<stdlib.h>



// typedef struct expr_val* exp;
// struct expr_val
// {
// 	char* str;
// 	int num;
//     float num;
// };

// extern exp mk_int(int item);
// extern exp mk_str(char* item);
// extern exp mk_float(float item);

typedef struct 
{
	std::string name;
	std::string type;
}
Para;
class node
{
public:
	node();
	~node();
	//std::string type;
protected:
	//std::string type;
	//virtual void print();
	//virtual void evalutate();
};


class expr : public node
{
public:
	expr();
	~expr();
	std::string m_type;
};







class ident : public node
{
public:
	ident(char*);
	~ident();
	std::string value();
protected:
	std::string m_value;

};



class extend: public node
{
public:
	extend(char* i);
	~extend();
	std::string value();
protected:
	std::string m_value;
	//void evaluate();
};
//template <typename T>

class r_expr;
class actual_args;
typedef struct 
{
	r_expr* l;
	std::string s;
	r_expr* r;
}bin_oper;

typedef struct 
{
	std::string s;
	r_expr* e;
}single_oper;

typedef struct 
{
	r_expr* e;
	std::string s; //method name
	actual_args* p;
}f_call;
typedef struct 
{
	std::string s; //class name;
	actual_args* p;
}c_call;

class r_expr : public node//expr
{
public:
	r_expr();
	//r_expr(char*,int);
	// r_expr(expr* e);
	// r_expr(expr* e1, char* s, expr* e2);
	// r_expr(char*s,expr* e);
	~r_expr();
	std::string identname;
	std::string tag;
	std::string m_type;
	bin_oper b;
	single_oper s;
	f_call f;
	c_call c;
	r_expr* identparent;
	//T value();  not sure how to do with the type of the value
private:
	//T m_value;
};


// class l_expr:public expr
// {
// public:
// 	l_expr(char*);
// 	l_expr(expr* , char*);
// 	~l_expr();
// }

class r_exprs: public node
{
public:
	r_exprs();
	r_exprs(r_exprs* es,r_expr* e);
	~r_exprs();
	std::vector<r_expr*> value(); 
	std::vector<r_expr*> m_value; 
};

class actual_args:public node
{
public:
	actual_args(r_expr* exp , r_exprs* e);
	actual_args();
	~actual_args();
	std::vector<r_expr*> m_value;
};

class make_ident : public r_expr
{
public:
	make_ident(char* );
	make_ident(r_expr* ,char* );
	~make_ident();
	std::string name();
	std::string m_name;
	bool isleft;
};


class element_call : public r_expr
{
public:
	element_call(r_expr* ,char*);
	~element_call();
};

class function_call : public r_expr
{
public:
	function_call(r_expr* e, char* s, actual_args* a);
	function_call(char* s, actual_args* a);
	~function_call();
};


class make_int : public r_expr
{
public:
	make_int(int i);
	~make_int();
	//int value();
private:
	//int m_value;

};

class make_str:public r_expr
{public:
	make_str(char* s);
	~make_str();
//	std::string value();
private:
//	std::string m_value;

};



class bin_operator : public r_expr
{public:
	bin_operator(r_expr* e1, char*s ,r_expr* e2);
	~bin_operator();

};

class negative_operator : public r_expr
{
public:
	negative_operator(r_expr* e);
	~negative_operator();
};

class not_operator: public r_expr
{
public:
	not_operator( r_expr *e);
	~not_operator();
};







class formal_args_first : public node
{
public:
	formal_args_first(char* s1,char* s2);
	~formal_args_first();
	Para value();
private:
	Para m_value;
	
};

class formal_args_ident : public node
{
public:
	formal_args_ident(char* s1,char* s2);
	~formal_args_ident();
	Para value();
private:
	Para m_value;
};

class formal_args_idents : public node
{
public:
	formal_args_idents();
	formal_args_idents(formal_args_idents*,formal_args_ident*);
	~formal_args_idents();
	std::vector<Para> value();
	std::vector<Para> m_value;
	//std::vector<formal_args_ident> value();
};





class formal_args : public node
{
public:
	formal_args();
	//formal_args(formal_args f);
	formal_args(formal_args_first* f,formal_args_idents* i );
	~formal_args();
	std::vector<Para> value();
	std::vector<Para> m_value;
	//std::vector<std::string> value();
};
class stmt:public node
{
public:
	stmt();
	~stmt();
	std::unordered_map<std::string,std::string> m_variables;
	std::string tag;
};


class statements;
class statement; 
class ifstmt; 
class expstmt;
class returnstmt;



class method:public node
{
public:
	method(char* s1,formal_args* f,char* s2,statements* s);
	method(char* s1,formal_args* f,statements* s);
	~method();
	std::string name();
	std::string type();
	std::vector<Para> para();
	std::unordered_map<std::string,std::string> m_variables;
	std::string m_returntype;
	std::vector<statement*> methodstatements;
private:
	std::string m_type;
	std::string m_name;
	std::vector<Para> m_para;
	
	//std::unordered_map<std::string,std::string> m_variables;
};



class methods : public node
{
public:
	methods();
	methods(methods* ms,method* m);
	~methods();
	std::vector<method*> value();
	std::vector<method*> m_value;
	//std::vector<method> former;

};



typedef struct 
{
	r_expr* condition;
	statements* execution;
}branch;

typedef struct {
	r_expr* left;
	r_expr* right;
}getvalue;

typedef struct{
	r_expr* left;
	std::string member;
	r_expr* right;
}getvalue_member;

class statement : public stmt
{
public:
	statement();
	~statement();
	std::vector<branch> branches;
	statements* elsestatements;
	branch whilestatement;
	getvalue g_value;
	getvalue_member g_value_m;
	r_expr* exp;
	std::string returntype;
};

class statements : public stmt
{
public:
	statements();
	statements(statements* ss,statement* s);
	~statements();
	std::vector<statement*> value();
	std::vector<statement*> m_value;

};

class elif:public node
{
public:
	elif(r_expr* e,statements* s);
	~elif();
	branch value();
	branch m_value;
};

class elifs:public node
{
public:
	elifs();
	elifs(elifs* es,elif* e);
	~elifs();
	std::vector<elif*> value();
private:
	std::vector<elif*> m_value;
};

class class_body:public node
{
public:
	class_body(statements* s,methods* m);
	std::vector<statement*> class_statements();
	std::vector<method*> class_methods();
	~class_body();
private:

	std::vector<statement*> m_statements;
	std::vector<method*> m_methods;
	
};

class ifstmt:public statement
{
public:
	ifstmt(r_expr* exp,statements* s1,elifs* elfs,statements* s2);
	ifstmt(r_expr* exp,statements* s,elifs* elfs);
	~ifstmt();

};

class whilestmt : public statement
{
public:
	whilestmt(r_expr* exp,statements* s);
	~whilestmt();
};

class expstmt: public statement
{
public:
	expstmt(r_expr* r);
	expstmt(r_expr* l ,r_expr* r);
	expstmt(r_expr* l ,char* s,r_expr* r);
	~expstmt();
};

class returnstmt : public statement
{
public:
	returnstmt();
	returnstmt(r_expr* e);
	~returnstmt();
};


class class_sig : public node
{
public:
	class_sig(char* s,formal_args* f );
	class_sig(char* s, formal_args* f,extend* e);
	~class_sig();
	//formal_args m_f_args;
	std::string name();
	std::string parent();
	std::vector<Para> para();
protected:
	std::string m_name;
	std::string m_parent;
	std::vector<Para> m_para;
};



class basic_class:public node
{
public:
	basic_class(class_sig* s, class_body* b);
	basic_class();
	~basic_class();
	std::string name();
	std::string parent();
	std::vector<Para> para();
	//std::string m_type;
	std::string m_name;
	std::string m_parent;
	std::vector<Para> m_para;
	basic_class* reference;
	std::vector<method*> m_methods;
	std::vector<method*> m_inherit_methods;
	std::vector<statement*> m_statements;
	std::unordered_map<std::string,method*> methodtable;
	std::unordered_map<std::string,std::string> m_variables; 
	std::unordered_map<std::string,std::string> m_variables_temp; 

//protected:
	//class_sig m_sign;
	//class_body m_body;

	//std::string name;
	//std::string parent;
	//std::vector<std::string> method_names; 

};

class basic_classes : public node
{
public:
	basic_classes();
	basic_classes(basic_classes* bcs, basic_class* bc);
	~basic_classes();

	std::vector<basic_class*> value();
	std::vector<basic_class*> m_value;
};


//std::vector<basic_class> classtable();


class program : public node
{public:
	program(basic_classes* cs,statements* ss);
	~program();
	//std::map<std::string,std::string> classes;
// protected:
// private:
	std::vector<basic_class*> cs;
	std::vector<statement*> ss;
	void class_inherit_issue();
	void class_method_inherit();
	std::unordered_map<std::string,std::string> m_variables;
};

#endif