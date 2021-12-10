#include <iostream>
#include <list>
#include <map>

using namespace std;

class Element {
	Element* parent;
	list <Element*> children;
	string name;				  //имя тега
	map <string, string> attribs; //имя атрибута, значение атрибута
public:
	void setName(string name) {
		this->name = name;
	};

	string getName() {
		return name;
	};

	void addAttribute(string name, string value) {
		attribs[name] = value;
	}

	map <string, string> getAttribs() {
		return attribs;
	}

	void addChild(Element& child) {
		children.push_back(&child);
	}

	void showAttribs() {
		for (auto el : attribs) {
			cout << el.first << " = " << el.second << " ";
		}
		cout << endl;
	}

	Element() { parent = nullptr; name = ""; }
	~Element() {}
};

int testFunction() {
	Element program;

	program.setName("program");
	program.addAttribute("name", "inner product Complex");


	Element operator1;
	Element operator2;
	Element operator3;


	program.addChild(operator1);
	program.addChild(operator2);
	program.addChild(operator3);

	operator1.setName("operator");
	operator2.setName("operator");
	operator3.setName("operator");


	operator1.addAttribute("id", "mult1");
	operator1.addAttribute("type", "Terminal");

	operator2.addAttribute("id", "mult2");
	operator2.addAttribute("type", "Terminal");

	operator3.addAttribute("id", "add");
	operator3.addAttribute("type", "Terminal");

	Element data1[3];
	Element data2[3];
	Element data3[3];

	operator1.addChild(data1[0]);
	operator1.addChild(data1[1]);
	operator1.addChild(data1[2]);

	operator2.addChild(data1[0]);
	operator2.addChild(data1[1]);
	operator2.addChild(data1[2]);

	operator3.addChild(data1[0]);
	operator3.addChild(data1[1]);
	operator3.addChild(data1[2]);

	data1[0].setName("data");
	data1[1].setName("data");
	data1[2].setName("data");

	data1[0].addAttribute("id", "x1");
	data1[0].addAttribute("type", "float");
	data1[0].addAttribute("connect_type", "input");
	data1[0].addAttribute("order", "1");
	data1[0].addAttribute("access_time", "10");

	data1[1].addAttribute("id", "y1");
	data1[1].addAttribute("type", "float");
	data1[1].addAttribute("connect_type", "input");
	data1[1].addAttribute("order", "2");
	data1[1].addAttribute("access_time", "10");

	data1[2].addAttribute("id", "c1");
	data1[2].addAttribute("type", "float");
	data1[2].addAttribute("connect_type", "output");
	data1[2].addAttribute("order", "1");
	data1[2].addAttribute("access_time", "10");



	cout << program.getName() << " ";
	program.showAttribs();
	cout << "  " << operator1.getName() << " ";
	operator1.showAttribs();
	cout << "    " << data1[0].getName() << " ";
	data1[0].showAttribs();
	cout << "    " << data1[1].getName() << " ";
	data1[1].showAttribs();
	cout << "    " << data1[2].getName() << " ";
	data1[2].showAttribs();

	cout << "  " << operator2.getName() << " ";
	operator2.showAttribs();

	cout << "  " << operator3.getName() << " ";
	operator3.showAttribs();


	return 0;
}
//<data id = "x1" type = "float" connect_type = "input" order = "1" access_time = "10" / >