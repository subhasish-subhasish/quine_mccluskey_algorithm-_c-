#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

//Functions
int numberOfOneCount(vector<int> a);//count no of 1
void printVector(const vector<int> v); //function for print vector
void printSet(const set<int> s); //fuction for printset
set<int> mergeSets(const set<int>& set1, const set<int>& set2); // Function to merge two sets
pair<int,vector<int>> minTermCount (int minTerm,int variable);
vector<int> dataCollection(int noMinterm,int noVariable); // function for data collection and put in a vector
class Data{
    public:
    int numberOfOnes;
    vector<int> binValue;  // The number of 1s in the binary representation
    set<int> minterms; // Minterms covered by this term
    bool isCombined=false;    // Flag to check if this term has been combined
    bool isPrimeImplicant=false;  // Flag to check if this term is a prime implicant
    void print(){
        cout<<"Number Of Ones :"<<numberOfOnes<<endl;
        cout<<"Binary value :";
        printVector(binValue);
        cout<<"Minterm :";
        printSet(minterms);
    }
};

bool canCombine(const Data &a,const Data &b,Data &result); //function collection data and marge them in one pair and return true else false;
vector<Data> quineMcCluskey(vector<Data> &grid,int noVariable); //function for quineMcCluskey Algo
void removeSameMinterm(vector<Data> &grid);//function for remove all same minterm

int main(){
    int noMinterm,noVarible;
    cout<<"Enter Number of Minterm :";cin>>noMinterm;
	cout<<"Enter Number Of varable :";cin>>noVarible;
	vector<int> minTermArray=dataCollection(noMinterm,noVarible);
    vector<Data> grid(noMinterm);
    for(int i=0;i<noMinterm;i++){
        pair<int,vector<int>> a = minTermCount(minTermArray[i],noVarible);
        grid[i].binValue=a.second;
        grid[i].numberOfOnes=a.first;
        grid[i].minterms.insert(minTermArray[i]);
    }
    
    vector<Data> primeImplicants = quineMcCluskey(grid, noVarible);
    removeSameMinterm(primeImplicants);
    // Print Prime Implicants
    cout << "\nPrime Implicants:\n";
    for (auto& term : primeImplicants) {
        term.print();
        cout << "------------------------\n";
    }
    
    return 0;
}

void printVector(const vector<int> v){
    cout<<"[ ";
	for (int i=0;i<v.size();i++){cout<<v[i]<< " ";}
    cout<<"]"<<endl;
}
void printSet(const set<int> s){
    cout<<"( ";
    for (int num : s){cout << num << " ";}
    cout<<")"<<endl;
}
set<int> mergeSets(const set<int>& set1, const set<int>& set2) {
    set<int> resultSet = set1;  // Copy set1 into resultSet
    resultSet.insert(set2.begin(), set2.end());  // Insert elements from set2 into resultSet
    return resultSet;  // Return the merged set
}
pair<int,vector<int>> minTermCount (int minTerm,int variable){
    vector<int> minTermVector;
    int onesCount =0; //count no one present in kamp
    for (int i = 0; i < variable; i++){
        //if one is there t
		if (minTerm & 1 << (variable - i - 1)){
			minTermVector.push_back(1); 
			onesCount++; 
		}
		else{
			minTermVector.push_back(0);
		}
	}
    pair<int,vector<int>> minTermAndCount; 
	minTermAndCount.first = onesCount;
	minTermAndCount.second =minTermVector;

	return minTermAndCount;
}
vector<int> dataCollection(int noMinterm,int noVariable){
    vector<int> minTermArray;
	cout<<"Enter All minterm :";
	for(int i=0;i<noMinterm;i++){
		int minterm;
		cin>>minterm;
		minTermArray.push_back(minterm);
	}
    return minTermArray;
}
bool canCombine(const Data &a,const Data &b,Data &result){
    if(abs(a.numberOfOnes-b.numberOfOnes)!=1) return false;

    int diffCount=0;
    vector<int> combineBinvalue=a.binValue;//store comibe binary value of two term
    for(int i=0;i<a.binValue.size();i++){
        if(a.binValue[i]!=b.binValue[i]){
            diffCount++;
            if(diffCount>1) return false;
            combineBinvalue[i]=-1; //marking the difference as -1 for dont care
        }
    }
    result.binValue=combineBinvalue;
    result.numberOfOnes=numberOfOneCount(combineBinvalue);
    result.minterms=mergeSets(a.minterms,b.minterms);
    return true;
}
vector<Data> quineMcCluskey(vector<Data>& grid, int noVarible) {
    vector<Data> combinedTerms;
    bool termsCombined = false;

    // Pairwise comparison of terms to combine them
    for (int i = 0; i < grid.size(); i++) {
        for (int j = i + 1; j < grid.size(); j++) {
            Data newTerm;
            if (canCombine(grid[i], grid[j], newTerm)) {
                grid[i].isCombined = true;
                grid[j].isCombined = true;
                combinedTerms.push_back(newTerm);
                termsCombined = true;
            }
        }
    }

    // Mark uncombined terms as prime implicants
    for (auto& term : grid) {
        if (!term.isCombined) {
            term.isPrimeImplicant = true;
        }
    }

    // If no further combinations, return prime implicants
    if (!termsCombined) return grid;

    // Recursively combine further if needed
    vector<Data> nextIteration = quineMcCluskey(combinedTerms, noVarible);
    
    // Collect uncombined prime implicants from the current grid and return
    for (auto& term : grid) {
        if (term.isPrimeImplicant) {
            nextIteration.push_back(term);
        }
    }
    return nextIteration;
}
void removeSameMinterm(vector<Data> &grid){
    for(int i=0;i<grid.size();i++){
        set<int> val1=grid[i].minterms;
        for(int j=i+1;j<grid.size();j++){
            set<int> val2=grid[j].minterms;
            if(val1==val2){
                grid.erase(grid.begin()+j);
           }
        }
    }
    return;
}
int numberOfOneCount(vector<int> a){
    int count=0;
    for(int i=0;i<=a.size();i++){
        if(a[i]==1) count++;
        
    }
    return count;
}