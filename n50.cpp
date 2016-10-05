#include <vector>
#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
#include <iostream>
#include <algorithm>    // sort
#include <numeric> // accumulate
#include <iomanip>  //setprecision
#include <fstream>

#include <gzstream.h>

static gzFile fp;
static  std::vector<int> rlen;


KSEQ_INIT(gzFile, gzread)
int readseqs(void);
int calc(void);
int myread(char* file);

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

  
  int mlines=myread(argv[1]); //does not work with seq on multi-lines! but a lot faster!
  //int mlines=1;
  if(mlines)
  	readseqs();
  calc();  

  return 0;
}

// ---------------------------------------- //
int calc()
// ---------------------------------------- //
{
  int pri=0;

  if(pri)std::cout<< "Now calc " << std::endl;
  sort(rlen.begin(),  rlen.end(), std::greater<int>());

  int n=rlen.size();
  if(pri)std::cout << "number of contigs/reads " << n << std::endl;
  int max=rlen[0];                 	
  float bases = accumulate(rlen.begin(), rlen.end(), 0.0);
  if(pri)std::cout << "bases " << bases <<  std::endl;
  float mean = bases / n;
  if(pri)std::cout << "mean " << mean <<  std::endl;

  int n50=0,l50=0;
  int done=0;
  long int t50=0;
  int ii=0;
  while(done<1){
    if(pri)if(ii>3693240) std::cout << ii << std::endl;
    t50+=rlen[ii];
    if(pri)if(ii>3693240) std::cout << " " << t50 << std::endl;
    if(t50 > bases*0.5) 
      done=1;
    if(pri)if(ii>3693240) std::cout << " " << done << std::endl;
    ii++;
   }
  if(pri)std::cout << "t50 " << t50<< " ii " << ii  <<  std::endl;

  n50=ii-1;  //counting from 0
  l50=rlen[n50]; 
  if(pri)std::cout << "n50 " << n50 << " l50 " << l50 <<  std::endl;


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
  rlen.reserve(300000);

  if(0)std::cout << " ...using kseq to read file" << std::endl;

  while ((l = kseq_read(seq)) >= 0) 
    rlen.push_back(seq->seq.l);
    
  kseq_destroy(seq);
  gzclose(fp);
  
 return 0;
}

// ---------------------------------------- //
int myread(char* file)   //FILE *namef)
// ---------------------------------------- //
{ // won't work with seq on multilines!
  char fq[5]={"@"};
  char fa[5]={">"};
  char plus[5]={"+"};
  int readevery=1;
  int pri=0;
  //std::ifstream infile(file);
  rlen.reserve(300000);
  igzstream infile(file);

/*
  std::string line;
  getline(infile1,line); //first line: name
  if(line.at(0)==fq[0] || line.at(0)==fa[0]){
        infile.clear();  // start reading from first line again
        infile.seekg (0, std::ios::beg);
	std::ifstream infile(file);
  }else{
        if(pri)std::cout << " Error: cannot determine if input file is fasta or fastq, probably a gzipped file?" << std::endl;
        infile.close();
//      igzstream infile(file); 
        //return(1);
  }*/

  int isfq=0;
  int nseq=0;
  while (!infile.eof()){
    std::string seq;
    std::string name;
    std::string line;
    nseq++;
    getline(infile,name);
    getline(infile,seq);

    if(0)if(nseq<5)std::cout << nseq << " " << name << " " << seq.length() << std::endl;
    if(seq.length())rlen.push_back(seq.length());

    if(isfq) { 
          getline(infile,line);
          getline(infile,seq);
          if(0)if(nseq<5)std::cout << nseq << " " << name << " " << line << std::endl;
    }

    if(nseq==1){
        getline(infile,line);
        if(line.at(0)==plus[0]) isfq=1;
	if( !isfq && line.at(0)!=fa[0]) {
		if(pri)std::cout<< "Sequences on multiple lines..." << std::endl;  // seq on single line 
		rlen.clear();
	        return(1);
	}
	getline(infile,line);
	if(!isfq)rlen.push_back(line.length());
    }

  }
  if(pri)std::cout << "Total sequences: " << nseq << std::endl;


 return 0;
}

