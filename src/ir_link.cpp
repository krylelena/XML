#include "ir_link.h"


void IrLink::setDataId(int dataId){
	this->dataId = dataId;
}

void IrLink::setOperatorId(std::string operatorId){
	this->operatorId = operatorId;
}

void IrLink::setDir(int dir){
	this->dir = dir;
}

int IrLink::getDataId(){
	return dataId;
}

std::string IrLink::getOperatorId(){
	return operatorId;
}

int IrLink::getDir(){
	return dir;
}

std::string IrLink::to_str(){
	std::string res = "data id " +  std::to_string(dataId) + ", op id "  + operatorId + ", dir "  + std::to_string(dir);
	return res;
}
