a.out : client.o A4_PES1201800157.o
	gcc client.o A4_PES1201800157.o -o a.out

client.o : client.c A4_PES1201800157.c assignment_4.h
	gcc -c client.c -g

A4_PES1201800157.o : A4_PES1201800157.c assignment_4.h 
	gcc -c A4_PES1201800157.c -g

clean:
	rm *.o a.exe
