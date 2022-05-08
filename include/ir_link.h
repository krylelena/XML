#ifndef IR_LINK_H
#define IR_LINK_H
#include <iostream>
#include <string>

class IrLink{
public:

	/* Constructors */
	IrLink(){};
	IrLink(int dataId, std::string operatorId, int dir)
			:dataId(dataId), operatorId(operatorId), dir(dir)
			{};

	/* Setters */
	void setDataId(int dataId);
	void setOperatorId(std::string operatorId);
	void setDir(int dir);

	/* Getters */
	int getDataId();
	std::string getOperatorId();
	int getDir();

	/* To string */
	std::string to_str();
private:
	int dataId;
	std::string operatorId;
	int dir;	/* 0 - from data to operator
				   1 - from operator to data */
};
#endif // IR_LINK_H
