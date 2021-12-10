#pragma once

#include <iostream>
#include <string>

using namespace std;

using ID_type = string;
using DataType = string;
using AccessTimeType = string; // должен быть int
using StateType = string;
using ValueType = string;

class IR_DataObject
{
	ID_type id;
	DataType type;
	AccessTimeType accessTime;
	StateType state;
	ValueType value;
	
public:
	IR_DataObject();
	~IR_DataObject();

	void setId(ID_type newId);
	ID_type getId();

	void setType(DataType newType);
	DataType getType();

	void setAccessTime(AccessTimeType newAccessTime);
	AccessTimeType getAccessTime();

	void setState(StateType state);
	StateType getState();

	void setValue(ValueType value);
	ValueType getValue(); 

};

//check functions 
//add show func