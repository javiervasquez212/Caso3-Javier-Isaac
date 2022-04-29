
#ifndef _PATHPARSE_
#define _PATHPARSE_ 0


#include <iostream>
#include <bits/stdc++.h>
#include "rapidxml/rapidxml_ext.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include <sstream>
#include <fstream>

#include "Selection.h"

using namespace std;
using namespace rapidxml;

void extractXMLData(xml_document<>* doc);
void extractNodeData(xml_node<>* node);

vector<SVGData*> vectorData;

int hexadecimalToDecimal(string pHexVal)
{
    int len = pHexVal.size();
    int base = 1;
    int dec_val = 0;
    
    for (int i = len - 1; i >= 0; i--) {
        if (pHexVal[i] >= '0' && pHexVal[i] <= '9') {
            dec_val += (int(pHexVal[i]) - 48) * base;
            base = base * 16;
        }
        else if (pHexVal[i] >= 'A' && pHexVal[i] <= 'F') {
            dec_val += (int(pHexVal[i]) - 55) * base;
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

      cout << hexadecimalToDecimal(color) << endl;

      if(hexadecimalToDecimal(color)<2556159   && hexadecimalToDecimal(color)>65373 ){
        cout<< "2556159 - 65373" << endl;
        break;
      }
      if(hexadecimalToDecimal(color)<16776960 && hexadecimalToDecimal(color)>16711680 ){
        cout<< "16776960 - 16711680" << endl;
        break;
      }
      if(hexadecimalToDecimal(color)<16711680  && hexadecimalToDecimal(color)>2556159 ){
        cout<< "16711680 - 2556159" << endl;
        break;
      }
      if(hexadecimalToDecimal(color)<16711680  && hexadecimalToDecimal(color)>65373 ){
        cout<< "16711680 - 65373" << endl;
        break;
      }
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
  coordinate X;
  coordinate Y;
  Range R;
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
          vectorData.push_back(SVGData(X,Y,R));
        }
        cout << "----------" << endl;
      }
      extractNodeData(node);
    }
  }
}


#endif