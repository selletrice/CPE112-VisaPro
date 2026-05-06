CC = gcc
CFLAGS = -Wall -g
OBJ = main.o document_logic.o student_db.o process_manager.o

VisaPro: $(OBJ)
	$(CC) $(OBJ) -o VisaPro

main.o: main.c visa_pro.h
	$(CC) $(CFLAGS) -c main.c

document_logic.o: document_logic.c visa_pro.h
	$(CC) $(CFLAGS) -c document_logic.c

student_db.o: student_db.c visa_pro.h
	$(CC) $(CFLAGS) -c student_db.c

process_manager.o: process_manager.c visa_pro.h
	$(CC) $(CFLAGS) -c process_manager.c

clean:
	del /f /q *.o VisaPro.exe