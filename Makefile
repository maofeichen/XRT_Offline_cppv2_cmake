CC 		= g++-4.9
INC		= -Iinclude
CFLAG	= -g -std=c++11 -Wall
LFLAG	= -g -std=C++11 -Wall

SRC 	= ./src/

OBJS 	= xt_main.o xt_data.o xt_file.o xt_liveness.o \
		xt_preprocess.o xt_propagate.o xt_searchavalanche.o \
		xt_util.o xt_detectAvalanche.o xt_log.o xt_taintpropagate.o \
		xt_node.o xt_record.o xt_alivebuffer.o xt_functioncall.o \
		TaintBitMap.o xt_detect.o RangeArray.o xt_ByteTaintPropagate.o \
		xt_modedetect.o xt_blockdetect.o xt_blockmodedetector.o xt_cbcdetector.o

OBJS_ADPT	= adpt_main.o adpt_detectavalan.o \
			  xt_file.o xt_liveness.o xt_preprocess.o xt_util.o \
			  xt_functioncall.o xt_alivebuffer.o xt_node.o xt_record.o xt_searchavalanche.o \
			  xt_log.o xt_propagate.o TaintBitMap.o xt_detect.o RangeArray.o xt_ByteTaintPropagate.o \
			  xt_taintpropagate.o xt_blockdetect.o xt_modedetect.o xt_blockmodedetector.o xt_cbcdetector.o \
			  adpt_file.o adpt_alivefunc.o adpt_alivebuf.o 

all : xt_main adpt_detector

xt_main : $(OBJS)
	$(CC) $(INC) -o ./bin/xt_main $(OBJS) $(CFLAG) -L/usr/local/lib/ -lboost_program_options 

adpt_detector : $(OBJS_ADPT)
	$(CC) $(INC) -o ./adpt_detector $(OBJS_ADPT) $(CFLAG) -L/usr/local/lib/ -lboost_program_options 

xt_main.o : src/xt_main.cpp
	$(CC) $(INC) -c src/xt_main.cpp $(CFLAG)

adpt_main.o : $(SRC)adpt_main.cpp
	$(CC) $(INC) -c $(SRC)adpt_main.cpp $(CFLAG) 

xt_data.o : src/xt_data.cpp
	$(CC) $(INC) -c src/xt_data.cpp $(CFLAG)

xt_file.o : src/xt_file.cpp
	$(CC) $(INC) -c src/xt_file.cpp $(CFLAG)

xt_liveness.o : src/xt_liveness.cpp
	$(CC) $(INC) -c src/xt_liveness.cpp $(CFLAG)

xt_preprocess.o : src/xt_preprocess.cpp
	$(CC) $(INC) -c src/xt_preprocess.cpp $(CFLAG)

xt_propagate.o : src/xt_propagate.cpp
	$(CC) $(INC) -c src/xt_propagate.cpp $(CFLAG)

xt_searchavalanche.o : src/xt_searchavalanche.cpp
	$(CC) $(INC) -c src/xt_searchavalanche.cpp $(CFLAG)

xt_util.o : src/xt_util.cpp
	$(CC) $(INC) -c src/xt_util.cpp $(CFLAG)

xt_detectAvalanche.o : src/xt_detectAvalanche.cpp
	$(CC) $(INC) -c src/xt_detectAvalanche.cpp $(CFLAG)

xt_log.o : src/xt_log.cpp
	$(CC) $(INC) -c src/xt_log.cpp $(CFLAG)

xt_taintpropagate.o : src/xt_taintpropagate.cpp
	$(CC) $(INC) -c src/xt_taintpropagate.cpp $(CFLAG)

xt_node.o : src/xt_node.cpp
	$(CC) $(INC) -c src/xt_node.cpp $(CFLAG)

xt_record.o : src/xt_record.cpp
	$(CC) $(INC) -c src/xt_record.cpp $(CFLAG)

xt_alivebuffer.o : src/xt_alivebuffer.cpp
	$(CC) $(INC) -c src/xt_alivebuffer.cpp $(CFLAG)

xt_functioncall.o : src/xt_functioncall.cpp
	$(CC) $(INC) -c src/xt_functioncall.cpp $(CFLAG)

TaintBitMap.o : src/TaintBitMap.cpp
	$(CC) $(INC) -c src/TaintBitMap.cpp $(CFLAG)

xt_detect.o : src/xt_detect.cpp  
	$(CC) $(INC) -c src/xt_detect.cpp $(CFLAG)
	
RangeArray.o : src/RangeArray.cpp
	$(CC) $(INC) -c src/RangeArray.cpp $(CFLAG)

xt_ByteTaintPropagate.o : src/xt_ByteTaintPropagate.cpp
	$(CC) $(INC) -c src/xt_ByteTaintPropagate.cpp $(CFLAG)

xt_modedetect.o : src/xt_modedetect.cpp
	$(CC) $(INC) -c src/xt_modedetect.cpp $(CFLAG)

xt_blockdetect.o : src/xt_blockdetect.cpp
	$(CC) $(INC) -c src/xt_blockdetect.cpp $(CFLAG)

xt_blockmodedetector.o : src/xt_blockmodedetector.cpp
	$(CC) $(INC) -c src/xt_blockmodedetector.cpp $(CFLAG)

xt_cbcdetector.o : src/xt_cbcdetector.cpp
	$(CC) $(INC) -c src/xt_cbcdetector.cpp $(CFLAG)

adpt_detectavalan.o : $(SRC)adpt_detectavalan.cpp
	$(CC) $(INC) -c $(SRC)adpt_detectavalan.cpp $(CFLAG)

adpt_file.o : $(SRC)adpt_file.cpp
	$(CC) $(INC) -c $(SRC)adpt_file.cpp $(CFLAG)

adpt_alivefunc.o : $(SRC)adpt_alivefunc.cpp
	$(CC) $(INC) -c $(SRC)adpt_alivefunc.cpp $(CFLAG)

adpt_alivebuf.o : $(SRC)adpt_alivebuf.cpp
	$(CC) $(INC) -c $(SRC)adpt_alivebuf.cpp $(CFLAG)

.PHONY : clean
clean :
	-rm -f $(OBJS) $(OBJS_ADPT) ./bin/xt_main adpt_detector