#include <iomanip>  //setprecision
#include <algorithm>    // sort, reverse
#include <gzstream.h>
#include <vector>  //setprecision


using std::cout;
using std::endl;
using std::vector;
using std::string;

static gzFile fp;
static  vector<int> rlen;
static  vector<string> rseq;
static  vector<string> rqual;
static  vector<string> rname;
static  vector<string> rcomment;


// ---------------------------------------- //
int fasttype(char* file)
// ---------------------------------------- //
{ 
  char fq[5]={"@"};
  char fa[5]={">"};
  string ttname;
  int isfq=0;
  igzstream infile(file);

  getline(infile,ttname);
  string ftype=ttname.substr(0,1);
  if(ftype==fa) isfq=0;
  else isfq=1;

  return(isfq);
}


// ---------------------------------------- //
int readfastq(char* file, int saveinfo=0, int readseq=0, int minlen=0, string selctg="")
// ---------------------------------------- //
{ 
  igzstream infile(file);
  char fq[5]={"@"};
  char fa[5]={">"};
  char plus[5]={"+"};
  int nseq=0;

 
  rlen.reserve(100000);
  rname.reserve(100000);
  if(readseq){
    rseq.reserve(100000);
    rqual.reserve(100000);
  }


  string read;
  string lname;
  string lcomment="";   
  string lseq="";
  int seqlen=0;
  int quallen=0;
  string lqual;
  int seqlines=0;


  int stop=1;
  while(stop){
    getline(infile,read);
    
    if(read.substr(0,1)==fq){  // name
      nseq++;

      if(nseq>1){ // previous
	if(seqlen>=minlen){

	  if(saveinfo){
	    rname.push_back(lname);
	    if(lcomment.size())rcomment.push_back(lcomment);
	    rlen.push_back(seqlen);
	    if(readseq)rseq.push_back(lseq);
	    if(readseq)rqual.push_back(lqual);
	  }


	  //cout << fa << lname ;
	  // if(lcomment.size()) cout << lcomment <<endl;
	  // else cout << endl;
	  
	  
	  if(quallen != seqlen)
	    cout << " ERROR! seq length different from quality lenght!! " << endl;
	}
      }
      
      size_t ns=0;
      size_t nt=0;
      ns=read.find(" ");
      nt=read.find("\t");

      if(ns!=std::string::npos) { 
	lname=read.substr(1,ns);
	lcomment=read.substr(ns+1,read.size());
      }else if(nt!=std::string::npos) {
	lname=read.substr(1,nt);
	lcomment=read.substr(nt+1,read.size());
      }else{
	lname=read.erase(0,1);
      }
      if(readseq){
	lseq="";
	lqual="";
      }
      seqlen=0;
      seqlines=0;
      quallen=0;
    }else if(read.substr(0,1)==plus){ // + and qual

      for(int ll=0; ll<seqlines; ll++){
	getline(infile,read);
	if(readseq)lqual.append(read);
	quallen+=read.size();
      }
    }else{ // sequence 
      if(readseq)lseq.append(read);
      seqlines++;
      seqlen+=read.size();
    }
 
    // EOF
    if(infile.eof()){ // previous
      if(seqlen>=minlen){

	if(saveinfo){
	  rname.push_back(lname);
	  if(lcomment.size())rcomment.push_back(lcomment);
	  rlen.push_back(seqlen);
	  if(readseq)rseq.push_back(lseq);
	  if(readseq)rqual.push_back(lqual);
	}
	if(quallen != seqlen)
	  cout << " ERROR! seq length different from quality lenght!! " << endl;
      }
      stop=0;
    }


  }//read loop
 
  return 0;
}


// ---------------------------------------- //
int readfasta(char* file, int saveinfo=0, int readseq=0, int minlen=0, string selctg="")
// ---------------------------------------- //
{ 
  igzstream infile(file);
  char fa[5]={">"};
  int nseq=0;

  rlen.reserve(100000);
  rname.reserve(100000);
  if(readseq)
    rseq.reserve(100000);


  string read;
  string lname;
  string lcomment="";   
  string lseq="";
  int seqlen=0;

  int stop=1;
  while(stop){
    getline(infile,read);
    
    if(read.substr(0,1)==fa){  // name
      nseq++;

      if(nseq>1){ // previous
	if(seqlen>=minlen){

	  if(saveinfo){
	    rname.push_back(lname);
	    rlen.push_back(seqlen);
	    if(readseq)rseq.push_back(lseq);
	    if(lcomment.size())rcomment.push_back(lcomment);
	  }


	}
      }
      
      size_t ns=0;
      size_t nt=0;
      ns=read.find(" ");
      nt=read.find("\t");

      if(ns!=std::string::npos) { 
	lname=read.substr(1,ns);
	lcomment=read.substr(ns+1,read.size());
      }else if(nt!=std::string::npos) {
	lname=read.substr(1,nt);
	lcomment=read.substr(nt+1,read.size());
      }else{
	lname=read.erase(0,1);
      }
      if(readseq)lseq="";
      seqlen=0;

    }else{ // sequence 
      if(readseq)lseq.append(read);
      seqlen+=read.size();
    }
 
    // EOF
    if(infile.eof()){ // previous
      if(seqlen>=minlen){


	if(saveinfo){
	  rname.push_back(lname);
	  rlen.push_back(seqlen);
	  if(readseq)rseq.push_back(lseq);
	  if(lcomment.size())rcomment.push_back(lcomment);
	}      


      }
      stop=0;
    }


  }//read loop
 
  return 0;
}

