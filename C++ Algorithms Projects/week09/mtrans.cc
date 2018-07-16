
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::list;
using std::vector;
using std::istringstream;
using std::ostream;

#include <math.h>
#include <stdlib.h>

class nz {	    // one instance for every non-zero entry in matrix
public:
  nz() { ind = 0; val = 0.0; }
  nz(int i, double v) {	// constructor when given the two items of data
    ind = i;
    val = v;
  }
  int getInd() const { return ind; } // access to ind class member
  double getVal() const { return val; } // access to val class member
  friend istringstream& operator>>(istringstream& is, nz& base);
  friend ostream& operator<<(ostream &os, const nz& base);

private:
  int ind;
  double val;
};
istringstream& operator>>(istringstream& is, nz& base)
{
  is>> base.ind;
  is>> base.val;
  return is;
}
ostream& operator<<(ostream &os,const nz& base)
{
  os<< base.ind<< " "<< base.val<< " ";
  return os;
}

typedef list<nz> sparseRow;
typedef vector<sparseRow> sparseMat;

void readMat(sparseMat&, int&);
void transpMat(const sparseMat, sparseMat&);

double epsilon = 0.0;

int main(int argc, char *argv[])
{
  int nzct;
  sparseMat rows;
  readMat(rows, nzct);

  vector<sparseRow> transp;
  transpMat(rows, transp);

  // now write out
  vector<sparseRow>::const_iterator rit; // we only want to /read/ list
  for (rit = transp.begin(); rit != transp.end(); rit++)
  {
    sparseRow row = *rit;
    // iterate over this row, only /read/
    sparseRow::const_iterator nzit;
    for (nzit = row.begin(); nzit != row.end(); nzit++)
    {
      cout<< *nzit;
    }

    cout<< endl;
  }
}

void readMat(sparseMat& rows, int& nzct)
{
  nzct = 0;
  string line;
  while (getline(cin, line))	// get next full line of text; NB: text
  {
    istringstream lstream(line) ;
    sparseRow row;

    nz next;
    while (lstream>> next) { // peel off values in this line, one at a time
      row.push_back(next);
      nzct++;
    }

    rows.push_back(row);
  }
}

void transpMat(const sparseMat rows, sparseMat& transp)
{
  for (unsigned int c = 0; c < rows.size(); c++)	// square matrix
  {
    sparseRow row;
    transp.push_back(row);	// initialise every row of transpose
  }

  vector<sparseRow>::const_iterator rit; // we only want to /read/ list
  int rowind;
  for (rit = rows.begin(), rowind = 1; rit != rows.end(); rit++, rowind++)
  {
    sparseRow row = *rit;
    sparseRow::const_iterator nzit;
    for (nzit = row.begin(); nzit != row.end(); nzit++)
    {
      int col = nzit->getInd();
      double val = nzit->getVal();
      transp[col-1].push_back(nz(rowind,val));
      //      cout<< "Put val from "<< rowind<< " on col "<< col<< endl;
    }
  }
}

// http://www.codersource.net/c/c-miscellaneous/overloading-stream-operators.aspx
