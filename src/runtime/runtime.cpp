#include "runtime.hpp"
#include "../ssconfig.hpp"
#include "../api/api.hpp"
#include <iostream>
#include <deque>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>
#include <sstream>
using namespace std;




CodeException::CodeException(const std::string& a,enum ErrorsNumber e){
		about = a;
		err = e;
}

enum ErrorsNumber CodeException::Get_Errors_Number() const{
		return err;
}

string CodeException::Show_Exception_Text() const{
		return about;
}

Runtime::Runtime(){
		data = new Runtime_Vars();
		nil.type = Type::NIL;
}

Runtime::~Runtime(){
		delete data;
}

void Api_Call(const std::string&, istream&);

void Runtime::Run_Order(const string& order){
		stringstream sorder(order);
		string word;
		sorder >> word;
		if(word == "{"){
				data->blocks.push_front(Block());
		} else if(word == "}"){
				data->blocks.pop_front();
		} else if(data->blocks.front().is_pass){
				return;
		}else if(word == "OnWindows{"){
				data->blocks.push_front(Block());
#ifndef _WIN32
				data->blocks.front().is_pass = true;
#endif
		} else if(word == "OnLinux{"){
				data->blocks.push_front(Block());
#ifndef linux
				data->blocks.front().is_pass = true;
#endif
		} else if(word == "$"){
				getline(sorder,word);
				system(word.c_str());
		} else if(word == "call"){
				sorder >> word;
				Api_Call(word,sorder);
		} else if(word == ":"){
				string line;
				sorder >> line;
				if(line.front() == '$'){
						Block* block_p;
						Var v = Get_Var(string(line.begin()+1,line.end()),&block_p);
						if(v.type == Type::NIL){
								// DON'T ANY DO
						}
						else if(v.type == Type::INT){
								cout << block_p->ints[v.addr];
						} else if(v.type == Type::FLOAT){
								cout << block_p->floats[v.addr];
						} else if(v.type == Type::STRING){
								cout << block_p->strings[v.addr];
						}
						return;
				}
				cout << line;
				getline(sorder,line);
				cout << line;
		} else if(word == ":;"){
				cout << endl;
		} else if(word == "int"){
				string varname;
				sorder >> varname;
				string tmp;
				sorder >> tmp;
				int default_v = 0;
				if(tmp == "="){
						sorder >> default_v;
				}
				Add_Int(varname,default_v);
		} else if(word == "float"){
				string varname;
				sorder >> varname;
				string tmp;
				sorder >> tmp;
				float default_v = 0;
				if(tmp == "="){
						sorder >> default_v;
				}
				Add_Float(varname,default_v);

		} else if(word == "string"){
				string varname;
				sorder >> varname;
				string tmp;
				sorder >> tmp;
				string default_v_str;
				string str;
				if(tmp == "="){
						sorder >> default_v_str;
						string::iterator it = default_v_str.begin(), beg;
						while(*it != '\"' && it != default_v_str.end()){
								++it;
						}
						if(it == default_v_str.end()){
								throw CodeException("NO DEFAULT STRING.", ErrorsNumber::NEED);
						}
						beg = it;
						while(*it != '\"' && it != default_v_str.end()){
								if(*it == '\\'){
										str += string(beg,it);
										++it;
								}
								++it;
						}
						str += string(beg,it);
				}
				Add_String(varname,str);
		}
		else if(word == ";;"){
				exit(0);
		}
}

void Api_Call(const std::string& name,istream& in){
		if(name == "print_api_version"){
				cout << "Api Version: " << SS_STD ;
		} else if(name == "endl"){
				cout << endl;
		}
	   	else {
				throw CodeException( "Cannot find API: "+name,ErrorsNumber::UNKONW_API); 
		}
}
