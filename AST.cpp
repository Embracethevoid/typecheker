#include"AST.h"
using namespace std;
node::node()
{

}


node::~node()
{ 

}
program::program(basic_classes* cls,statements* sts)//:clses(c.value()),stmts(s.value())
{
	cs = cls->value();
	ss = sts->value();
	//class_inherit_issue();	
	//class_method_inherit();

}

basic_class::basic_class()
{
	m_name = "Obj";
}

extern auto Obj = new basic_class();

void program::class_inherit_issue()
{
	unordered_map<string,string> classtable;
	for(auto c: cs)
	{
		classtable[c->name()] = c->parent();
		//cout<<c.name()<<" "<<c.parent()<<endl;
	}
	for(auto c:cs)
	{
		auto temp = c->name();
		unordered_set<string> temptype;
		while(temp != string("Obj"))
		{
			temptype.insert(temp);
			temp = classtable[temp];
			if( classtable.find(temp) == classtable.end() && temp != "Obj")
			{
				cerr<<"illegal inherit from "<<temp<<endl;
				return;
			}
			if (temptype.find(temp) != temptype.end())
			{
				
				cerr<< "circle in class inherit:";
				auto mark = classtable[temp];
				cout<<temp<<"->";
				while (mark != temp)
				{
					cout<<mark<<"->";
					mark = classtable[mark];
				}
				cout<<mark<<endl;
				exit(-1);
				//return;
			}
			
			
		}
		if(c->parent() == "Obj")
		{
			c->reference  = Obj;
		}
		else
		{
			for(auto p:cs)
			{
				if(p->name() == c->parent())
				{
					c->reference = p;
				}
			}
		}

	}
}

void program::class_method_inherit()
{
	for(auto c:cs)
	{
		auto temp = c;
		while(temp->reference != Obj)
		{
			for(auto i:temp->reference->m_methods)
			{
				bool flag = 0;
				for(auto m: c->m_methods)
				{
					if(i->name() == m->name())
					{
						flag = 1;
						//detect the overwrite 
						break;
					}
				}
				if(flag)
				{
					c->m_inherit_methods.push_back(i);
				}
			}
			temp = temp->reference;
		}
	}

}

program::~program()
{

}


basic_class::basic_class(class_sig* s, class_body* b)/*:m_sign(s),m_body(b)*/
{
	m_name = s->name();
	m_parent = s->parent();
	m_para = s->para();
	m_statements = b->class_statements();
	m_methods = b->class_methods();
	// delete s;
}
string basic_class::name()
{
	return m_name;
}

string basic_class::parent()
{
	return m_parent;
}
vector<Para> basic_class::para()
{
	return m_para;
}
basic_class::~basic_class()
{

}
// std::vector<basic_class> classtable()
// {
// 	return std::vector<basic_class>;
// }

class_sig::class_sig(char* s,formal_args* f,extend* e)/*:m_name(std::string(s)),m_f_args(f),m_parent(e.value())*/
{
	m_para = f->value();
	// delete f;
	m_name = string(s);
	m_parent = e->value();
	if(m_name == m_parent)
	{
		cerr<<"illegal inherit"<<endl;
		//exit(-1);
		return ;
	}
	// delete e;
	
}

class_sig::class_sig(char* s,formal_args* f)/*:m_name(std::string(s)),m_f_args(f)*/
{
	m_para = f->value();
	// delete f;
	m_name = string(s);
	m_parent = string("Obj");
}
std::string class_sig::name()
{
	return m_name;
}

std::string class_sig::parent()
{
	return m_parent;
}

vector<Para> class_sig::para()
{
	return m_para;
}

class_sig::~class_sig()
{

}



extend::extend(char* i):m_value(std::string(i))
{

}
extend::~extend()
{

}

string extend::value()
{
	return m_value;
}

ident::ident(char* s)/*:m_value(std::string(s))*/
{

}


ident::~ident()
{

}
// std::string ident::value()
// {
// 	return m_value;
// }

class_body::class_body(statements* s,methods* m)
{
	m_statements = s->value();
	m_methods = m->value();

}

std::vector<statement*> class_body::class_statements()
{
	return m_statements;
}
std::vector<method*> class_body::class_methods()
{
	return m_methods;
}


class_body::~class_body()
{

}

statements::statements()
{

}

statements::statements(statements* ss,statement* s)
{
	m_value = ss->value();
	m_value.push_back(s);
	delete ss;

}
statements::~statements()
{

}


std::vector<statement*> statements::value()
{
	return m_value;
}


methods::methods()
{

}

