#include <vector>
#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
#include <iostream>
#include <algorithm>    // sort
#include <numeric> // accumulate
#include <iomanip>  //setprecision

static gzFile fp;
static  std::vector<int> rlen;


KSEQ_INIT(gzFile, gzread)
int readseqs(void);
int calc(void);

int main(int argc, char *argv[])
{ 

  if (argc == 1) {
   fprintf(stderr, "Usage: %s <reads.fq/fa>\n", argv[0]);
   return 1;
  }	
  if((fp = gzopen(argv[1],"r")) == NULL){ 
    printf("ERROR main:: missing input file  !! \n");
    return 1;
  }
  
  readseqs();
  calc();  

  return 0;
}

// ---------------------------------------- //
int calc()
// ---------------------------------------- //
{

  sort(rlen.begin(),  rlen.end(), std::greater<int>());

  int n=rlen.size();
  int max=rlen[0];                 	
  float bases = accumulate(rlen.begin(), rlen.end(), 0.0);
  float mean = bases / n;

  int n50=0,l50=0;
  int done=0;
  int t50=0;
  int ii=0;
  while(done<1){
    t50+=rlen[ii];
    if(t50 > bases*0.5) 
      done=1;
    ii++;
   }  
   n50=ii-1;  //counting from 0
   l50=rlen[n50]; 

  std::cout << std::fixed << std::setprecision(0) <<  "Bases= " << bases << " contigs= "<< n << " mean_length= " 
	<< mean << " longest= " << max << " l50= "<< l50 << " n50= " << n50+1   //counting from 1
	<< std::endl;  

  return 0;
}

// ---------------------------------------- //
int readseqs(){
// ---------------------------------------- //

  kseq_t *seq;
  int l=-1;
  seq = kseq_init(fp);
  rlen.reserve(200000);

  while ((l = kseq_read(seq)) >= 0) 
    rlen.push_back(seq->seq.l);
    
  kseq_destroy(seq);
  gzclose(fp);
  
 return 0;
}

