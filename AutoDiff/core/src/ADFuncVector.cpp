#include "ADFuncVector.h"


/////////////////////////////////////////// CONSTRUCTOR

ADFuncVector::ADFuncVector(int size){
	_size = size;
}

ADFuncVector::ADFuncVector(int size, std::vector<ADFunc> funcVec){
	_size = size;
	_funcVec = funcVec;
}

/////////////////////////////////////////// SETTER

void ADFuncVector::setSize(int size){
	_size = size;
}

void ADFuncVector::setFuncVec(std::vector<ADFunc> funcVec){
	if(!checkValid()){
		throw std::runtime_error("Dimension Not Matched!");
	}
	_funcVec = funcVec;
}
void ADFuncVector::set(int size, std::vector<ADFunc> funcVec){
	if(size!=funcVec.size()){
		throw std::runtime_error("Dimension Not Matched!");
	}
	_size = size;
	_funcVec = funcVec;
}

/////////////////////////////////////////// GETTER

// get size of ADFunc Vector
int ADFuncVector::size(){
	if(!checkValid()){
		throw std::runtime_error("Dimension Not Matched!");
	}
	return _size;
}

// check if _funcVec.size() matches with _size
bool ADFuncVector::checkValid(){
	return _size == _funcVec.size();
}

// get partial derivative of ADFunc Vector with respect to a variable 
// given its variable index in seed vector
// 1-d dval vector returned
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
			row_result.push_back( (_funcVec[fv_pair.first]).dval_wrt(fv_pair.second) );
		}
		std::vector<double> row_copy(row_result);
		result.push_back(row_copy);
	}
	return result;
}