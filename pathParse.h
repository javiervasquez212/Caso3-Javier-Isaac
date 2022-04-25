#include <iostream>
#include <bits/stdc++.h>
#include "rapidxml/rapidxml_ext.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include <sstream>
#include <fstream>

using namespace std;
using namespace rapidxml;

void extractXMLData(xml_document<>* doc);
void extractNodeData(xml_node<>* node);


void extractCoordinate(string pString){

  vector<float> vectorCoordinatesX;
  vector<float> vectorCoordinatesY;

  string number = "";
  for (int i = 0; i < pString.length(); i++)
  {
    if(isdigit(pString[i]) ){
        number += pString[i];
    }
    else if(pString[i] == ','){
      vectorCoordinatesX.push_back(std::stof(number));
      number += pString[i];
      number = "";
    }
    else if (pString[i] == '.')
    {
      number += pString[i];
    }
    else if (pString[i] == '-')
    {
      number += pString[i];
    }
    else if (pString[i] == ' ')
    {
      if(number != ""){
        vectorCoordinatesY.push_back(std::stof(number));
      }
      number = "";
    }
  }
  cout << " Maximo} X,Y: " << *max_element(vectorCoordinatesX.begin(), vectorCoordinatesX.end()) << " , " <<
  *max_element(vectorCoordinatesY.begin(), vectorCoordinatesY.end()) << endl;

  cout << " Minimo X,Y: " << *min_element(vectorCoordinatesX.begin(), vectorCoordinatesX.end()) << " , " <<
  *min_element(vectorCoordinatesY.begin(), vectorCoordinatesY.end()) << endl;
  
  cout<< "------------"<< endl;
}



/*void divideCoordinate(string pString){
  string X;
  string Y;
  string position;
  int counter = 0;
  
  stringstream input_stringstream(pString);                    
  while (getline(input_stringstream, position, ','))
  {
    if(counter == 0){
      X = position;
      counter++;
    }
    else{
      Y = position;
    }
  }
  cout << "X: " << X << " Y: " << Y << endl;
}*/



void extractXMLData(xml_document<>* doc){
  xml_node<>* node = doc->first_node();

  cout << "Etiqueta: " << node->name() << endl;
  for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
    cout << " Atributo: " << attrib->name() << endl;
    cout << "\tValor: " << attrib->value() << endl;
  }

  extractNodeData(node);
}

//Recorre el resto de elementos del documento
void extractNodeData(xml_node<>* node){
  for (node = node->first_node(); node != NULL; node = node->next_sibling()){
    if (node->type() == node_element){
      if((string)node->name() == "path"){
        //cout << "Etiqueta: " << node->name() << endl;
        for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
          if((string)attrib->name() == "d"){
            extractCoordinate((string)attrib->value());
          }
        }
      }
      extractNodeData(node);
    }
  }
}