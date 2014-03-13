//Book parser

#include <iostream>
#include <utility>
#include <cstdlib>
#include <vector>
#include <climits>
#include <fstream>
#include <locale>
#include <boost/algorithm/string.hpp> 

using namespace std;


void GetFile();
vector<pair<string,int> > SetUp(string file);
void PrintMenu(vector<pair< string, int> >& words);
vector<string> GetWords(string file);
bool CheckWord(string& word);
vector<pair<string,int> > StoreFreq(vector<string>& words);
void Print(vector<pair<string,int> >A);

void Quicksort(vector<pair< string, int> >&A, int left, int right);
int Partition(vector<pair< string, int> >&A, int left, int right);
void Swap(vector<pair< string, int> >& A, int i, int j);
int BinarySearchString(vector<pair< string, int> >& A, string key, int min, int max);
int BinarySearchInt(vector<pair< string, int> >& A, int key, int min, int max);

bool Menu(vector<pair< string, int> >& words, int num);
void PrintTotalWords(vector<pair< string, int> >& words);
void PrintTotalUnique(vector<pair< string, int> >& words);
void PrintTopTen(vector<pair< string, int> > words);
void SearchWord(vector<pair< string, int> >& words);
void SearchFreq(vector<pair< string, int> > words);

int main(){
  
  GetFile();
  
  return 0;
}

//************************************************************************************************
void GetFile(){
   string file;
   
   cout << "Please enter the name of the text file: "; 
   cin  >> file;
   cin.clear();
   vector<pair<string,int> > words= SetUp(file);
   //Print(words);
   PrintMenu(words);
}

//************************************************************************************************
vector<pair< string, int> > SetUp(string file){
  vector<string> allwords= GetWords(file);
  vector<pair<string,int> >p= StoreFreq(allwords);
  
  return p;
}

//************************************************************************************************
void PrintMenu(vector<pair< string, int> >& words){
   int num= 0;
   
   do{
   cout <<"_____________________________________"<< endl;
   cout <<"\tMENU" << endl <<endl;
   cout <<"1. Print # of total words in file"<<endl;
   cout <<"2. Print # of unique words" << endl;
   cout <<"3. Print top 10 most frequent words"<<endl;
   cout <<"4. Search for word"<<endl;
   cout <<"5. Find all words of X frequency"<< endl;
   cout <<"6. Generate report 1-3" << endl;
   cout <<"7. Quit" << endl;
   cout <<"_____________________________________"<< endl;
   cout <<"Please enter #: ";
   cin  >> num;
   }while(!(Menu(words, num)));
}

//************************************************************************************************
bool Menu(vector<pair< string, int> >& words, int num){
  bool done= false;
  switch (num){
    case 1: PrintTotalWords(words); break;
    case 2: PrintTotalUnique(words); break;
    case 3: PrintTopTen(words); break;
    case 4: SearchWord(words); break;
    case 5: SearchFreq(words); break;
    case 6: {
	      PrintTotalWords(words);
	      PrintTotalUnique(words);
	      PrintTopTen(words);
	      break;
	    }
    case 7: done= true; break; 
    default: PrintMenu(words); break;
  };
  
  return done;
}

//************************************************************************************************
vector<string> GetWords(string file){
  ifstream fin;
  string word;
  vector<string> words;
  
  fin.open(file.c_str());
  while(fin){
   fin >> word;
   boost::algorithm::to_lower(word);
   if(CheckWord(word)){
      words.push_back(word);
   }
  }
  fin.close();
  return words;
}

//************************************************************************************************
bool CheckWord(string& word){
  locale loc;
  bool isword= true;
  bool cutb= false;
  int count= 0;
  for (int i= 0; i < word.size(); i++){
    if(!isalpha(word[i])){ 
      if(i == (word.size()-1))
	cutb= true;
      else
	isword= false;
    }
  }
  if (cutb)
    word= word.substr(0, word.size()-1);
  
  return isword;
}

