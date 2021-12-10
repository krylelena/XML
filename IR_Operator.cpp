#include "IR_Operator.h"

IR_Operator::IR_Operator() {
	//cout << "Call constructor IR_Operator()" << endl;
	id = "No id for operator";
	type = "Terminal";
	inputData = nullptr;
	outputData = nullptr;
	inputData_size = 0;
	outputData_size = 0;
	nestedOperators_size = 0;

	//showAll();
}

IR_Operator::IR_Operator(const IR_Operator& obj)
{
	//cout << "Call COPY constructor IR_Operator()" << endl;
	id = obj.id;
	type = obj.type;
	inputData = nullptr;
	outputData = nullptr;
	nestedOperators = nullptr;
	outputData_size = 0;
	inputData_size = 0;
	nestedOperators_size = 0;
}

IR_Operator::~IR_Operator() {
	//cout << "Call destructor ~IR_Operator()" << endl;

	if (inputData != nullptr) 
		delete[] inputData;
	if (outputData != nullptr)
		delete[] outputData;
	if (nestedOperators != nullptr)
		delete[] nestedOperators;
	inputData_size = 0;
	outputData_size = 0;
	nestedOperators_size = 0;

	//showAll();
}

void IR_Operator::addInputData(IR_DataObject& newInputData) {
	cout << endl << "Call IR_Operator::addInputData("<< &newInputData << ")" << endl;

	if (inputData == nullptr) {
		inputData = new IR_DataObject*[1];
		inputData[0] = &newInputData;
		inputData_size = 1;
	}
	else {
		IR_DataObject** bufInputData = new IR_DataObject*[inputData_size + 1];
		for (size_t i = 0; i < inputData_size; i++) {
			bufInputData[i] = inputData[i];
		}
		bufInputData[inputData_size] = &newInputData;
		delete[] inputData;
		inputData = bufInputData;
		inputData_size++;
	}

	showAll();
}

void IR_Operator::addOutputData(IR_DataObject& newOutputData) {
	cout << endl << "Call IR_Operator::addOutputData(" << &newOutputData << ")" << endl;

	if (outputData == nullptr) {
		outputData = new IR_DataObject * [1];
		outputData[0] = &newOutputData;
		outputData_size = 1;
	}
	else {
		IR_DataObject** bufOutputData = new IR_DataObject * [outputData_size + 1];
		for (size_t i = 0; i < outputData_size; i++) {
			bufOutputData[i] = outputData[i];
		}
		bufOutputData[outputData_size] = &newOutputData;
		delete[] outputData;
		outputData = bufOutputData;
		outputData_size++;
	}

	showAll();
}

void IR_Operator::addNestedOperators(IR_Operator& newNestedOperators) {
	cout << endl << "Call IR_Operator::addNestedOperators(" << &newNestedOperators << ")" << endl;
	
	if (nestedOperators == nullptr) {
		nestedOperators = new IR_Operator * [1];
		nestedOperators[0] = &newNestedOperators;
		nestedOperators_size = 1;
	}
	else {
		IR_Operator** bufNestedOperators = new IR_Operator * [nestedOperators_size + 1];
		for (size_t i = 0; i < nestedOperators_size; i++) {
			bufNestedOperators[i] = nestedOperators[i];
		}
		bufNestedOperators[nestedOperators_size] = &newNestedOperators;
		delete[] nestedOperators;
		nestedOperators = bufNestedOperators;
		nestedOperators_size++;
	}

	showAll();
}

void IR_Operator::setId(ID_type id) {
	this->id = id;
}

ID_type IR_Operator::getId() {
	return id;
}
void IR_Operator::setType(OperatorType type) {
	this->type = type;
}
OperatorType IR_Operator::getType() {
	return type;
}

void IR_Operator::clear()
{
	cout << "Call clear IR_Operator()" << endl;
	id = "No id for operator";
	type = "Terminal";
	inputData = nullptr;
	outputData = nullptr;
	inputData_size = 0;
	outputData_size = 0;
	nestedOperators_size = 0;
}

void IR_Operator::showAll() {
	showIdAndType();
	showInputData();
	//showOutputData();
	//showNestedOperators();
}
void IR_Operator::showIdAndType(){
	cout << "  id = " << id << endl << "  type = " << type << endl;
}
void IR_Operator::showInputData(){
	cout << "  inputData: size = "<< inputData_size << endl;
	for (size_t i = 0; i < inputData_size; i++) {
		cout << "    Data ";
		cout << "id =   " << inputData[i]->getId();
		cout << " type =   " << inputData[i]->getType();
		cout << " access_time =   " << inputData[i]->getAccessTime();
		cout << " state =   " << inputData[i]->getState();
		cout << " value =   " << inputData[i]->getValue();
		cout << endl;
	}
}

void IR_Operator::showOutputData() {
	cout << "  outputData: size = " << outputData_size << endl;
	for (size_t i = 0; i < outputData_size; i++) {
		cout << "    Data ";
		cout << "id =   " << outputData[i]->getId();
		cout << " type =   " << outputData[i]->getType();
		cout << " access_time =   " << outputData[i]->getAccessTime();
		cout << " state =   " << outputData[i]->getState();
		cout << " value =   " << outputData[i]->getValue();
		cout << endl;
	}
}

void IR_Operator::showNestedOperators() {
	cout << "  nestedOperators: size = " << nestedOperators_size << endl;
	for (size_t i = 0; i < nestedOperators_size; i++) {
		cout << "    Operator " << i << nestedOperators[i] << endl;
	}
}
