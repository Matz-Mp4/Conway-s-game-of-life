all: VidaApp VidaController VidaModel VidaView VidaArquivoView VidaArquivoModel Lista

Lista: Lista.c Lista.h
	gcc -c Lista.c

VidaModel: VidaModel.c VidaModel.h
	gcc -c VidaModel.c -lncurses

VidaArquivoModel: VidaArquivoModel.c VidaArquivoModel.h
	gcc -c VidaArquivoModel.c -lncurses


VidaView: VidaView.c VidaView.h
	gcc -c VidaView.c -lncurses

VidaViewArquivo: VidaArquivoView.c VidaArquivoView.h
	gcc -c VidaArquivoView.c -lncurses


VidaController: VidaController.c VidaController.h
	gcc -c VidaController.c -lncurses

VidaApp: VidaApp.c Lista.o VidaModel.o VidaController.o VidaView.o  VidaArquivoView.o VidaArquivoModel.o
	gcc -o VidaApp VidaApp.c Lista.o VidaModel.o  VidaView.o VidaArquivoModel.o VidaArquivoView.o  VidaController.o -lncurses
