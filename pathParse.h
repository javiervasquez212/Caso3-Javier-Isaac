
#ifndef _PATHPARSE_
#define _PATHPARSE_ 0

#include <iostream>
#include <bits/stdc++.h>
#include "rapidxml/rapidxml_ext.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include <sstream>
#include <fstream>
#include "Coordinate.h"
#include "Range.h"
#include "PathData.h"

using namespace std;
using namespace rapidxml;

void extractXMLData(xml_document<>* doc);
void extractNodeData(xml_node<>* node);

vector<PathData*> vectorData;

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

      cout << "Code color path: " << "0x"+color << endl;

      if(hexadecimalToDecimal(color)<=0x83FF00   && hexadecimalToDecimal(color)>=0x2700FF ){
        cout<< "Range color: 0x83FF00 - 0x2700FF" << endl;
        break;
      }
      if(hexadecimalToDecimal(color)<=0xFFFF00 && hexadecimalToDecimal(color)>=0xFF0000 ){
        cout<< "Range color: 0xFFFF00 - 0xFF0000" << endl;
        break;
      }
      if(hexadecimalToDecimal(color)<=0xFF0000  && hexadecimalToDecimal(color)>=0x83FF00 ){
        cout<< "Range color: 0xFF0000 - 0x83FF00" << endl;
        break;
      }
      if(hexadecimalToDecimal(color)<=0xFFFF00  && hexadecimalToDecimal(color)>=0x83FF00 ){
        cout<< "Range color: 0xFFFF00 - 0x83FF00" << endl;
        break;
      }
    }
  }
}

void extractCoordinate(string pString){

  int flagX = 0;
  int flagY = 0;

  float absoluteX;
  float absoluteY;

  vector<float> vectorCoordinatesX;
  vector<float> vectorCoordinatesY;

  string numberStr = "";

  for (int i = 0; i < pString.length(); i++)
  {
    if(isdigit(pString[i]) ){
        numberStr += pString[i];
    }
    else if(pString[i] == ','){

      if(flagX !=0){
      
      vectorCoordinatesX.push_back(std::stof(numberStr)+absoluteX);
      numberStr += pString[i];
      numberStr = "";
      }
      else{
        absoluteX = std::stof(numberStr);
        numberStr="";
        flagX++;
      } 
    }
    else if (pString[i] == '.')
    {
      numberStr += pString[i];
    }
    else if (pString[i] == '-')
    {
      numberStr += pString[i];
    }
    else if (pString[i] == ' ')
    {
      if(flagY!=0){
        if(numberStr != "" && std::stof(numberStr)!=absoluteY){
          vectorCoordinatesY.push_back(std::stof(numberStr)+absoluteY);
          }
          numberStr = "";
      }
        else if(flagY == 0 && numberStr!="") {
          absoluteY = std::stof(numberStr);
          flagY++;
        }
    }
  }

  if(vectorCoordinatesX.size()!=0 && vectorCoordinatesY.size()!=0){    

    cout << "Maximo X,Y: " << *max_element(vectorCoordinatesX.begin(), vectorCoordinatesX.end()) << " , " <<
    *max_element(vectorCoordinatesY.begin(), vectorCoordinatesY.end()) << endl;
    cout << "Minimo X,Y: " << *min_element(vectorCoordinatesX.begin(), vectorCoordinatesX.end()) << " , " <<
    *min_element(vectorCoordinatesY.begin(), vectorCoordinatesY.end()) << endl;

  }
}

void extractNodeData(xml_node<>* node){
  Coordinate X;
  Coordinate Y;
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
        }
        cout << "----------" << endl;
      }
      extractNodeData(node);
    }
  }
}

#endif