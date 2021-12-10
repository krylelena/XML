#pragma once

#include <iostream>
#include <string>

#include "IR_DataObject.h"

using namespace std;

using ID_type = string;
using OperatorType = string;

class IR_Operator
{
	ID_type id;
	OperatorType type;
	IR_DataObject** inputData;
	IR_DataObject** outputData;
	IR_Operator** nestedOperators; //вложенный оператор
	size_t inputData_size;
	size_t outputData_size;
	size_t nestedOperators_size;

	//void showAll();
	void showIdAndType();
	void showInputData();
	void showOutputData();
	void showNestedOperators();
public:
	IR_Operator();
	IR_Operator(const IR_Operator& obj); //конструктор копирования
	~IR_Operator();
	void addInputData(IR_DataObject& newInputData);
	void addOutputData(IR_DataObject& newOutputData);
	void addNestedOperators(IR_Operator& newNestedOperators);
	void setId(ID_type id);
	ID_type getId();
	void setType(OperatorType type);
	OperatorType getType();

	void clear();
	void showAll();
};

//if complex then 1. add array for APE or 2. наследование от IR_operator + add array for APE