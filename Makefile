VisaPro: main.o document_logic.o student_db.o process_manager.o
	gcc main.o document_logic.o student_db.o process_manager.o -o VisaPro

main.o: main.c
	gcc -c main.c

document_logic.o: document_logic.c visa_pro.h
	gcc -c document_logic.c

student_db.o: student_db.c visa_pro.h
	gcc -c student_db.c

process_manager.o: process_manager.c visa_pro.h
	gcc -c process_manager.c

clean:
	rm *.o VisaPro