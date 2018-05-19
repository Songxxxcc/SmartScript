#include "runtime/runtime.hpp"
#include "ssconfig.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int main(int argc ,char** argv){
		if(argc <= 1){
				cerr << "No Runable Script." << endl;
		} else {
				//cout << "Script name:"<< argv[1] << endl;
				Runtime runtime;
				ifstream input(argv[1]);
				string order;
				try{
						while(getline(input,order)){
								runtime.Run_Order(order);
						}
				}catch(CodeException ex){
						switch(ex.Get_Errors_Number()){
								case ErrorsNumber::UNKONW_API:
										cerr << ex.Show_Exception_Text() << endl;
										cerr << "Cannot find this API. Please check your smartscript API version." << endl;
								break;
								//cerr << ex.Show_Exception_Text() << endl;

						}
				}

		}
		return 0;
}
