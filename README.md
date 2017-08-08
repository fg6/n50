# n50
C++ code to evaluate basic stats for a fasta/fastq(.gz) file

Usage: ./n50 \<reads.fastq/fasta(.gz)\>


Requirements:
- zlib
- tested with gcc 4.9.2
  
To compile:
- ./install.sh

Output:
- Bases: total number of bases found in the file
- contigs: total number of contigs/scaffolds/reads found
- mean_length: mean lenght of contigs/scaffolds/reads
- longest: longest contig/scaffold/read
- N50: contig/scaffold/read N50
- n: number of contigs/scaffolds/reads contributing to the N50
