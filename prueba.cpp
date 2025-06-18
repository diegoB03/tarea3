#include<iostream>
using namespace std;

int main(){
    int i;
    string nodo;
    string arco;
    char c,x;
    string wea ="helo pesbex ";
    for (i=0;i<wea.length() and c!=' ';i++){
        c = wea[i];
        if (c !=' '){
            nodo = nodo + c;
        }
    }
    
    for (i;x != ' ';i++) {
        x= wea[i];
//        cout << "hola mundo" << '\n';
        if (x != ' '){
            arco= arco + x; 
//            cout << arco << '\n';   
        }
        
        
    }

        
        //std::cout << wea[i] << "\n";
    cout << nodo << "\n";
    cout << arco << "\n";
    
    
    return 0;

}