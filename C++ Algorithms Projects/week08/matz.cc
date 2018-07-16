#include <cmath>
#include <sstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    int column = 1;
    ostringstream oss;
    double epsilon = 0;
    /*
       If there are more than 1 arguments and the second argument is -e then the
       epsilon command is used and the value of epsilon will be the third argument.
    */
    if(argc > 1 && string(argv[1]) == "-e")
        epsilon = fabs(strtod(argv[2], 0));
    /*
       While the input file has a new line, a new stringstream is created for each line.
    */
    while(getline(cin, line))
    {
        istringstream lstream(line) ;
        double val;
        /*
           While the line has a value, it will check if the value is outside the epsilon range,
           if it is the column and the corresponding value will be added to the stringstream.
        */
        while(lstream >> val)
        {
            if(val > epsilon || val < (-1 * epsilon))
                oss << column << " " << val << " ";
             column++;
        }
        column = 1;
        oss << endl;
    }
    cout << oss.str();
    return 0;
}
