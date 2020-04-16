a.out : sanity_client.o A1_BF_PES1201800157.o
	gcc sanity_client.o A1_BF_PES1201800157.o -o a.out

sanity_client.o : sanity_client.c A1_BF_PES1201800157.c assignment_1.h
	gcc -c sanity_client.c -g

A1_BF_PES1201800157.o : A1_BF_PES1201800157.c assignment_1.h 
	gcc -c A1_BF_PES1201800157.c -g

clean:
	rm *.o a.exe