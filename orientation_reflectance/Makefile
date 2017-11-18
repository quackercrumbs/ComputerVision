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
Cpp_OBJ = image.os
Cpp_OBJ_1 = image.o s1.o
Cpp_OBJ_2 = image.o s2.o
Cpp_OBJ_3 = image.o s3.o
Cpp_OBJ_4 = image.o s4.o

PROGRAM_1 = s1
$(PROGRAM_1): $(Cpp_OBJ_1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_1) $(INCLUDES) $(LIBS_ALL)

PROGRAM_2 = s2
$(PROGRAM_2): $(Cpp_OBJ_2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_2) $(INCLUDES) $(LIBS_ALL)

PROGRAM_3 = s3
$(PROGRAM_3): $(Cpp_OBJ_3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_3) $(INCLUDES) $(LIBS_ALL)

PROGRAM_4 = s4
$(PROGRAM_4): $(Cpp_OBJ_4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_4) $(INCLUDES) $(LIBS_ALL)

all: s1 s2 s3 s4

s_1:
	make $(PROGRAM_1)
s_2:
	make $(PROGRAM_2)
s_3:
	make $(PROGRAM_3)
s_4:
	make $(PROGRAM_4)

clean:
	(rm -f *.o;)

(: