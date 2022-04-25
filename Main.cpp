#include "pathParse.h"


int main(){
    //Leer XML
    file<> file("image.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    //Recorrer elementos y atributos
    extractNodeData(&myDoc);

    return 0;

}