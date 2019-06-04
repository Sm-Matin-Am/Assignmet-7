CC := g++ -std=c++11
CFLAGS += -c

all: A7.out

response.o: ../utils/response.cpp ../utils/response.hpp ../utils/include.hpp
	$(CC) $(CFLAGS) -c ../utils/response.cpp -o response.o

request.o: ../utils/request.cpp ../utils/request.hpp ../utils/include.hpp ../utils/utilities.hpp
	$(CC) $(CFLAGS) -c ../utils/request.cpp -o request.o

utilities.o: ../utils/utilities.cpp ../utils/utilities.hpp
	$(CC) $(CFLAGS) -c ../utils/utilities.cpp -o utilities.o

server.o: ../server/server.cpp ../server/server.hpp ../server/route.hpp ../utils/utilities.hpp ../utils/response.hpp ../utils/request.hpp ../utils/include.hpp
	$(CC) $(CFLAGS) -c ../server/server.cpp -o server.o

route.o: ../server/route.cpp ../server/route.hpp ../utils/utilities.hpp ../utils/response.hpp ../utils/request.hpp ../utils/include.hpp
	$(CC) $(CFLAGS) -c ../server/route.cpp -o route.o

main.o: main.cpp systemInterface.hpp systemInterface.cpp handlers.hpp
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

handlers.o: handlers.cpp handlers.hpp systemInterface.hpp
	$(CC) $(CFLAGS) handlers.cpp -o handlers.o

A7.out: main.o customer.o publisher.o film.o filmRepository.o bank.o idSeter.o message.o comment.o exceptions.o commandDetails.o functions.o systemInterface.o handlers.o response.o request.o utilities.o server.o route.o
	$(CC) main.o customer.o publisher.o film.o filmRepository.o bank.o idSeter.o message.o comment.o exceptions.o commandDetails.o functions.o systemInterface.o 		handlers.o response.o request.o utilities.o server.o route.o -o A7.out

clean:
	rm -r *.o