methods::methods(methods* ms,method* m)/*:m_value(m)*/
{
	m_value = ms->value();
	for(auto b:m_value)
	{
		// cout<<m->name()<< b.name()<<endl;
		if (m->name() == b->name())
		{
			// cout<<"here am i"<<endl;
			cerr<<"function \""<< b->name()<<"\" cannot be redefined"<<endl;
			exit(-1);
			//return;
		}
	}
	m_value.push_back(m);
	// delete m;

}
methods::~methods()
{

}

std::vector<method*> methods::value()
{
	return m_value;
}

statement::statement()
{

}

statement::~statement()
{

}
method::method(char* s1,formal_args* f,char* s2,statements* s):m_name(string(s1)),m_type(string(s2))//:m_name(string(s1)),/*:name(std::string(s))*/
{
	m_para = f->value();
	methodstatements = s->value();
	//cout<<m_name<<m_type<<endl;
}

method::method(char* s1,formal_args* f,statements* s):m_name(string(s1)),m_type(string("Nothing"))
{
	m_para = f->value();
	methodstatements = s->value();
}

// std::unordered_map<std::string,std::string> method::variables()
// {
// 	return m_variables;
// }

string method::name()
{
	return m_name;
}
string method::type()
{
	return m_type;
}
vector<Para> method::para()
{
	return m_para;
}
method::~method()
{

}

basic_classes::basic_classes()
{

}
basic_classes::basic_classes(basic_classes* bcs, basic_class* bc)
{
	m_value = bcs->value();
	delete bcs;
	for(int i = 0 ;i<m_value.size();++i)
	{
		if (bc->name() == m_value[i]->name())
		{
			cerr<<"class \""<< bc->name()<<"\" cannot be redefined"<<endl;
			//exit(-1);
			return ;
		}
	}
	m_value.push_back(bc);
	// delete bc;


}

basic_classes::~basic_classes()
{

}

std::vector<basic_class*> basic_classes::value()
{
	return m_value;
}

formal_args_first::formal_args_first(char* s1,char* s2)
{
	//printf("%s %s",&s1,&s2);
	m_value.name = string(s1);
	m_value.type = string(s2);


}

vector<Para> formal_args::value()
{
	return m_value;
}
formal_args_first::~formal_args_first()
{

}
Para formal_args_first::value()
{
	return m_value;
}

// std::string formal_args_first::value()
// {
// 	return m_value1;
// }

formal_args_ident::formal_args_ident(char*s1,char* s2)
{
	//printf("%s %s",s1,s2);
	m_value.name = string(s1);
	m_value.type = string(s2);
}

formal_args_ident::~formal_args_ident()
{

}
Para formal_args_ident::value()
{
	return m_value;
}

formal_args_idents::formal_args_idents()
{

}

formal_args_idents::formal_args_idents(formal_args_idents* is,formal_args_ident* i)
{
	m_value = is->value();
	m_value.push_back(i->value());
	delete is;
}

formal_args_idents::~formal_args_idents()
{

}

vector<Para> formal_args_idents::value()
{
	return m_value;
}


formal_args::~formal_args()
{

}

formal_args::formal_args(formal_args_first* f,formal_args_idents* i )
{
	m_value = i->value();
	m_value.insert(m_value.begin(),f->value());
	// for(int i = 0; i <m_value.size();++i)
	// {
	// 	cout<<m_value[i].name<<":"<<m_value[i].type<<" ";
	// }
	// cout<<endl;
}
formal_args::formal_args()
{

}


// formal_args::formal_args(formal_args f)
// {
// 	m_value = f.value();
// }


r_expr::r_expr()
{

}

r_expr::~r_expr()
{

}


make_int::make_int(int i)
{
	// char* to integer
	m_type = "INT";
}

make_int::~make_int()
{

}

// int make_int::value()
// {
// 	return m_value;
// }


make_str::make_str(char*s)/*:m_value(std::string(s))*/
{
	m_type = "STR";
}


make_str::~make_str()
{

}

// std::string make_str::value()
// {
// 	return m_value;
// }

bin_operator::bin_operator(r_expr* e1,char *s,r_expr* e2)
{
	// if(s == "PLUS")
	// {
		
	// }
	// else if( s == "MINUS")
	// {
		
	// }
	// else if( s == "TIMES")
	// {
		
	// }
	// else if( s == "DIVIDE")
	// {
		
	// }
	// else if( s == "ATMOST")
	// {
		
	// }
	// else if( s == "ATLEAST")
	// {
		
	// }
	// else if( s == "MORE")
	// {
		
	// }
	// else if( s == "LESS")
	// {
		
	// }
	// else if( s == "EQUALS")
	// {
		
	// }
	// else if( s == "GETS")
	// {
		
	// }
	// else if( s == "AND")
	// {
		
	// }
	// else if( s == "OR")
	// {
		
	// }
	// else
	// {

	// }
	b = {e1,string(s),e2};
	tag = "bin_oper";
	
}

