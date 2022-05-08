GXX := g++
program := xml_parse
include_dir := third_parts
root_source := src
root_include := include
lib_dir := lib
sources := 

all: run show_xml

run: $(program)
	./$(program) output.xml

show_xml:
	cat output.xml


$(program): main.o ir_data.o ir_operator.o ir_link.o
	$(GXX) -o $(program) main.o ir_data.o ir_operator.o ir_link.o -L$(lib_dir) -lpugixml

main.o: $(root_source)/main.cpp
	$(GXX) -c $(root_source)/main.cpp -I$(include_dir) -I$(root_include)

ir_data.o: $(root_source)/ir_data.cpp
	$(GXX) -c $(root_source)/ir_data.cpp -I$(root_include)

ir_operator.o: $(root_source)/ir_operator.cpp
	$(GXX) -c $(root_source)/ir_operator.cpp -I$(root_include)

ir_link.o: $(root_source)/ir_link.cpp
	$(GXX) -c $(root_source)/ir_link.cpp -I$(root_include)


build-libpugixml: libpugixml.a

libpugixml.a: pugixml.o
	ar cr libpugixml.a pugixml.o


pugixml.o: pugixml.cpp
	$(GXX) -c pugixml.cpp

clean:
	rm -rf *.o $(program)
