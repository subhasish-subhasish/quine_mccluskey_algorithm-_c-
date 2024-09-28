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
int main(){
    Data a,b,c;
    a.numberOfOnes=2;a.binValue={1,0,0,1};a.minterms={9};
    b.numberOfOnes=1;b.binValue={0,0,0,1};b.minterms={1};
    if(canCombine(a,b,c)){
        c.print();
    }
    else{
        cout<<"Not possible";
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