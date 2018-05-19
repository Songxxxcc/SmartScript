#include "runtime.hpp"
#include "../ssconfig.hpp"

#include <iostream>
#include <deque>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>
#include <sstream>
using namespace std;

struct Var{
		unsigned int type;
		unsigned long addr;
};

struct Block{
		deque<long> ints;
		deque<double> floats;
		unordered_map<string,Var> vars;
		bool is_pass = false;
};

struct Runtime_Vars{
		deque<Block> blocks;
		Runtime_Vars(){
				blocks.push_front(Block());
		}
};

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
}

Runtime::~Runtime(){
		delete data;
}

void Api_Call(const std::string&, istream&);

void Runtime::Run_Order(const string& order){
		stringstream sorder(order);
		string word;
		sorder >> word;
		if(word == ":"){
				data->blocks.push_front(Block());
		} else if(word == ";"){
				data->blocks.pop_front();
		} else if(data->blocks.front().is_pass){
				return;
		}else if(word == "OnWindows:"){
				data->blocks.push_front(Block());
#ifndef _WIN32
				data->blocks.front().is_pass = true;
#endif
		} else if(word == "OnLinux:"){
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
		}
		else if(word == ";;"){
				exit(0);
		}
}

void Api_Call(const std::string& name,istream& in){
		if(name == "print_api_version"){
				cout << "Api Version: " << SS_STD ;
		} else {
				throw CodeException( "Cannot find API: "+name,ErrorsNumber::UNKONW_API); 
		}
}

