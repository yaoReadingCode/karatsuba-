#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <algorithm> 



using namespace std;

//Method declaration to compare the value of two large digits
signed int comparestr(string tempdividend, string tempdivisor);



//Method to reverse a string
string stringrev(string s){
    int n = s.length();
    for (int i = 0; i < n / 2; i++){
        swap(s[i], s[n - i - 1]);
    }
    return s;
}

//Method to reverse array
void arrayrev(int arr[], int start, int end)
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

//Method to change from integer to string
string integtostring(int & i)
{
    string s;
    stringstream ss(s);
    ss<<i;
    return ss.str();
}

//Implementation of school addition
string schoolsummation(string a, string b, string base){
    
    string firstterm = a;
    string secondterm = b;
    string basebit = base;

     //Defining arrays to store digits of the first, second term and the result for each position
    int first [1000] = {0};
    int second [1000] = {0};
    int sumrob [1001] = {0};

    //calling reverse function to reverse a string 
    reverse(firstterm.begin(),firstterm.end());
    reverse(secondterm.begin(),secondterm.end());

    int basebitint = stoi(basebit);
    int carry = 0;
    int c = 0;

    //Setting an array to store the result
    if (firstterm.size() > secondterm.size()){
        c = firstterm.size();

    }else{
        c = secondterm.size();
    }
    
    //Storing each digits in an array
    for (int i = 0; i < firstterm.size(); i++){
        first[i] = firstterm[i] - '0';
    }
    
    for (int i = 0; i < secondterm.size(); i++){
        second[i] = secondterm[i] - '0';
    }
    
    //Addition school method 
    for (int i = 0; i < c; i++){
        sumrob[i] = (first[i] + second[i]+ carry) % basebitint;
        carry = (first[i] + second[i] + carry) / basebitint;
    }
    
    sumrob[c] = carry;
    
    int n = sizeof(sumrob)/sizeof(sumrob[0]);
    
    arrayrev(sumrob, 0, n-1);
    
    //converting integer array to string
    string answer;
    for (int i = 0; i < n; i++)
    {
        int &temporal = sumrob[i];
        answer += integtostring(temporal);
    }
    
    //Erasing 0s in the front 
    answer.erase(0, min(answer.find_first_not_of('0'), answer.size()-1));
    
    return answer;
    
    
}




//Implementation method to substract two numbers
string schoolsubstraction(string a, string b, string base){
    
    string fterm = a;
    string sterm = b;
    string bs = base;


    int basesubs = stoi(bs);

    // Aligning digits through padding 0s 
    if (fterm.length() < sterm.length()){
        int cant = sterm.length()-fterm.length();
        for (int i = 0; i < cant; i++){
            fterm.insert(fterm.begin(), '0');
        }
    } else if (fterm.length() > sterm.length()){
        int cant = fterm.length()-sterm.length();
        for (int i = 0; i < cant; i++){
            sterm.insert(sterm.begin(), '0');
        }
    }

    //Special case for division
    if(comparestr(fterm,sterm)==-1){

        return "-1";
    }
    
    // Substracting each number in each position
    string answsubs;
    int carri = 0;
    for (int i = fterm.length()-1; i >= 0; i--){
        int numbertwosubs = sterm[i] - '0';
        int numberonesubs = fterm[i] - '0';
        int numfin = numberonesubs - numbertwosubs + carri;
        if (numfin < 0){
            carri = -1;
            numfin += basesubs;
        } else {
            carri = 0;
        }
        answsubs += to_string(numfin);
    }
    
    // reverse string
    answsubs = stringrev(answsubs);
    return answsubs;
}

