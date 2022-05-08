#ifndef IR_DATA_H
#define IR_DATA_H

class IrData {

public:
	IrData(){}
	~IrData(){}
	void setId(const int &id);
	int getId();

	/* Overload */
	bool operator==(const IrData & rData);
private:
	int id;

};
#endif // IR_DATA_H

