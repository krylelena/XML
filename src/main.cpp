/* C++ headers */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/* XML lib headers*/
#include "pugixml.hpp"

/* Project headers */
#include "ir_data.h"
#include "ir_operator.h"
#include "ir_link.h"

void create_xml_file(std::string file_name = "output.xml");

/* Parse function */
void parse_xml(std::string file_name = "output.xml");

/* Convert function */
IrOperator convertToIrOperator(pugi::xml_node & op_xml);

/* Show functions */
void showIrOperators(std::vector<IrOperator> &operators);
void showIrData(std::vector<IrData> &data);
void showIrLinks(std::vector<IrLink> &links);

/* Take data */
std::vector<IrData> takeInputIrData(pugi::xml_node & op_xml);
std::vector<IrData> takeOutputIrData(pugi::xml_node & op_xml);

/* Add data to vector */
void addIrDataToVector(std::vector<IrData> &data,std::vector<IrData> &newData);


/* Create link */
void createLinksFromVectorData(std::vector<IrLink> & links, std::vector<IrData> & data, IrOperator & op, int dir);

int main(int argc, char * argv[]){
	create_xml_file(argv[1]);
	parse_xml(argv[1]);
	return 0;
}
void create_xml_file(std::string file_name){

	pugi::xml_document doc;
	pugi::xml_node program = doc.append_child("program");

	/* Create operator nodes */
	pugi::xml_node op1 = program.append_child("operator");
	pugi::xml_node op2 = program.append_child("operator");
	pugi::xml_node op3 = program.append_child("operator");

	/* Create data nodes */
	pugi::xml_node op1_data[3];
	pugi::xml_node op2_data[3];
	pugi::xml_node op3_data[3];
	for (int i = 0; i < 3; ++i) {
		op1_data[i] = op1.append_child("data");
	}

	for (int i = 0; i < 3; ++i) {
		op2_data[i] = op2.append_child("data");
	}

	for (int i = 0; i < 3; ++i) {
		op3_data[i] = op3.append_child("data");
	}


	/* Filling attribute operators */
	op1.append_attribute("id") = "mult1";
	op2.append_attribute("id") = "mult2";
	op3.append_attribute("id") = "sum";

	/* Filling attribute data */
	op1_data[0].append_attribute("id") = "1";
	op1_data[1].append_attribute("id") = "2";
	op1_data[2].append_attribute("id") = "3";
	op2_data[0].append_attribute("id") = "4";
	op2_data[1].append_attribute("id") = "5";
	op2_data[2].append_attribute("id") = "6";
	op3_data[0].append_attribute("id") = "3";
	op3_data[1].append_attribute("id") = "6";
	op3_data[2].append_attribute("id") = "7";

	op1_data[0].append_attribute("dir") = "input";
	op1_data[1].append_attribute("dir") = "input";
	op1_data[2].append_attribute("dir") = "output";
	op2_data[0].append_attribute("dir") = "input";
	op2_data[1].append_attribute("dir") = "input";
	op2_data[2].append_attribute("dir") = "output";
	op3_data[0].append_attribute("dir") = "input";
	op3_data[1].append_attribute("dir") = "input";
	op3_data[2].append_attribute("dir") = "output";


	doc.save_file(file_name.c_str());
}



void parse_xml(std::string file_name){
	/* Declaration containers */
	std::vector<IrOperator> operators;
	std::vector<IrData> data;
	std::vector<IrLink> links;

	/* Load xml file */
	pugi::xml_document doc;
	doc.load_file(file_name.c_str());

	/* Take top tag */
	pugi::xml_node program = doc.child("program");

	/* Parse tag inside */
	for(auto el : program){

		/* Add current operator in Ir vector */
		IrOperator currOp = convertToIrOperator(el);
		operators.push_back(currOp);

		/* Take input data from operator tag */
		std::vector<IrData> inputData = takeInputIrData(el);

		/* Create link objects from input data */
		if(inputData.size() != 0){
			createLinksFromVectorData(links, inputData, currOp, 0);
		}

		/* Take input data from operator tag */
		std::vector<IrData> outputData = takeOutputIrData(el);

		/* Create link objects from input data */
		if (outputData.size() != 0){
			createLinksFromVectorData(links, outputData, currOp, 1);
		}

		/* Add input/output data in Ir vector */
		addIrDataToVector(data, inputData);
		addIrDataToVector(data, outputData);
	}

	/* Show result Ir objects */
	std::cout << "Operators" << std::endl;
	showIrOperators(operators);
	std::cout << " - " << std::endl;
	std::cout << "Data" << std::endl;
	showIrData(data);
	std::cout << " - " << std::endl;
	std::cout << "link" << std::endl;
	showIrLinks(links);
	std::cout << " - " << std::endl;
}

IrOperator convertToIrOperator(pugi::xml_node & op_xml){
	IrOperator op;
	op.setId(op_xml.attribute("id").value());

	return op;
}

void showIrOperators(std::vector<IrOperator> &operators){
	for (auto el : operators){
		std::cout << el.getId() <<std::endl;
	}
}

void showIrData(std::vector<IrData> &data){
	for (auto el : data){
		std::cout << el.getId() << std::endl;
	}
}

void showIrLinks(std::vector<IrLink> &links){
	for (auto el : links){
		std::cout << el.to_str() << std::endl;
	}
}

std::vector<IrData> takeInputIrData(pugi::xml_node & op_xml){
	std::vector<IrData> dataResult;
	for (auto data : op_xml) {
		std::string dir = data.attribute("dir").value();
		if(dir == "input"){
			IrData currData;
			int id = data.attribute("id").as_int();
			currData.setId(id);
			dataResult.push_back(currData);
		}
	}
	return dataResult;
}

std::vector<IrData> takeOutputIrData(pugi::xml_node & op_xml){
	std::vector<IrData> dataResult;
	for (auto data : op_xml) {
		std::string dir = data.attribute("dir").value();
		if(dir == "output"){
			IrData currData;
			int id = data.attribute("id").as_int();
			currData.setId(id);
			dataResult.push_back(currData);
		}
	}
	return dataResult ;
}

void addIrDataToVector(std::vector<IrData> &data,std::vector<IrData> &newData){
	for (auto el : newData) {
		if(std::find(data.begin(), data.end(), el) == data.end()){
			data.push_back(el);
		}
	}
}


void createLinksFromVectorData(std::vector<IrLink> & links, std::vector<IrData> & data, IrOperator & op, int dir)
{
	for (auto el : data){
		links.push_back(IrLink(el.getId(), op.getId(), dir));
	}
}
