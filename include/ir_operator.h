#ifndef IR_OPERATOR_H
#define IR_OPERATOR_H

#include <iostream>
#include <string>

class IrOperator{

public:
	IrOperator(){}
	~IrOperator(){}
	void setId(const std::string &id);
	std::string getId();
private:
	std::string id;
};

#endif //  IR_OPERATOR_H
