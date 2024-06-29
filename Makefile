OUT	= main

OBJS = \
include/certusPDF.o \
include/helpers.o \
include/pdfBuffer.o \
include/QrToPng.o \
include/TinyPngOut.o \
include/AnnotationsWriter.o \
include/QrCode.o \
include/base64.o \
main.o

LIB = \
-L/home/notis/CertusPDF/libs/PDF-Writer-master/build/PDFWriter \
-L/home/notis/CertusPDF/libs/PDF-Writer-master/build/LibAesgm \
-L/home/notis/CertusPDF/libs/PDF-Writer-master/build/FreeType \
-L/home/notis/CertusPDF/libs/PDF-Writer-master/build/LibJpeg \
-L/home/notis/CertusPDF/libs/PDF-Writer-master/build/LibPng \
-L/home/notis/CertusPDF/libs/PDF-Writer-master/build/LibTiff \
-L/home/notis/CertusPDF/libs/PDF-Writer-master/build/Zlib \
-L/home/notis/CertusPDF/libs/libxl-4.3.0.14/lib64

INC = \
-I/home/notis/CertusPDF/libs/PDF-Writer-master/FreeType/include \
-I/home/notis/CertusPDF/libs/PDF-Writer-master/PDFWriter \
-I/home/notis/CertusPDF/include \
-I/home/notis/CertusPDF/libs/libxl-4.3.0.14/include_cpp

CC = g++
VERSION = -std=c++14
OPTIMIZATION = -Ofast -fomit-frame-pointer -funroll-loops -ftree-vectorize -ffat-lto-objects -flto -ffunction-sections -fdata-sections -fno-rtti -DNDEBUG -march=native -mtune=native -m64

DEBUG = #-g
PROFILING = #$(DEBUG) -pg -fno-omit-frame-pointer -fno-inline-functions -fno-inline-functions-called-once -fno-optimize-sibling-calls -fno-default-inline -fno-inline
SHARED = #-fIPC

FLAGS	= -c $(VERSION) $(OPTIMIZATION) $(DEBUG) $(PROFILING) $(SHARED)
WFLAGS = #-Wall -Wshadow -Wextra -Wpedantic -Wconversion -Wsign-conversion
LFLAGS = -Wl,--gc-sections -lpthread -lPDFWriter -lLibAesgm -lFreeType -lLibJpeg -lLibPng -lLibTiff -lZlib -lxl


all: $(OBJS)
	$(CC) $(PROFILING) $(OBJS) -o $(OUT) $(LIB) $(INC) $(LFLAGS)


main.o: main.cpp include/block.h
	$(CC) $(FLAGS) $(WFLAGS) $(INC) main.cpp -lcppunit

include/certusPDF.o: include/certusPDF.cpp include/certusPDF.h include/colorMatching.hpp
	$(CC) $(FLAGS) $(WFLAGS) $(INC) include/certusPDF.cpp -o include/certusPDF.o -lcppunit

include/helpers.o: include/helpers.cpp include/helpers.h
	$(CC) $(FLAGS) $(WFLAGS) $(INC) include/helpers.cpp -o include/helpers.o -lcppunit

include/pdfBuffer.o: include/pdfBuffer.cpp include/pdfBuffer.h
	$(CC) $(FLAGS) $(WFLAGS) $(INC) include/pdfBuffer.cpp -o include/pdfBuffer.o -lcppunit

include/QrToPng.o: include/QrToPng.cpp include/QrToPng.h
	$(CC) $(FLAGS) $(WFLAGS) $(INC) include/QrToPng.cpp -o include/QrToPng.o -lcppunit

include/TinyPngOut.o: include/TinyPngOut.cpp include/TinyPngOut.hpp
	$(CC) $(FLAGS) $(WFLAGS) $(INC) include/TinyPngOut.cpp -o include/TinyPngOut.o -lcppunit

include/AnnotationsWriter.o: include/AnnotationsWriter.cpp include/AnnotationsWriter.h
	$(CC) $(FLAGS) $(WFLAGS) $(INC) include/AnnotationsWriter.cpp -o include/AnnotationsWriter.o -lcppunit

include/QrCode.o: include/QrCode.cpp include/QrCode.hpp
	$(CC) $(FLAGS) $(WFLAGS) $(INC) include/QrCode.cpp -o include/QrCode.o -lcppunit

include/base64.o: include/base64.cpp include/base64.h
	$(CC) $(FLAGS) $(WFLAGS) $(INC) include/base64.cpp -o include/base64.o -lcppunit


clean:
	rm -f $(OBJS) $(OUT)
