#include "runtime.hpp"

#include <string>
#include <deque>
using namespace std;

void Runtime::Add_Int(const string& name, long dvalue){
		if(data->blocks.front().vars.find(name) != data->blocks.front().vars.end()){
				throw CodeException("Cannot make new value.", ErrorsNumber::OTHERS);
		} else {
				pair<string, Var> var(name,Var());
				var.second.type = Type::INT;
				var.second.addr = data->blocks.front().ints.size();
				data->blocks.front().ints.push_back(dvalue);
				data->blocks.front().vars.insert(var);
		}
}

void Runtime::Add_Float(const string& name, double dvalue){
		if(data->blocks.front().vars.find(name) == data->blocks.front().vars.end()){
				throw CodeException("Cannot make new value.", ErrorsNumber::OTHERS);
		} else {
				pair<string, Var> var(name,Var());
				var.second.type = Type::FLOAT;
				var.second.addr = data->blocks.front().floats.size();
				data->blocks.front().floats.push_back(dvalue);
				data->blocks.front().vars.insert(var);
		}
}

void Runtime::Add_String(const string& name, string dvalue){
		if(data->blocks.front().vars.find(name) == data->blocks.front().vars.end()){
				throw CodeException("Cannot make new value.", ErrorsNumber::OTHERS);
		} else {
				pair<string, Var> var(name,Var());
				var.second.type = Type::STRING;
				var.second.addr = data->blocks.front().strings.size();
				data->blocks.front().strings.push_back(dvalue);
				data->blocks.front().vars.insert(var);
		}
}

Var Runtime::Get_Var(const string& name, Block** block){
		for(deque<Block>::iterator it = data->blocks.begin(); it != data->blocks.end();++it){
				unordered_map<string,Var>::iterator that = it->vars.find(name);
				if(that != it->vars.end()){
						*block = &(*it);
						return that->second;
				}
		}

		return nil;
}
