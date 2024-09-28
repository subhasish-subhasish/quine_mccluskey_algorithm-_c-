#include <iostream>
using namespace std;
#include <vector>
#include <set>
#include <map>
void printVector(const vector<int> v);
void printSet(const set<int> s);
int numberOfOneCount(vector<int> a);
set<int> mergeSets(const set<int>& set1, const set<int>& set2);
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
bool canCombine(const Data &a,const Data &b,Data &result);
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
int main(){
    Data a,b,c,d,e,f,g,h,ans;
    a.numberOfOnes=1;a.binValue={0,0,0,1};a.minterms={1};
    b.numberOfOnes=2;b.binValue={0,0,1,1};b.minterms={3};
    c.numberOfOnes=1;c.binValue={0,1,0,0};c.minterms={4};
    d.numberOfOnes=2;d.binValue={0,1,0,1};d.minterms={5};
    e.numberOfOnes=2;e.binValue={0,1,1,0};e.minterms={6};
    f.numberOfOnes=3;f.binValue={0,1,1,1};f.minterms={7};
    g.numberOfOnes=2;g.binValue={1,1,0,0};g.minterms={12};
    h.numberOfOnes=3;h.binValue={1,1,1,0};h.minterms={14};
    vector<Data>v ={a,b,c,d,e,f,g,h};
    vector<Data> ans=quineMcCluskey(v,4);
    cout << "\nPrime Implicants:\n";
    for (auto& term : ans) {
        term.print();
        cout << "------------------------\n";
    }
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
int numberOfOneCount(vector<int> a){
    int count=0;
    for(int i=0;i<=a.size();i++){
        if(a[i]==1) count++;
        
    }
    return count;
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