bin_operator::~bin_operator()
{

}

negative_operator::negative_operator(r_expr* e)
{
	// do the neg of the value
		s = {string("NEG"),e};
	tag = "single_oper";
}

negative_operator::~negative_operator()
{

}

not_operator::not_operator(r_expr* e)
{
	// do the not operation
	s = {string("NOT"),e};
	tag = "single_oper";
}

not_operator::~not_operator()
{

}




r_exprs::r_exprs()
{

}


r_exprs::r_exprs(r_exprs* es,r_expr* e)
{
	m_value = es->value();
	m_value.push_back(e);
}

vector<r_expr*> r_exprs::value()
{
	return m_value;
}

r_exprs::~r_exprs()
{

}


actual_args::actual_args()
{

}

actual_args::actual_args(r_expr* exp,r_exprs* exps)
{
	m_value = exps->m_value;
	m_value.insert(m_value.begin(),exp);
}
actual_args::~actual_args()
{

}


function_call::function_call(r_expr* e, char* s, actual_args* a)
{
	f = {e,string(s),a};
	tag = string("function_call");
	
}


function_call::function_call(char* s, actual_args* a)
{
	c = {string(s),a};
	tag = string("class_call");
}

// function_call::function_call(expr* e, char* s, actual_args a)
// {

// }
// function_call::function_call(char* s, actual_args a)
// {

// }


function_call::~function_call()
{

}


make_ident::make_ident(char* s)
{
	m_name = string(s);
	identname = string(s);
	tag = string("IDENT");
	//isleft  =b;
}

make_ident::make_ident(r_expr* e,char* s2)
{
	m_name = string(s2);
	identname = string(s2);
	tag = string("IDENTINMEMBER");
	identparent = e;
	//isleft = b;
}


make_ident::~make_ident()
{

}
string make_ident::name()
{
	return m_name;
}

element_call::element_call(r_expr* e,char* s)
{

}
element_call::~element_call()
{

}

stmt::stmt()
{

}

stmt::~stmt()
{

}


elif::elif(r_expr* e, statements* s)
{
	m_value = branch{e,s};
}

branch elif::value()
{
	return m_value;
}

elif::~elif()
{

}



elifs::elifs()
{

}

elifs::elifs(elifs* es,elif* e)
{
	m_value = es->value();
	m_value.push_back(e);
	delete es;
}

vector<elif*> elifs::value()
{
	return m_value;
}
elifs::~elifs()
{

}
//ifstmt(r_expr* exp,std::vector<statement*> s1,elifs* elfs,std::vector<statement*> s2);
//ifstmt(r_expr* exp,std::vector<statement*> s,elifs* elfs);
ifstmt::ifstmt(r_expr* exp,statements* s1,elifs* elfs,statements* s2) //with else
{
	tag = string("IFELSE");
	//cout<< "metifstmt"<<endl;
	branches.push_back({exp,s1});
	//branches.insert(elfs->value().begin(),elfs->value().end(),branches.begin());
	for(auto e : elfs->value())
	{
		branches.push_back(e->value());
	}
	elsestatements = s2;
}

ifstmt::ifstmt(r_expr* exp,statements* s,elifs* elfs) //without else
{
	tag = string("IF");
	branches.push_back({exp,s});
	//branches.insert(elfs->value().begin(),elfs->value().end(),branches.begin());
	for(auto e : elfs->value())
	{
		branches.push_back(e->value());
	}
}

ifstmt::~ifstmt()
{

}
whilestmt::whilestmt(r_expr* exp,statements* s)
{
	tag = string("WHILE");
	whilestatement = branch{exp,s};
}

whilestmt::~whilestmt()
{

}

expstmt::expstmt(r_expr* l, r_expr* r)
{
	g_value = {l,r};
	tag = string("GETVALUE");
}

expstmt::expstmt(r_expr* l ,char* s,r_expr* r)
{
	g_value_m = {l,string(s),r};
	tag = string("GETVALUEMEMBER");
}

expstmt::expstmt( r_expr* r)
{
	exp =r;
}
expstmt::~expstmt()
{

}

returnstmt::returnstmt()
{
	tag = string("RETURNNULL");
}

returnstmt::returnstmt(r_expr* e)
{
	tag = string("RETURN");
	exp = e;
	//returntype = e->m_type;
}

returnstmt::~returnstmt()
{

}