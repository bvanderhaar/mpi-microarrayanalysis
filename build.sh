if [[ $OSTYPE == darwin* ]]; then
  clang-format -i microarrayanalysis.cpp
  mpic++ --std=c++11 microarrayanalysis.cpp -o microarrayanalysis
  chmod +x microarrayanalysis.cpp
fi
if [[ $OSTYPE == linux* ]]; then
  mpic++ --std=c++11 microarrayanalysis.cpp -o microarrayanalysis
  chmod +x microarrayanalysis.cpp
fi
