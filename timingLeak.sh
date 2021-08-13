g++ -o out assembly_parser.cpp
for (( i = 0; i < 1000; i++ )); do
	c="output"
	c+=$i
	./out $c
done