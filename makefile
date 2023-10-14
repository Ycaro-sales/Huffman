
build:
	gcc -Wall ./core/compress.c ./core/decompress.c ./core/huffman_file.c ./core/huffman_tree.c ./models/max_heap.c ./models/hashtable.c ./models/list.c ./utils.c main.c -o ./main -g

clean:
	rm -rf bin

run:
	./bin/main
