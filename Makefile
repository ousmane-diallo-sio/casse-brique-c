casse-brique: main.o ./services/clean_stdin.o ./services/console_msg.o ./services/general.o ./network/client.o ./network/server.o ./maps/map.o ./game/play.o
	gcc main.o clean_stdin.o console_msg.o general.o client.o server.o map.o play.o -o casse-brique

main.o: main.c
	gcc -c main.c

./services/clean_stdin.o: ./services/clean_stdin.c ./services/clean_stdin.h
	gcc -c ./services/clean_stdin.c

./services/console_msg.o: ./services/console_msg.c ./services/console_msg.h
	gcc -c ./services/console_msg.c

./services/general.o: ./services/general.c ./services/general.h
	gcc -c ./services/general.c

./network/client.o: ./network/client.c ./network/client.h
	gcc -c ./network/client.c

./network/server.o: ./network/server.c ./network/server.h
	gcc -c ./network/server.c

./maps/map.o: ./maps/map.c ./maps/map.h
	gcc -c ./maps/map.c

./game/play.o: ./game/play.c ./game/play.h
	gcc -c ./game/play.c

clean:
	rm *.o casse-brique

run:
	make && ./casse-brique

clean_run:
	make && ./casse-brique && make clean



