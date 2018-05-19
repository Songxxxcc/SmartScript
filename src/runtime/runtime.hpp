#pragma once

#include "../ssconfig.hpp"
#include <string>
#include <exception>
#include <iostream>

struct Runtime_Vars;

enum ErrorsNumber{
		UNKONW_DO,
		UNKONW_FUNCTION,
		UNKONW_VAR,
		UNKONW_API,
		NEED,
		RUNTIME,
		EXCEPTION_IN_CODE
};

enum Type{
		INT,
		FLOAT,
		STRING,
		INTS,
		FLOATS,
		STRINGS,
		OWNSTRUCT
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
		public:
			Runtime();
			Runtime(const Runtime&) = delete;
			Runtime(Runtime&&) = delete;
			~Runtime();

			void Run_Order(const std::string&);
};