//************************************************************************************************
vector<pair<string,int> > StoreFreq(vector<string>& words){
  sort(words.begin(), words.end());
  
  vector<pair<string, int> > temp;
  
  for (int i=0; i < words.size(); i++){
     if(temp.size() == 0 || temp.back().first != words[i])
       temp.push_back(make_pair(words[i],1));
     else if (temp.back().first == words[i]){
       temp.back().second+= 1;
     }
       
  }
  //Print(temp);
  return temp;
}

//************************************************************************************************
void PrintTotalWords(vector<pair< string, int> >& words){
  int total= 0;
  for (int i = 0; i < words.size(); i++){
    total+= words[i].second; 
  }
  
  cout << "Total amount of words: " << total <<endl;
}

//************************************************************************************************
void PrintTotalUnique(vector<pair< string, int> >& words){
  cout << "Total amount of unique words: " << words.size() <<endl;
}

//************************************************************************************************
void PrintTopTen(vector<pair< string, int> > words){
  Quicksort(words,0, words.size());
  cout << "Top Ten" << endl;
  for (int i= 1; i <= 10; i ++){ 
    cout << i <<". " << words[words.size()-i].first << "\t:\t" << words[words.size()-i].second << endl;
  }
}

//************************************************************************************************
void SearchWord(vector<pair< string, int> >& words){
  string key= " ";
  cout << "Enter the word you want to find (characters only): ";
  cin >> key;
  boost::algorithm::to_lower(key);
  int i= BinarySearchString(words, key, 0, words.size());
  
  if (i != -1)
    i= words[i].second;
  else
    i= 0;
  
  cout << "The word " << key << " appears " << i << " times." << endl;
  
}

//************************************************************************************************
void SearchFreq(vector<pair< string, int> > words){
  Quicksort(words,0, words.size());
  int key= -1;
  
  cout << "Enter the frequency you want to find (positive integer): ";
  cin >> key;
  
  int i= BinarySearchInt(words, key, 0, words.size());
  if (i != -1){
    int j= i;
    cout << "List of words with frequency of " << key << endl;
    while(words[j].second == words[i].second){
      cout << words[j].first << "\t\t: " << words[j].second << endl;
      j++;
    }
  }else
    cout << "No word has a frequency of " << key << endl;
  
}


//************************************************************************************************
void Print(vector<pair<string,int> > A){
  cout << endl << " LIST A: " << endl << "*********************" << endl;
  for (int i= 0; i < A.size(); i++){
      cout << A[i].first << " , " << A[i].second <<  endl;
  } 
}

//************************************************************************************************
void Quicksort(vector<pair< string, int> >& A, int left, int right){
  int p; 
  if (left < right){
     p = Partition(A, left, right);
     Quicksort(A, left, p);
     Quicksort(A, (p+1), right);
  }
 
}


//************************************************************************************************
int Partition(vector<pair< string, int> >& A, int left, int right){
  int pivot= A[left].second;
  int split= left;
  
  for (int i= left+1; i < right; i++){
     if (A[i].second < pivot){
        split+= 1;
	Swap(A, split, i);
     }
  }
  Swap(A, left, split);
  return split;
}

//************************************************************************************************
void Swap(vector<pair< string, int> >& A, int i, int j){
  pair< string, int> temp;
  temp= A[i];
  A[i]= A[j];
  A[j]= temp;
}

//************************************************************************************************
int BinarySearchString(vector<pair< string, int> >& A, string key, int min, int max){
  if(max<min)
    return -1;
  else{
    int mid= (min+max)/2;
    if (A[mid].first ==key)
      return mid;
    else if (A[mid].first.compare(key) > 0)
      return BinarySearchString(A, key, min, mid-1);
    else 
      return BinarySearchString(A, key, mid+1, max);
  }
}

//************************************************************************************************
int BinarySearchInt(vector<pair< string, int> >& A, int key, int min, int max){
  if(max<min)
    return -1;
  else{
    int mid= (min+max)/2;
    if (A[mid].second ==key){
      bool done= false;
      while(!done){
	if(A[mid].second ==key)
	  mid--;
	else
	  done= true;
      }
      return mid+1;
    }
    else if (A[mid].second > key){
      return BinarySearchInt(A, key, min, mid-1);
    }else 
      return BinarySearchInt(A, key, mid+1, max);
  }
}