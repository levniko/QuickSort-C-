#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<algorithm>	
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>
using namespace std;
struct Node
{
	string country;
	string item;
	string order;
	int sold;
	float profit;
};
int partition(struct Node array[], int start, int finish)
{
    struct Node pivot = array[finish];    // pivot
    int i = (start - 1);  // Index of smaller element
 
    for (int j = start; j <= finish- 1; j++)
    {
        
        if (array[j].country < pivot.country) // If current element is smaller aflphabetically than pivot 
        {
            i++;    // increment index of smaller element
            swap(array[i], array[j]);	//swap them
        }
		else if(array[j].country==pivot.country) // If current element country and pivot's  country are same
		{
	    	if(array[j].profit > pivot.profit)	// Descending order with profit same country
			{				    		
			    i++;							//increment index of smaller element
				swap(array[i], array[j]);			// swap them
			}
		}
    }
    swap(array[i + 1], array[finish]);
    return (i + 1);
}

void quickSort(struct Node array[], int start, int finish)
{
    if (start < finish)
    {
        int pivot = partition(array, start, finish);
        quickSort(array, start, pivot - 1);  // Recursion Left of the pivot 
        quickSort(array, pivot + 1, finish); // Recursion right of the pivot
    }
}
int frequency_of_primes (int n) {
  int i,j;
  int freq=n-1;
  for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
  return freq;
}
int main(int argc, char *argv[]) {
	
    ifstream file;
	file.open("sales.txt");

	if (!file) {
		cerr << "File cannot be opened!";
		exit(1);
	}

	//const int N = atoi(argv[1]); //you should read value of N from command line
	int N = 100;
	string line;
	struct Node *myArr = new struct Node[N]; // Dynamic memory allocation
	getline(file, line); //this is the header line
    clock_t t;
	int f;
	t = clock();
	for (int i = 0; i < N; i++) {

		getline(file, line, '\t'); //country (string)
		string country = line;
		myArr[i].country=country;
		getline(file, line, '\t'); //item type (string)
		string item = line;
		myArr[i].item = item;
		getline(file, line, '\t'); //order id (string)
		string order = line;
		myArr[i].order=order;
		file >>	myArr[i].sold; //units sold (integer)	
		file >> myArr[i].profit; //total profit (float)
		getline(file, line, '\n'); //this is for reading the \n character into dummy variable.
	}
	cout<<"Calculating running time...\n"<<endl;
    f = frequency_of_primes (99999);
	quickSort(myArr,0,N-1); // Call quicksort
	ofstream myfile;	
	myfile.open ("sorted.txt");
	for(int i = 0; i < N; i++){	///  Writing to the txt file
		myfile << myArr[i].country<<"\t"<<myArr[i].item<<"\t"<<myArr[i].order<<"\t"<<myArr[i].sold<<"\t"<<myArr[i].profit<<"\t"<<endl;
	}
	myfile.close(); // Close file
    t = clock() - t;
 	printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	delete [] myArr; // delete array
	return 0;
}

