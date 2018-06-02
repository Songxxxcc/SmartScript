#pragma once

#include "../ssconfig.hpp"
#include <string>
#include <exception>
#include <iostream>
#include <deque>
#include <unordered_map>
#include <string>

struct Runtime_Vars;

enum ErrorsNumber{
		UNKONW_DO,
		UNKONW_FUNCTION,
		UNKONW_VAR,
		UNKONW_API,
		NEED,
		OTHERS,
		RUNTIME,
		EXCEPTION_IN_CODE
};

enum Type{
		INT,
		FLOAT,
		STRING,
		NIL/*,
				INTS,
				FLOATS,
				STRINGS,
				OWNSTRUCT*/
};

struct Var{
		unsigned int type;
		unsigned long addr;
};

struct Block{
		std::deque<long> ints;
		std::deque<double> floats;
		std::deque<std::string> strings;
		std::unordered_map<std::string,Var> vars;
		bool is_pass = false;
};

struct Runtime_Vars{
		std::deque<Block> blocks;
		Runtime_Vars(){
				blocks.push_front(Block());
		}
};


class CodeException : std::exception{
		std::string about;
		enum ErrorsNumber err;
		public:
		CodeException(const std::string&,enum ErrorsNumber);
		std::string Show_Exception_Text() const;
		enum ErrorsNumber Get_Errors_Number() const;
};

class Runtime{
		Runtime_Vars* data;
		Var nil;
		public:
		Runtime();
		Runtime(const Runtime&) = delete;
		Runtime(Runtime&&) = delete;
		~Runtime();

		void Run_Order(const std::string&);

		void Add_Int(const std::string& name,long default_value);
		void Add_String(const std::string& name, std::string default_value);
		void Add_Float(const std::string& name, double default_value);

		Var Get_Var(const std::string& name,Block** block);

		Var Find_Var(std::string name);

};



