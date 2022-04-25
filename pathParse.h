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

int hexadecimalToDecimal(string hexVal)
{
    int len = hexVal.size();
    int base = 1;
    int dec_val = 0;
    
    for (int i = len - 1; i >= 0; i--) {
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;
            base = base * 16;
        }
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            dec_val += (int(hexVal[i]) - 55) * base;
            base = base * 16;
        }
    }
    return dec_val;
}

void extractColor(string pString){

  string color = "";
  int counter = 0;

  for (int i = 0; i < pString.length(); i++){

    if(isdigit(pString[i])){
        color += pString[i];
    }
    if(pString[i] >= 'a' && pString[i] <= 'f'){
      if(counter != 0){
        color += toupper(pString[i]);
      }
      counter++;
    }
    if(pString[i] ==';'){
      cout<< "Color en decimal:" << hexadecimalToDecimal(color) << endl;
      cout<< "Color en HEX:" << color << endl;
      break;
    }
  }
}


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
  cout << "Maximo X,Y: " << *max_element(vectorCoordinatesX.begin(), vectorCoordinatesX.end()) << " , " <<
  *max_element(vectorCoordinatesY.begin(), vectorCoordinatesY.end()) << endl;

  cout << "Minimo X,Y: " << *min_element(vectorCoordinatesX.begin(), vectorCoordinatesX.end()) << " , " <<
  *min_element(vectorCoordinatesY.begin(), vectorCoordinatesY.end()) << endl;
}

void extractNodeData(xml_node<>* node){
  for (node = node->first_node(); node != NULL; node = node->next_sibling()){
    if (node->type() == node_element){
      if((string)node->name() == "path"){
        for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
          if((string)attrib->name() == "d"){
            extractCoordinate((string)attrib->value());
          }
          if((string)attrib->name() == "style"){
            extractColor((string)attrib->value());
          }
        }
        cout << "----------" << endl;
      }
      extractNodeData(node);
    }
  }
}