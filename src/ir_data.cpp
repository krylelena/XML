#include "ir_data.h"



void IrData::setId(const int &id){
	this->id = id;
}

int IrData::getId(){
	return id;
}

bool IrData::operator==(const IrData & rData ){
	if (id == rData.id)
		return 1;
	return 0;
}
