#include<iostream>
#include<fstream>

using namespace std;

struct infografo{ 
    string cantArcos, cantNodos, cantConduc;
    string linea;
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
//                       cout << arco << '\n';   
                }
            
            
            }
        
                //std::cout << info.linea[i] << "\n";
        cout << info.cantNodos << "\n";
        cout << info.cantArcos << "\n";
        cout << info.cantConduc << "\n";

        } else {
            cout << "Error al abrir el archivo\n";
		    exit(1);
        }

    }
    ar.close();
    return ;

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