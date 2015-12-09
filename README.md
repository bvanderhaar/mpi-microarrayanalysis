## Abstract
Analysis of gene microarray data to test for gene expression of renal disease.  Two versions of the program are analyzed - one executed serially on a single system and another using MPI on multiple systems.  Results indicate the MPI version is significantly faster.

## High Level Design
The gene data is read from a CSV file and processed row by row.  Each row processing generates 1000 permutations of the t-stats to normalize the data.
The MPI version returns the D-score value based on the row processed.  The results are combined serially, then printed out.

## Implementation
A serial version is compiled with Clang/LLVM with the C++14 standard libraries and spec on a MacBook Pro. The MPI version is compiled with the GNU C compiler with C++14 standard library on EOS machines running Fedora Linux.  The math and gene analysis functions are shared between the two programs.  

## Testing Methodology
The C++ clock API is used to record running time. Reading the file from disk and putting the values into a typed vector are ignored in both programs.  A 13" 2015 MacBook Pro and a 15" 2012 MacBook Pro were used for the serial program time test.  Three EOS machines were used to execute the program using MPI.

## Discussion
Level 2 optimizations resulted in almost a three-fold speed up in the serial version.


## Conclusion
