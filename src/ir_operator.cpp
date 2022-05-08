#include "ir_operator.h"

void IrOperator::setId(const std::string &id){
	this->id = id;
}

std::string IrOperator::getId(){
	return id;
}
