CC := g++ -std=c++11
CFLAGS += -c

all: A7.out

A7.out: main.o customer.o publisher.o film.o filmRepository.o bank.o idSeter.o message.o comment.o exceptions.o commandDetails.o functions.o systemInterface.o
	$(CC) main.o customer.o publisher.o film.o filmRepository.o bank.o idSeter.o message.o comment.o exceptions.o commandDetails.o functions.o systemInterface.o -o A7.out

main.o: main.cpp systemInterface.hpp systemInterface.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

systemInterface.o: systemInterface.cpp systemInterface.hpp customer.hpp publisher.hpp film.hpp filmRepository.hpp bank.hpp idSeter.hpp exceptions.hpp commandDetails.hpp functions.hpp
	$(CC) $(CFLAGS) systemInterface.cpp -o systemInterface.o

customer.o: customer.hpp customer.cpp film.hpp message.hpp comment.hpp exceptions.hpp functions.hpp
	$(CC) $(CFLAGS) customer.cpp -o customer.o

publisher.o: customer.hpp publisher.hpp publisher.cpp film.hpp message.hpp comment.hpp exceptions.hpp functions.hpp
	$(CC) $(CFLAGS) publisher.cpp -o publisher.o

film.o: customer.hpp publisher.hpp film.hpp film.cpp filmRepository.hpp message.hpp comment.hpp exceptions.hpp functions.hpp
	$(CC) $(CFLAGS) film.cpp -o film.o

filmRepository.o: customer.hpp publisher.hpp film.hpp filmRepository.hpp filmRepository.cpp comment.hpp exceptions.hpp
	$(CC) -c filmRepository.cpp -o filmRepository.o

bank.o: bank.hpp bank.cpp
	$(CC) $(CFLAGS) bank.cpp -o bank.o

idSeter.o: idSeter.hpp idSeter.cpp
	$(CC) $(CFLAGS) idSeter.cpp -o idSeter.o

message.o: message.hpp message.cpp
	$(CC) $(CFLAGS) message.cpp -o message.o

comment.o: comment.hpp comment.cpp
	$(CC) $(CFLAGS) comment.cpp -o comment.o

exceptions.o: exceptions.cpp exceptions.hpp
	$(CC) $(CFLAGS) exceptions.cpp -o exceptions.o

commandDetails.o: commandDetails.cpp commandDetails.hpp
	$(CC) $(CFLAGS) commandDetails.cpp -o commandDetails.o

functions.o: customer.hpp publisher.hpp film.hpp exceptions.hpp functions.hpp functions.cpp systemInterface.hpp
	$(CC) $(CFLAGS) functions.cpp -o functions.o

clean:
	rm -r *.o