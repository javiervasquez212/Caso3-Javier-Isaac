
#ifndef _PATHPARSE_
#define _PATHPARSE_ 0

#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include "rapidxml/rapidxml_ext.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include <sstream>
#include <fstream>
#include "Coordinate.h"
#include "Range.h"
#include "PathData.h"
#include "Parameter.h"

using namespace std;
using namespace rapidxml;

void extractXMLData(xml_document<>* doc);
void extractNodeData(xml_node<>* node);

vector<PathData*> vectorData;
vector<PathData*> vectorSolution;
vector<Parameter*> vectorParameter;

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

void extractColorPath(string pString, PathData &pDataPath){

  Range auxRange;
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

      if(hexadecimalToDecimal(color)<=0x83FF00   && hexadecimalToDecimal(color)>=0x2700FF ){
        auxRange.setStart(0x2700FF);
        auxRange.setEnd(0x83FF00);
        break;
      }
      if(hexadecimalToDecimal(color)<=0xFFFF00 && hexadecimalToDecimal(color)>=0xFF0000 ){
        auxRange.setStart(0xFF0000);
        auxRange.setEnd(0xFFFF00);
        break;
      }
      if(hexadecimalToDecimal(color)<=0xFF0000  && hexadecimalToDecimal(color)>=0x83FF00 ){
        auxRange.setStart(0x83FF00);
        auxRange.setEnd(0xFF0000);
        break;
      }
      if(hexadecimalToDecimal(color)<=0xFFFF00  && hexadecimalToDecimal(color)>=0x83FF00 ){
        auxRange.setStart(0xFFFF00);
        auxRange.setEnd(0x83FF00);
        break;
      }
      else{
        break;
      }
    }
  }

  pDataPath.setColors(auxRange);
  pDataPath.setPathColor(color);
}

void extractCoordinatePath(string pString, PathData &pDataPath){

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

    Coordinate absoluteCoordinate(absoluteX,absoluteY);
    Coordinate minCoordinates(*min_element(vectorCoordinatesX.begin(), vectorCoordinatesX.end()),*min_element(vectorCoordinatesY.begin(), vectorCoordinatesY.end()));
    Coordinate maxCoordinate(*max_element(vectorCoordinatesX.begin(), vectorCoordinatesX.end()),*max_element(vectorCoordinatesY.begin(), vectorCoordinatesY.end()));
    
    pDataPath.setAbsoluteCoordinate(absoluteCoordinate);
    pDataPath.setMaxCoordinate(maxCoordinate);
    pDataPath.setMinCoordinate(minCoordinates);
    pDataPath.setPathPoints(pString);
  }
}

void extractNodeData(xml_node<>* node){

  for (node = node->first_node(); node != NULL; node = node->next_sibling()){

    PathData* auxPath;
    auxPath = new PathData();

    if (node->type() == node_element){
      if((string)node->name() == "path"){
        for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
          if((string)attrib->name() == "d"){
            extractCoordinatePath((string)attrib->value(), *auxPath);
          }
          if((string)attrib->name() == "style"){
            extractColorPath((string)attrib->value(), *auxPath);
          }
        }
        vectorData.push_back(auxPath);
      }
      extractNodeData(node);
    }
  }
}

vector<Parameter*> createParameter(Coordinate pArrayPoint[], int pArrayColors[], int pArrayPointSize, int pArrayColorSize){

  for (int x = 0; x < pArrayPointSize; x++)
  {
    for (int y = 0; y < pArrayColorSize; y++)
    {
      Parameter* auxParameter;
      auxParameter = new Parameter(pArrayPoint[x], pArrayColors[y]);
      vectorParameter.push_back(auxParameter);
    }
  }
  return vectorParameter;
}
  bool RecursiveSelection(PathData *pPath, vector<Parameter*> pParameterVector){

  if(pParameterVector.size() == 0){
    return false;
    }
  else if(pParameterVector.size() == 1){
    Parameter *element = pParameterVector[0];
    if(pPath->getMinX()<= element->getPoint().getX() && pPath->getMaxX()>= element->getPoint().getX() &&
       pPath->getMinY()<= element->getPoint().getY() && pPath->getMaxY()>= element->getPoint().getY() &&
       pPath->getColors().getStart() <= element->getColor() && pPath->getColors().getEnd() >= element->getColor()){
      return true;
      }
    else{
      return false;
      }
    }
  else{

    int middleIndex = pParameterVector.size()/2;
    Parameter *middleParameter = pParameterVector[middleIndex];

    if(pPath->getMinX()<= middleParameter->getPoint().getX() && pPath->getMaxX()>= middleParameter->getPoint().getX() &&
       pPath->getMinY()<= middleParameter->getPoint().getY() && pPath->getMaxY()>= middleParameter->getPoint().getY() &&
       pPath->getColors().getStart() <= middleParameter->getColor() && pPath->getColors().getEnd() >= middleParameter->getColor()){
         return true;
         }
    else{
      vector<Parameter*> firstHalveParameterVector(pParameterVector.begin(), pParameterVector.begin() + middleIndex);
      vector<Parameter*> SecondHalveParameterVector(pParameterVector.begin() + middleIndex, pParameterVector.end());
      if(RecursiveSelection(pPath,firstHalveParameterVector) || RecursiveSelection(pPath,SecondHalveParameterVector)){
        return true;
      }
      else{
        return false;
      }
    }
  }
}

vector<PathData*> Selection(vector<PathData*> pPathVector, vector<Parameter*> pParameterVector){

  cout << pPathVector.size() << endl;
   for(PathData *path : pPathVector){ 
     if(RecursiveSelection(path, pParameterVector)){
       vectorSolution.push_back(path);
     }
   }
   cout << vectorSolution.size() << endl;
   return vectorSolution;
}

void PrintVectorPathsData(){

  for(PathData *path : vectorData){
    cout << "d: " << path->getPathPoints() << endl;
    cout << "Color: " << path->getPathColor() << endl;
    cout << "Max Coordinates: " << path->getMaxX() << "," << path->getMaxY() << endl;
    cout << "Min Coordinates: " << path->getMinX() << "," << path->getMinY() << endl;
    cout << "Range colors: " << path->getColors().getStart() << "-" << path->getColors().getEnd()<<endl;
    cout << "---------------------"<<endl;
  }
}

/*vector<PathData*> match(Coordinate pArrayPoint[], int pArrayColors[], int pArrayPointSize, int pArrayColorSize){

  createParameter(pArrayPoint,pArrayColors,pArrayPointSize,pArrayColorSize);

  for(PathData *path : vectorData){
    for(Parameter *parameter : vectorParameter){
      if(parameter->getColor() <= path->getColors().getEnd() && parameter->getColor() >= path->getColors().getStart()){
        if(parameter->getPoint().getX() <= path->getMaxX() && parameter->getPoint().getY() <= path->getMaxY() &&
        parameter->getPoint().getY() >= path->getMinX() && parameter->getPoint().getY() >= path->getMinY()){
          vectorSolution.push_back(path);
         }
        }
      }
    }
    std::sort(vectorSolution.begin(),vectorSolution.end());
    vectorSolution.erase(std::unique(vectorSolution.begin(),vectorSolution.end()),vectorSolution.end());

    return vectorSolution;
  }*/

#endif