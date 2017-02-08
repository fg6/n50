# n50
C++ code to evaluate basic stats for a fasta/fastq(.gz) file

Usage: ./n50 \<reads.fastq/fasta(.gz)\>


Requirements:
- gzstream in the CPLUS_INCLUDE_PATH
  
To compile:
- source ./compile.sh 
  this will check if gzstream is available in the CPLUS_INCLUDE_PATH and them compile
  otherwise please include the full path to gzstream in the mygzstream on the first line of compile.sh
