#include "ADFuncVector.h"


/////////////////////////////////////////// CONSTRUCTOR

ADFuncVector::ADFuncVector(){
	_size = 0;
	_num_vars = -1;
}

ADFuncVector::ADFuncVector(int size){
	_size = size;
	_num_vars = -1;
}

ADFuncVector::ADFuncVector(std::vector<ADFunc> funcVec){
	_size = funcVec.size();
	_funcVec = funcVec;
	if(funcVec.size()!=0){
		_num_vars = funcVec[0].countVar();
	} else {
		_num_vars = -1;
	}
	
	for(ADFunc f: funcVec){
		if(f.countVar()!=_num_vars){
			throw std::runtime_error("Input function have different number of varibales!");
		}
	}
}

/////////////////////////////////////////// SETTER

void ADFuncVector::setSize(int size){
	if(_funcVec.size()!=0 && _funcVec.size()!=size){
		throw std::runtime_error("Input size mismatches with current funcVector! Please use clear() before set size.");
	}
	_size = size;
}

void ADFuncVector::setFuncVec(std::vector<ADFunc> funcVec){
	//case 1: _size set, _funcVec not _set
	//        throw error if _size!=funcVec.size()
	if(_funcVec.size()==0 && funcVec.size()!=_size && _size!=0){
		throw std::runtime_error("Input funcVector mismatches with current size! Please use clear() before set a new funcVector.");
	}
	//case 2: _size set, _funcVec set
	//        _size and _funcVec changed
	//case 3: _size not set, _funcVec not set
	//        _size and _funcVec changed
	if(funcVec.size()!=0){
		_num_vars = funcVec[0].countVar();
	} else {
		_num_vars = -1;
	}
	
	for(ADFunc f: funcVec){
		if(f.countVar()!=_num_vars){
			throw std::runtime_error("Input function have different number of varibales!");
		}
	}
	_funcVec = funcVec;
	_size = funcVec.size();
}

void ADFuncVector::clear(){
	_size = 0;
	_funcVec.clear();
	_num_vars = -1;
}

// append a new func to the end
void ADFuncVector::push_back(ADFunc func){
	if(func.countVar()!=_num_vars){
		throw std::runtime_error("Input size mismatches with previously defined funcVector! Please use clear() before set size.");
	}
	_funcVec.push_back(func);
	_size = _funcVec.size();
}

/////////////////////////////////////////// GETTER

// get val of a function
double ADFuncVector::val(int index){
	if(index>=_size){
		throw std::out_of_range("Index out of range!");
	}
	return _funcVec.at(index).val();
}

// get size of ADFunc Vector
int ADFuncVector::size(){
	if(!checkValid()){
		throw std::runtime_error("Dimension Not Matched!");
	}
	return _size;
}

// check if _funcVec.size() matches with _size
bool ADFuncVector::checkValid(){
	for(ADFunc f: _funcVec){
		if(f.countVar()!=_num_vars){
			throw std::runtime_error("Input function have different number of varibales!");
		}
	}
	if(_size!=0 && _size != _funcVec.size()){
		throw std::runtime_error("Internal size not matched with internal std::vector<ADFunc>! Please use setFuncVec() or setSize() to fix it!");
	}
	return true;
}

// check if _funVec is empty
bool ADFuncVector::empty(){
	return _size == 0;
}

// get partial derivative of a particular function with respect to a variable 
// given function index and variable index in seed vector
// 1 single double returned
double ADFuncVector::dval_wrt(int func_index, int var_index){
	if(func_index>=_size){
		throw std::out_of_range("Function index out of range!");
	}
	return _funcVec[func_index].dval_wrt(var_index);
}

// get partial derivative of ADFunc Vector with respect to a variable 
// given its variable name
// 1-d dval vector returned
double ADFuncVector::dval_wrt(int func_index, std::string var_name){
	if(func_index>=_size){
		throw std::out_of_range("Function index out of range!");
	}
	
	return _funcVec[func_index].dval_wrt(var_name);
}