//Implementation of karatsuba multiplication
string karatmultipl(string a, string b, string base){
    
    string firstproduct = a;
    string secondproduct = b;
    string basebitproduct = base;

    // Aligning digits through padding 0s 
    if (firstproduct.length() < secondproduct.length()){
        int delta = secondproduct.length()- firstproduct.length();
        for (int i = 0; i < delta; i ++){
            firstproduct.insert(0, "0");
        }
    } else if (firstproduct.length() > secondproduct.length()){
        int delta = firstproduct.length() - secondproduct.length();
        for (int i = 0; i < delta; i++){
            secondproduct.insert(0, "0");
        }
    }
    
    // base case
    if (firstproduct.length() == 1 || secondproduct.length() == 1){
        int firstprodint = stoi(firstproduct);
        int secondproductint = stoi(secondproduct);
        int baseinteger = stoi(basebitproduct);
        
        int resproduct = firstprodint * secondproductint;
        int carrymult = 0;
        if (resproduct >= baseinteger){
            while (resproduct >= baseinteger){
                resproduct -= baseinteger;
                carrymult++;
            }
        }
        string summation = to_string(carrymult) + to_string(resproduct);
        return summation;
    }
    
    // set m and find r
    int m = firstproduct.length();
    int r = firstproduct.length() / 2;
    
    // Separing strings
    string aone = firstproduct.substr(0, m-r);
    string azero = firstproduct.substr(m-r, firstproduct.size());
    
    string bone = secondproduct.substr(0, m-r);
    string bzero = secondproduct.substr(m-r, firstproduct.size());
    
    string psec = karatmultipl(aone, bone, basebitproduct);
    string pzero = karatmultipl(azero, bzero, basebitproduct);
    string pone = karatmultipl(schoolsummation(aone, azero, base), schoolsummation(bone, bzero, basebitproduct), basebitproduct);
    pone = schoolsubstraction(pone, schoolsummation(psec, pzero, basebitproduct), basebitproduct);
        // pad 0's
        for (int i = 0; i < 2*r; i++){
            psec += '0';
        }
        for (int i = 0; i < r; i++){
        pone += '0';
        }
        
        return schoolsummation(psec, schoolsummation(pone, pzero, basebitproduct), basebitproduct);
    
}


string division(string a, string b, string base){ 
    
    
    string ans; 

    int idx = 0; 

    string s;

    string remainder;


    if (comparestr(a,b)==0) {  
        string sone = "1";
        return sone;

    } else if (comparestr(a,b)<0) { 
        string zero = "0";
        return zero;
    } 

    string tempdividend = a.substr(0,++idx); 
   

    while (comparestr(tempdividend,b)<0) 
      
        
        tempdividend = a.substr(0,++idx); 
        //cout << tempdividend;
      
   
    while (a.length() >= idx) 
    { 
        
        int quotient = 0; 

        if(comparestr(tempdividend, b)>=0){  

                

            do{ 
                  
                remainder = schoolsubstraction(tempdividend, b, base); 

                tempdividend = remainder; 

                quotient++; 

                } while (comparestr(tempdividend,b) >= 0);    

                string tempquotient = integtostring(quotient); 

                ans.append(tempquotient); 

                
                    if(idx == a.length()){ 
                        
                        tempdividend=remainder; 
                    
                    }else{

                    char s = a.at(idx); 

                    string h; 

                    h.push_back(s); 
                 
                    tempdividend = tempdividend.append(h);  

                    //remainder = tempdividend  

                    }

        } else{
          
            quotient = 0; 

            //cout << quotient;
          
            string tempquotient = integtostring(quotient);  

            ans.append(tempquotient); 

            //tempdividend = a.substr(0,++idx);

            
            if(idx == a.length()){ 
                tempdividend=remainder;
                
            }else{

            char s = a.at(idx); 

            string t; 

            t.push_back(s); 
         
            tempdividend = tempdividend.append(t);
            //char s = a.at(++idx); 

            //h.push_back(s);
            }
        }
        idx++; 
    } 

      
    // If divisor is greater than number 
    if (ans.length() == 0) 
        return "0"; 
      
    // else return ans 
    return ans; 
 }

signed int comparestr(string tempdividend, string tempdivisor){

    string strone = tempdividend;

    string strtwo = tempdivisor;
    
    // pad zeros
    if (strone.length() < strtwo.length()){
        int repeat = strtwo.length()-strone.length();
        for (int i = 0; i < repeat; i++){
            strone.insert(strone.begin(), '0');
        }
    } else if (strone.length() > strtwo.length()){
        int repeat = strone.length()-strtwo.length();
        for (int i = 0; i < repeat; i++){
            strtwo.insert(strtwo.begin(), '0');
        }
    }



    int counta;

    int i;

    for (i = 0; i < strone.length(); ++i){

        if ((strone[i] - '0') == (strtwo[i] - '0')){ 
            counta++;
        } else if((strone[i] - '0') > (strtwo[i] - '0')){
            return 1;
        } else if ((strone[i] - '0') < (strtwo[i] - '0')){
            return -1;
        }
    }

    if (counta == strone.length()){
        return 0;
    }

    return 4;
}





int main(){
    
    std::string a;
    std::string b;
    std::string base;
    
    cin >> a >> b >> base;
    
    std::string resultAdd = schoolsummation(a,b,base);
    
    std::string resultmulti = karatmultipl(a,b,base);

    std::string resultdiv = division(a,b,base);
    
    cout << resultAdd << " " << resultmulti<< " " << resultdiv << endl;
    
    
}





















