CPP = g++ 
FLAGS = -O3 -pg -Wall -W
RM  = rm -f
EXEC = fp_extended

OBJECTS = \
	 fp_extended.o \
	 

all: $(OBJECTS) compile touch 


fp_extended.o : fp_extended.cpp
			   		 $(CPP) $(FLAGS) -c fp_extended.cpp
clean:  
					 $(RM) $(OBJECTS) $(EXEC) 

compile: 
					 $(CPP) $(FLAGS) $(OBJECTS) -o $(EXEC) 

touch:
					 @echo " "
					 @echo "Compilation done successfully..................."
					 @echo " "
