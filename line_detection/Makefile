########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 


#First Program (ListTest)
Cpp_OBJ = image.o hough_lines.o edge_detection.o
Cpp_OBJ_1 = image.o hough_lines.o edge_detection.o h1.o
Cpp_OBJ_2 = image.o hough_lines.o edge_detection.o h2.o
Cpp_OBJ_3 = image.o hough_lines.o edge_detection.o h3.o
Cpp_OBJ_4 = image.o hough_lines.o edge_detection.o h4.o

PROGRAM_1 = h1
$(PROGRAM_1): $(Cpp_OBJ_1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_1) $(INCLUDES) $(LIBS_ALL)

PROGRAM_2 = h2
$(PROGRAM_2): $(Cpp_OBJ_2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_2) $(INCLUDES) $(LIBS_ALL)

PROGRAM_3 = h3
$(PROGRAM_3): $(Cpp_OBJ_3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_3) $(INCLUDES) $(LIBS_ALL)

PROGRAM_4 = h4
$(PROGRAM_4): $(Cpp_OBJ_4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_4) $(INCLUDES) $(LIBS_ALL)

all: h1 h2 h3 h4

h_1:
	make $(PROGRAM_1)
h_2:
	make $(PROGRAM_2)
h_3:
	make $(PROGRAM_3)
h_4:
	make $(PROGRAM_4)

clean:
	(rm -f *.o;)

(:
