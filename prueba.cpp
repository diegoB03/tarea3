#include<iostream>
#include "implementacion/Graphl_2.cpp"
#include<fstream>
#include<sstream>

using namespace std;
using std::string;
using std::stoi;



struct infografo{ 
    string cantArcos, cantNodos, cantConduc;
    string linea;
    int arcosNum, nodosNum, conducNum;
    int arcos[90];
    int nodos[90];
    

};

void datosGrafo(){
    fstream ar;
    infografo info;

    

    ar.open("data1.txt", ios::in);
    if(ar.is_open() ){
        if(getline(ar, info.linea)){
            
            char c,x,v;
            int i;
            
            for (i=0;i<info.linea.length() and c!=' ';i++){
                c = info.linea[i];
                if (c !=' '){
                    info.cantNodos = info.cantNodos + c;
                }
            }

            for (i;x != ' ';i++) {
                x= info.linea[i];
//                cout << "hola mundo" << '\n';
                if (x != ' '){
                    info.cantArcos= info.cantArcos + x; 
//                    cout << arco << '\n';   
                }


            }
        
            for (i ;v != ' ' and  i < info.linea.length();i++) {
                v= info.linea[i];
                if (v != ' '){
                    info.cantConduc= info.cantConduc + v; 
                    cout << info.cantConduc << '\n';   
                }
            
            
            }
            
            info.cantConduc += ' ';
        
            //std::cout << info.linea[i] << "\n";
        
        info.nodosNum  = stoi(info.cantNodos);
        info.arcosNum  = stoi(info.cantArcos);
        info.conducNum = stoi(info.cantConduc);

        cout << info.arcosNum <<  " prueba carajo" << "\n";
        cout << info.nodosNum << " prueba carajo" << "\n";
        cout << info.conducNum <<  " prueba carajo" << "\n";

        } else {
            cout << "Error al abrir el archivo\n";
		    exit(1);
        }

    }
    ar.close();
    return ;

}

void crearArcos(){
    infografo info;
    fstream ar;
    int i = 0;


    Graphl *grf = new Graphl(info.nodosNum);

    while (i < info.cantArcos and getline(r, info.linea)){
        
    }

//    cout << info.arcosNum  << "\n"; 
//    cout << info.nodosNum  << "\n";
//    cout << info.conducNum << "\n";    

//    while(i < info.arcosNum and getline(ar, info.linea)){
//
//        
//    }

    
}


int main(){
    infografo info;

    datosGrafo();
//    infografo info;
//    int i;
//    char c,x,v;
//    string info.linea ="13 12 13";
//    for (i=0;i<info.linea.length() and c!=' ';i++){
//        c = info.linea[i];
//        if (c !=' '){
//            info.cantNodos = info.cantNodos + c;
//        }
//    }
//    
//    for (i;x != ' ';i++) {
//        x= info.linea[i];
////        cout << "hola mundo" << '\n';
//        if (x != ' '){
//            info.cantArcos= info.cantArcos + x; 
////            cout << arco << '\n';   
//        }
//        
//        
//    }
//
//    for (i ;v != ' ' and  i < info.linea.length();i++) {
//        v= info.linea[i];
//        if (v != ' '){
//            info.cantConduc= info.cantConduc + v; 
////               cout << arco << '\n';   
//        }
//    
//    
//    }
//
//        //std::cout << info.linea[i] << "\n";
//    cout << info.cantNodos << "\n";
//    cout << info.cantArcos << "\n";
//    cout << info.cantConduc << "\n";
    
    
    return 0;

}