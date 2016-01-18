
./bin/max_calcul: ./obj/max_calcul.o ./obj/max_func.o
	gcc -o $@ $^

./obj/max_calcul.o : ./include/max_func.h

./obj/%.o: ./src/%.c
	gcc -o $@ -c $<

clean:
	rm -rf ./obj/*.o ./bin/max_calcul


