if [ ! -f NCI-60.csv ]; then
 curl -O http://www.cis.gvsu.edu/~wolffe/courses/cs677/projects/NCI-60.csv
fi
if [[ $OSTYPE == darwin* ]]; then
  clang-format -i cpu-microarrayanalysis.cpp mpi-microarrayanalysis.cpp BVshared.cpp
  clang++ --std=c++11 cpu-microarrayanalysis.cpp BVshared.cpp -o cpu-microarrayanalysis
  mpic++ --std=c++11 mpi-microarrayanalysis.cpp BVshared.cpp -o mpi-microarrayanalysis
  chmod +x mpi-microarrayanalysis
  chmod +x cpu-microarrayanalysis
fi
if [[ $OSTYPE == linux* ]]; then
  mpic++ --std=c++11 mpi-microarrayanalysis.cpp -o mpi-microarrayanalysis
  chmod +x mpi-microarrayanalysis.cpp
fi
