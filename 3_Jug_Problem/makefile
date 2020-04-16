a.out : A3_client_PES1201800157.o A3_impl_PES1201800157.o
	gcc A3_client_PES1201800157.o A3_impl_PES1201800157.o -o a.out

A3_client_PES1201800157.o : A3_client_PES1201800157.c A3_impl_PES1201800157.c A3_header_PES1201800157.h
	gcc -c A3_client_PES1201800157.c -g 

A3_impl_PES1201800157.o : A3_impl_PES1201800157.c A3_header_PES1201800157.h 
	gcc -c A3_impl_PES1201800157.c -g 

clean:
	rm *.o a.exe