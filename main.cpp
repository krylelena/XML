#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "rapidxml.hpp"
#include "IR_Operator.h"
#include "IR_DataObject.h"

using namespace std;
using namespace rapidxml;

void testFunction();
void testXML();
void parseProgram(xml_node<>& root_node);
void parseHighLevelOperator(xml_node<>& parentOperator_node,  vector <IR_Operator>& arrProgram, vector <IR_Operator>& OperatorHeap, vector<IR_DataObject>& DataHeap);
void parseOperator(xml_node<>& parentOperator_node, vector <IR_Operator*> arrNestedOperator, vector <IR_Operator>& OperatorHeap, vector<IR_DataObject>& DataHeap);
void parseData(xml_node<>& operator_node, map <string, IR_DataObject>& arrInData, map <string, IR_DataObject>& arrOutData);

int main() {
	//testFunction();
	testXML();
	return 0;
}
void testXML() {
	cout << "\nParsing my graph (sample.xml)....." << endl;
	xml_document<> doc;
	xml_node<>* root_node = NULL;

	// Read the sample.xml file
	ifstream theFile("AlgScalar1.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	// Parse the buffer
	doc.parse<0>(&buffer[0]);

	// Find out the root node
	root_node = doc.first_node("program");

	parseProgram(*root_node);

}
void parseProgram(xml_node<>& root_node)
{
	vector <IR_Operator> arrProgram;
	vector <IR_Operator> OperatorHeap;
	vector<IR_DataObject> DataHeap;

	parseHighLevelOperator(root_node, arrProgram, OperatorHeap, DataHeap);
	//***************debug data
	cout << endl;
	for (auto el : arrProgram) {
		el.showAll();
		cout << endl;
	}
	
}
void parseHighLevelOperator(xml_node<>& parentOperator_node, vector<IR_Operator>& arrProgram, vector<IR_Operator>& OperatorHeap, vector<IR_DataObject>& DataHeap)
{
	map <string, IR_DataObject> arrInData;
	map <string, IR_DataObject> arrOutData;
	vector <IR_Operator*> local_arrNestedOperator;
	IR_Operator currentOperator;

	for (xml_node<>* operator_node = (&parentOperator_node)->first_node("operator"); operator_node; operator_node = operator_node->next_sibling())
	{
		currentOperator.setId(operator_node->first_attribute("id")->value());
		currentOperator.setType(operator_node->first_attribute("type")->value());

		cout << "\nOperator id =   " << currentOperator.getId();
		cout << "\nOperator type =   " << currentOperator.getType();
		cout << endl;

		if (currentOperator.getType() == "Complex") {
			parseOperator(*operator_node, local_arrNestedOperator, OperatorHeap, DataHeap);
			for (auto ptr : local_arrNestedOperator) {
				currentOperator.addNestedOperators(*ptr);//Привязать объект входных данных из кучи данных
			}
		}
		//*************************************************************************************************************************
		parseData(*operator_node, arrInData, arrOutData);
		for (int i = 1; i < arrInData.size(); i++) {
			IR_DataObject bufData = arrInData[to_string(i)];
			//поместить bufData в кучу данных и вернуть адрес
			DataHeap.push_back(bufData);
			currentOperator.addInputData(DataHeap.back());//Привязать объект входных данных из кучи данных
		}
		for (int i = 1; i < arrOutData.size(); i++) {
			IR_DataObject bufData = arrOutData[to_string(i)];
			//поместить bufData в кучу данных и вернуть адрес
			DataHeap.push_back(bufData);
			currentOperator.addOutputData(DataHeap.back());//Привязать объект выходных данных из кучи данных
		}
		arrProgram.push_back(currentOperator);
		currentOperator.clear();
		arrInData.clear();
		arrOutData.clear();
	}
}
void parseOperator(xml_node<>& parentOperator_node, vector <IR_Operator*> arrNestedOperator, vector<IR_Operator>& OperatorHeap, vector<IR_DataObject>& DataHeap)
{
	map <string, IR_DataObject> arrInData;
	map <string, IR_DataObject> arrOutData;
	vector <IR_Operator*> local_arrNestedOperator;
	IR_Operator currentOperator;

	for (xml_node<>* operator_node = (&parentOperator_node)->first_node("operator"); operator_node; operator_node = operator_node->next_sibling())
	{
		currentOperator.setId(operator_node->first_attribute("id")->value());
		currentOperator.setType(operator_node->first_attribute("type")->value());

		cout << "\nOperator id =   " << currentOperator.getId();
		cout << "\nOperator type =   " << currentOperator.getType();
		cout << endl;

		if (currentOperator.getType() == "Complex") {
			parseOperator(*operator_node, local_arrNestedOperator, OperatorHeap, DataHeap);
			for (auto ptr : local_arrNestedOperator) {
				currentOperator.addNestedOperators(*ptr);//Привязать объект входных данных из кучи данных
			}
		}
		//*************************************************************************************************************************
		parseData(*operator_node, arrInData, arrOutData);
		for (int i = 1; i < arrInData.size(); i++) {
			IR_DataObject bufData = arrInData[to_string(i)];
			//поместить bufData в кучу данных и вернуть адрес
			DataHeap.push_back(bufData);
			currentOperator.addInputData(DataHeap.back());//Привязать объект входных данных из кучи данных
		}
		for (int i = 1; i < arrOutData.size(); i++) {
			IR_DataObject bufData = arrOutData[to_string(i)];
			//поместить bufData в кучу данных и вернуть адрес
			DataHeap.push_back(bufData);
			currentOperator.addOutputData(DataHeap.back());//Привязать объект выходных данных из кучи данных
		}
		OperatorHeap.push_back(currentOperator);
		arrNestedOperator.push_back(&OperatorHeap.back());
		currentOperator.clear();
		arrInData.clear();
		arrOutData.clear();
	}
}
void parseData(xml_node<>& operator_node, map <string, IR_DataObject>& arrInData, map <string, IR_DataObject>& arrOutData)
{
	IR_DataObject currentData;

	for (xml_node<>* data_node = (&operator_node)->first_node("data"); data_node; data_node = data_node->next_sibling("data"))
	{

		currentData.setId(data_node->first_attribute("id")->value());
		currentData.setType(data_node->first_attribute("type")->value());
		currentData.setAccessTime(data_node->first_attribute("access_time")->value());
		currentData.setState(data_node->first_attribute("state")->value());

		string state = data_node->first_attribute("state")->value();

		if (state == "full") {
			currentData.setValue(data_node->first_attribute("value")->value());
		}
		string connect_type = data_node->first_attribute("connect_type")->value();
		string order = data_node->first_attribute("order")->value();
		if (connect_type == "input") {
			arrInData[order] = currentData;
		}
		else if(connect_type == "output") {
			arrOutData[order] = currentData;

		}

		/*cout << "Data id =   " << data_node->first_attribute("id")->value();
		cout << endl;

		cout << "Data type =   " << data_node->first_attribute("type")->value();
		cout << endl;

		cout << "Data connect_type =   " << data_node->first_attribute("connect_type")->value();
		cout << endl;

		cout << "Data order =   " << data_node->first_attribute("order")->value();
		cout << endl;

		cout << "Data access_time =   " << data_node->first_attribute("access_time")->value();
		cout << endl;

		cout << "Data state =   " << state;
		cout << endl;

		if (state == "full") {
			cout << "Data value =   " << data_node->first_attribute("value")->value();
		}
		cout << endl << endl;*/
	}
	cout << endl;
}
void testFunction() {
	string generalType = "float";
	IR_Operator multiplier2, mult1, mult2, add;
	IR_DataObject data[7];

	data[0].setId("x1");
	data[1].setId("y1");
	data[2].setId("x2");
	data[3].setId("y2");
	data[4].setId("c1");
	data[5].setId("c2");
	data[6].setId("c");
	
	data[0].setType(generalType);
	data[1].setType(generalType);
	data[2].setType(generalType);
	data[3].setType(generalType);
	data[4].setType(generalType);
	data[5].setType(generalType);
	data[6].setType(generalType);

	/*data[0].setAccessTime(10);
	data[1].setAccessTime(10);
	data[2].setAccessTime(10);
	data[3].setAccessTime(10);
	data[4].setAccessTime(10);
	data[5].setAccessTime(10);
	data[6].setAccessTime(10);*/

	data[0].setState("empty");
	data[1].setState("full");
	data[2].setState("empty");
	data[3].setState("empty");
	data[4].setState("empty");
	data[5].setState("empty");
	data[6].setState("empty");

	multiplier2.setId("multiplier2");
	mult1.setId("mult1");
	mult2.setId("mult2");
	add.setId("add");

	multiplier2.setType("Complex");
	//others operators are terminal default

	multiplier2.addInputData(data[0]);
	multiplier2.addInputData(data[1]);
	multiplier2.addInputData(data[2]);
	multiplier2.addInputData(data[3]);
	multiplier2.addOutputData(data[4]);
	multiplier2.addOutputData(data[5]);
	
	multiplier2.addNestedOperators(mult1);
	multiplier2.addNestedOperators(mult2);

	mult1.addInputData(data[0]);
	mult1.addInputData(data[1]);
	mult1.addOutputData(data[4]);

	mult2.addInputData(data[2]);
	mult2.addInputData(data[3]);
	mult2.addOutputData(data[5]);

	add.addInputData(data[4]);
	add.addInputData(data[5]);
	add.addOutputData(data[6]);
	
}

//красивый вывод - тест