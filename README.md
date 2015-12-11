## Abstract
Analysis of gene microarray data to test for gene expression of renal disease.  Two versions of the program are analyzed - one executed serially on a single system and another using MPI on multiple systems.  Results give a speed up in the MPI version run on multiple machines.

## High Level Design
The gene data is read from a CSV file and processed row by row.  Each row processing generates 1000 permutations of the t-stats to normalize the data.
The MPI version returns the D-score value based on the row processed.

## Implementation
A serial version is compiled with Clang/LLVM with the option "-std=c++14" on a MacBook Pro. The MPI version is compiled with the GNU C compiler with options "-std=c++11" standard library on EOS machines running Fedora Linux.  The math and gene analysis functions are shared between the two programs.  In the MPI version, the MPI_Irecv function is used to receive results asynchronously. Once all results are available, the resulting buffers are put into a result array and printed out.

## Testing Methodology
The C++ clock API is used to record running time in the serial program.  MPI_Wtime is used to record running time in the MPI version of the code. Reading the file from disk and putting the values into a typed vector are ignored in both programs.  A 13" 2015 MacBook Pro was used as the control for the serial program.  Three EOS machines were used to execute the program using MPI.

## Discussion
The MPI version resulted in an observed 1.5-10x speedup.  Due to the independent nature of the problem, more speedup is expected. The MPI code used to run this simulation could be optimized further.  Rows could be sent one by one instead of sending the entire set of data to each host.  In addition, compiler optimizations could be used to speed up execution.  More efficient communication could also be used to send the result back.  Synchronous communication may make more sense for this problem.

## Conclusion
The MPI_Irecv function may not be the ideal way to maximize performance in this scenario.  However, asynchronous communication can be very powerful with other problem sets.
