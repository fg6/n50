#include "readfastaq.h"
#include <numeric> // accumulate


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

  int err=1;

  // File type	
  int isfq=fasttype(argv[1]);

  if(!isfq)
     err=readfasta(argv[1],1); // save info (contig names and length) in vectors
  else
     err=readfastq(argv[1],1);

  if(!err)calc();  

  return 0;
}


// ---------------------------------------- //
int calc()
// ---------------------------------------- //
{
  sort(rlen.begin(),  rlen.end(), std::greater<int>());

  int n=rlen.size();
  int max=rlen[0];                 	
  long int  bases = accumulate(rlen.begin(), rlen.end(), 0.0);
  float mean = bases*1. / n;

  int n50=0,l50=0;
  int done=0;
  long int t50=0;
  int ii=0;
  while(done<1){
    t50+=rlen[ii];
    if(t50 > bases*0.5) 
      done=1;
    ii++;
   }

  n50=ii;
  l50=rlen[n50-1];  //counting from 0
  
  std::cout << std::fixed << std::setprecision(0) <<  "Bases= " << bases << " contigs= "<< n << " mean_length= " 
	<< mean << " longest= " << max << " N50= "<< l50 << " n= " << n50   //counting from 1
	<< std::endl;  

  return 0;
}

