# ----- test vector ----- #
make test_vector.o
make test_distance.o
echo ""
./core/lib/test_vector.o
./core/lib/test_distance.o

make clean
