a.out : sanity_client.o A2_PES1201800157.o
	gcc sanity_client.o A2_PES1201800157.o -lm -o a.out

sanity_client.o : sanity_client.c A2_PES1201800157.c assignment_2.h
	gcc -c sanity_client.c -g -lm

A2_PES1201800157.o : A2_PES1201800157.c assignment_2.h 
	gcc -c A2_PES1201800157.c -g -lm

clean:
	rm *.o a.exe