// get partial derivative of ADFunc Vector with respect to a variable 
// given its variable index in seed vector
// 1-d dval vector returned
// out of index is handled by ADFunc class
std::vector<double> ADFuncVector::dval_wrt(int index){
	std::vector<double> result;
	for(ADFunc func: _funcVec){
		result.push_back(func.dval_wrt(index));
	}
	return result;
}

// get partial derivative of ADFunc Vector with respect to a variable 
// given its variable name
// 1-d dval vector returned
std::vector<double> ADFuncVector::dval_wrt(std::string var_name){
	std::vector<double> result;
	for(ADFunc func: _funcVec){
		result.push_back(func.dval_wrt(var_name));
	}
	return result;
}

// Given function index and corresponding variable index,
// get partial derivative of ADFunc Vector with respect to more than one variables 
// 1-d dval vector returned
std::vector<double> ADFuncVector::dval_wrt(std::vector<std::pair<int, int> > fun_var){
	std::vector<double> result;
	for(std::pair<int,int> fv_pair: fun_var){
		if(fv_pair.first>=_size){
			throw std::out_of_range("Function index out of range!");
		}
		result.push_back( (_funcVec[fv_pair.first]).dval_wrt(fv_pair.second) );
	}
	return result;
}

// Given function index and variable name, 
// get partial derivative of ADFunc Vector with respect to more than one variables 
// 1-d dval vector returned
std::vector<double> ADFuncVector::dval_wrt(std::vector<std::pair<int, std::string> > fun_var){
	std::vector<double> result;
	for(std::pair<int,std::string> fv_pair: fun_var){
		if(fv_pair.first>=_size){
			throw std::out_of_range("Function index out of range!");
		}
		result.push_back( (_funcVec[fv_pair.first]).dval_wrt(fv_pair.second) );
	}
	return result;
}

// Given function index and variable index, 
// get partial derivative of ADFunc Vector with respect to more than one variables 
// 2-d dval vector returned
std::vector<std::vector<double> > ADFuncVector::dval_wrt(std::vector<std::vector<std::pair<int, int> > > fun_var){
	std::vector<std::vector<double> > result;
	std::vector<double> row_result;
	for(std::vector<std::pair<int,int> > row: fun_var){

		row_result.clear();
		for(std::pair<int,int> fv_pair: row){
			if(fv_pair.first>=_size){
				throw std::out_of_range("Function index out of range!");
			}
			row_result.push_back( (_funcVec[fv_pair.first]).dval_wrt(fv_pair.second) );
		}
		std::vector<double> row_copy(row_result);
		result.push_back(row_copy);
	}
	return result;
}

// Given function index and variable name, 
// get partial derivative of ADFunc Vector with respect to more than one variables 
// 2-d dval vector returned
std::vector<std::vector<double> > ADFuncVector::dval_wrt(std::vector<std::vector<std::pair<int, std::string> > > fun_var){
	std::vector<std::vector<double> > result;
	std::vector<double> row_result;
	for(std::vector<std::pair<int,std::string> > row: fun_var){
		row_result.clear();
		for(std::pair<int,std::string> fv_pair: row){
			if(fv_pair.first>=_size){
				throw std::out_of_range("Function index out of range!");
			} 
			row_result.push_back( (_funcVec[fv_pair.first]).dval_wrt(fv_pair.second) );
		}
		std::vector<double> row_copy(row_result);
		result.push_back(row_copy);
	}
	return result;
}

// return the jacobian of ADFuncVector
// use _funcVec's order and the order that seed vector provides
std::vector<std::vector<double> > ADFuncVector::jacobian(){
	std::vector<std::vector<double> > result;
	std::vector<double> row_result;
	for(int i=0;i<_size;i++){
		row_result.clear();
		for(int j=0;j<_num_vars;j++){
			row_result.push_back( (_funcVec[i]).dval_wrt(j) );
		}
		std::vector<double> row_copy(row_result);
		result.push_back(row_copy);
	}
	return result;
}

ADFunc* ADFuncVector::at(int i){
	if(i>_size) throw std::out_of_range("Index out of range!");
	return &(_funcVec[i]);
}

int ADFuncVector::countVar(){
	return _num_vars;
}