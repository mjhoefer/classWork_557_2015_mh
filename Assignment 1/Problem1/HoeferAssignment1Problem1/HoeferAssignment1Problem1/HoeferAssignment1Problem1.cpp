//allows us to use the iostream library functions (cout)
#include <iostream>

// declares our current namespace, eliminates the need to specify functions
// from the std library "std::cout" can be replaced with "cout"
using namespace std;

double myFunction(int n);

// main function, starting point for every c++ program
int main(int argc, char *argv[])
{
	//declaring an integer and defining it as the result
	// of the function call "myFunction" with a argument of 10
	int p = myFunction(10);
	
	//this outputs p to the console,
	// with the value of whatever was returned by "myFunction"
	cout << p << endl;
	system("Pause");
	
}

//definition of myFunction
double myFunction(int n)
{
	// declares 4 integers (unsigned, so they can't be negative)
	// also initializes i to be 0 and j to be 1
	unsigned int i = 0, j = 1, t, k;

	// for loop, will loop through the code in brackets
	// n+1 number of times (until k>n). Sets k equal to zero,
	// increments k after each run through of the code
	for (k = 0; k <= n; ++k)
	{
		// set t equal to i plus j
		// first time: t = 1
		// second time: t = 2
		t = i + j;

		// set i equal to j
		// first time: i = 1
		// second time: i = 1
		i = j;

		//set j equal to t 
		// 0,1,2,3,4, 5, 6, 7, 8, 9, 10
		// 1,2,3,5,8,13,21,34,55,89,144
		j = t;
	}
	return j;
}