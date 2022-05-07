#include "pathParse.h"


int main(){
    //Leer XML
    file<> file("image.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    //Recorrer elementos y atributos
    extractNodeData(&myDoc);
    Coordinate a1(100,200);
    Coordinate a2(255,144);
    Coordinate a3(300,70);

    Coordinate a4(150,250);
    Coordinate a5(50,150);
    Coordinate a6(-50,50);

    Coordinate arrayCoordinate[] = {a1,a2,a3,a4,a5,a6};
    int arrayColor[] = {0x7DA367,0x57ABE7,0XFF6633,0x800080,0x996633,0x990099};


    match(arrayCoordinate, arrayColor,6,6);

    


    return 0;

}