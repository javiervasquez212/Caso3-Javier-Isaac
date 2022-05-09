#ifndef _SELECTION_
#define _SELECTION_ 0

#include <iostream>
#include <vector>
#include <string>
#include "MySubject.h"
#include "PathData.h"
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include "rapidxml/rapidxml_utils.hpp"
#include <sstream>
#include <fstream>
#include "Coordinate.h"
#include "Range.h"
#include "PathData.h"
#include "Parameter.h"

using namespace std;
using namespace rapidxml;

class Selection : public MySubject
{
protected:
  int sizeX;
  int sizeY;
  vector<PathData *> vectorData;
  vector<PathData *> vectorSolution;
  vector<Parameter *> vectorParameter;

public:
  Selection();
  void startSelection();
  vector<PathData *> getVectorSolution();
  int getSizeX();
  int getSizeY();
  int hexadecimalToDecimal(string pHexVal);
  void extractColorPath(string pString, PathData &pDataPath);
  void extractCoordinatePath(string pString, PathData &pDataPath);
  void extractNodeData(xml_node<> *pNode);
  vector<Parameter *> createParameter(Coordinate pArrayPoint[], int pArrayColors[], int pArrayPointSize, int pArrayColorSize);
  bool RecursiveSelection(PathData *pPath, vector<Parameter *> pParameterVector);
  vector<PathData *> selection(vector<PathData *> pPathVector, vector<Parameter *> pParameterVector);
  void PrintVectorPathsData();
};

Selection::Selection()
{
}

vector<PathData *> Selection::getVectorSolution()
{
  return this->vectorSolution;
}

void Selection::startSelection()
{
  // Leer XML
  file<> file("Images/image.svg"); // Lee y carga el archivo en memoria
  xml_document<> myDoc;            // Raíz del árbol DOM
  myDoc.parse<0>(file.data());     // Parsea el XML en un DOM

  // Recorrer elementos y atributos

  this->extractNodeData(&myDoc);

  // Parametros

  Coordinate a1(100, 200);
  Coordinate a2(255, 144);
  Coordinate a3(300, 70);
  Coordinate a4(150, 250);
  Coordinate a5(50, 150);
  Coordinate a6(-50, 50);

  // Array Coordenadas

  Coordinate arrayCoordinate[] = {a1, a2, a3, a4, a5, a6};

  // Array colores

  int arrayColor[] = {0x7DA367, 0x57ABE7, 0XFF6633, 0x800080, 0x996633, 0x990099};

  // Creamos el vector paremetro;
  vector<Parameter *> vectorParameter = this->createParameter(arrayCoordinate, arrayColor, 6, 6);

  // Llamamos la función Selection

  selection(vectorData, vectorParameter);

  this->notify();
}

int Selection::hexadecimalToDecimal(string pHexVal)
{
  int len = pHexVal.size();
  int base = 1;
  int dec_val = 0;

  for (int i = len - 1; i >= 0; i--)
  {
    if (pHexVal[i] >= '0' && pHexVal[i] <= '9')
    {
      dec_val += (int(pHexVal[i]) - 48) * base;
      base = base * 16;
    }
    else if (pHexVal[i] >= 'A' && pHexVal[i] <= 'F')
    {
      dec_val += (int(pHexVal[i]) - 55) * base;
      base = base * 16;
    }
  }
  return dec_val;
}

/*
This function extracts the path color and sets the values to the pathData object based on the
color ranges
*/

void Selection::extractColorPath(string pString, PathData &pDataPath)
{ // Extract Color from each Path

  Range auxRange;
  string color = "";
  int counter = 0;

  for (int i = 0; i < pString.length(); i++)
  {

    if (isdigit(pString[i]))
    {
      color += pString[i];
    }
    if (pString[i] >= 'a' && pString[i] <= 'f')
    {
      if (counter != 0)
      {
        color += toupper(pString[i]);
      }
      counter++;
    }
    if (pString[i] == ';')
    {

      if (hexadecimalToDecimal(color) <= 0x83FF00 && hexadecimalToDecimal(color) >= 0x2700FF)
      {
        auxRange.setStart(0x2700FF);
        auxRange.setEnd(0x83FF00);
        break;
      }
      if (hexadecimalToDecimal(color) <= 0xFFFF00 && hexadecimalToDecimal(color) >= 0xFF0000)
      {
        auxRange.setStart(0xFF0000);
        auxRange.setEnd(0xFFFF00);
        break;
      }
      if (hexadecimalToDecimal(color) <= 0xFF0000 && hexadecimalToDecimal(color) >= 0x83FF00)
      {
        auxRange.setStart(0x83FF00);
        auxRange.setEnd(0xFF0000);
        break;
      }
      if (hexadecimalToDecimal(color) <= 0xFFFF00 && hexadecimalToDecimal(color) >= 0x83FF00)
      {
        auxRange.setStart(0xFFFF00);
        auxRange.setEnd(0x83FF00);
        break;
      }
      else
      {
        break;
      }
    }
  }

  pDataPath.setColors(auxRange);
  pDataPath.setPathColor(color);
}

/*
This function extracts the path absolute coordinate and the relative coordinates and sets the values to the atributes of pathData
*/

void Selection::extractCoordinatePath(string pString, PathData &pDataPath)
{ // Extract Coordinates from each Path

  int flagX = 0;
  int flagY = 0;

  float absoluteX;
  float absoluteY;

  vector<float> vectorCoordinatesX;
  vector<float> vectorCoordinatesY;

  string numberStr = "";

  for (int i = 0; i < pString.length(); i++)
  {
    if (isdigit(pString[i]))
    {
      numberStr += pString[i];
    }
    else if (pString[i] == ',')
    {
      if (flagX != 0)
      {
        vectorCoordinatesX.push_back(std::stof(numberStr) + absoluteX);
        numberStr += pString[i];
        numberStr = "";
      }
      else
      {
        absoluteX = std::stof(numberStr);
        numberStr = "";
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
      if (flagY != 0)
      {
        if (numberStr != "" && std::stof(numberStr) != absoluteY)
        {
          vectorCoordinatesY.push_back(std::stof(numberStr) + absoluteY);
        }
        numberStr = "";
      }
      else if (flagY == 0 && numberStr != "")
      {
        absoluteY = std::stof(numberStr);
        flagY++;
      }
    }
  }
  if (vectorCoordinatesX.size() != 0 && vectorCoordinatesY.size() != 0)
  {

    Coordinate absoluteCoordinate(absoluteX, absoluteY);
    Coordinate minCoordinates(*min_element(vectorCoordinatesX.begin(), vectorCoordinatesX.end()), *min_element(vectorCoordinatesY.begin(), vectorCoordinatesY.end()));
    Coordinate maxCoordinate(*max_element(vectorCoordinatesX.begin(), vectorCoordinatesX.end()), *max_element(vectorCoordinatesY.begin(), vectorCoordinatesY.end()));

    pDataPath.setAbsoluteCoordinate(absoluteCoordinate);
    pDataPath.setMaxCoordinate(maxCoordinate);
    pDataPath.setMinCoordinate(minCoordinates);
    pDataPath.setPathPoints(pString);

    vector<float> aux = vectorCoordinatesX;
    auto elementToRemove = aux.begin();
    aux.erase(elementToRemove);

    pDataPath.setVectorX(aux);
    pDataPath.setVectorY(vectorCoordinatesY);
  }
}

/*
This function extracts the information from the SVG and creates a pathData object from each path to then add it to
the vectorData
*/

void Selection::extractNodeData(xml_node<> *node)
{ // Parse SVG and push elements in vectorData

  for (node = node->first_node(); node != NULL; node = node->next_sibling())
  {
    PathData *auxPath;
    auxPath = new PathData();
    if (node->type() == node_element)
    {
      if ((string)node->name() == "svg")
      {
        for (xml_attribute<> *attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute())
        {
          if ((string)attrib->name() == "width")
          {
            this->sizeX = std::stof(attrib->value());
          }
          if ((string)attrib->name() == "height")
          {
            this->sizeY = std::stof(attrib->value());
          }
        }
      }
      if ((string)node->name() == "path")
      {
        for (xml_attribute<> *attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute())
        {
          if ((string)attrib->name() == "d")
          {
            extractCoordinatePath((string)attrib->value(), *auxPath);
          }
          if ((string)attrib->name() == "style")
          {
            extractColorPath((string)attrib->value(), *auxPath);
          }
        }
        vectorData.push_back(auxPath);
      }
      extractNodeData(node);
    }
  }
}

/*
This function generates the parameter vector based on the information provided by the user
*/
vector<Parameter *> Selection::createParameter(Coordinate pArrayPoint[], int pArrayColors[], int pArrayPointSize, int pArrayColorSize)
{ // Auxiliary recursive function

  for (int x = 0; x < pArrayPointSize; x++)
  {
    for (int y = 0; y < pArrayColorSize; y++)
    {
      Parameter *auxParameter;
      auxParameter = new Parameter(pArrayPoint[x], pArrayColors[y]);
      vectorParameter.push_back(auxParameter);
    }
  }
  return vectorParameter;
}

/*
This function checks if there is a match between the parameters provided by the user and the paths from the svg
It Works by the Divide and Conquer design pattern

BigO = O( n log n )
n = Size of the Parameter Vector (number of points to compare)
*/

bool Selection::RecursiveSelection(PathData *pPath, vector<Parameter *> pParameterVector)
{

  if (pParameterVector.size() == 0)
  {
    return false;
  }
  /*Conquer: we conquer the problem when the subproblem is small enough to be solved in a trivial way
  The base case is when the size of the problem is 1*/
  else if (pParameterVector.size() == 1)
  {
    Parameter *element = pParameterVector[0];
    if (pPath->getMinX() <= element->getPoint().getX() && pPath->getMaxX() >= element->getPoint().getX() &&
        pPath->getMinY() <= element->getPoint().getY() && pPath->getMaxY() >= element->getPoint().getY() &&
        pPath->getColors().getStart() <= element->getColor() && pPath->getColors().getEnd() >= element->getColor())
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    // Divide: we divide the problem in smaller subproblems, in this case, the parameter vector, of the same instance of the problem, using recursion
    int middleIndex = pParameterVector.size() / 2;
    Parameter *middleParameter = pParameterVector[middleIndex];

    if (pPath->getMinX() <= middleParameter->getPoint().getX() && pPath->getMaxX() >= middleParameter->getPoint().getX() &&
        pPath->getMinY() <= middleParameter->getPoint().getY() && pPath->getMaxY() >= middleParameter->getPoint().getY() &&
        pPath->getColors().getStart() <= middleParameter->getColor() && pPath->getColors().getEnd() >= middleParameter->getColor())
    {
      return true;
    }
    else
    {
      vector<Parameter *> firstHalveParameterVector(pParameterVector.begin(), pParameterVector.begin() + middleIndex);
      vector<Parameter *> SecondHalveParameterVector(pParameterVector.begin() + middleIndex, pParameterVector.end());
      if (RecursiveSelection(pPath, firstHalveParameterVector) || RecursiveSelection(pPath, SecondHalveParameterVector))
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }
}

/*
MERGE: we combine the subproblem solutions to obtain the solution
*/

vector<PathData *> Selection::selection(vector<PathData *> pPathVector, vector<Parameter *> pParameterVector)
{ // Main Selection Function
  for (PathData *path : pPathVector)
  {
    if (RecursiveSelection(path, pParameterVector))
    {
      vectorSolution.push_back(path);
    }
  }
  // cout <<"VECTOR GENERAL: " << vectorData.size() << endl;
  // cout <<"VECTOR SOLUCION: " << vectorSolution.size() << endl;
  return vectorSolution;
}

void Selection::PrintVectorPathsData()
{ // Print attributes of elements in vectorData

  for (PathData *path : vectorData)
  {
    cout << "d: " << path->getPathPoints() << endl;
    cout << "Color: " << path->getPathColor() << endl;
    cout << "Max Coordinates: " << path->getMaxX() << "," << path->getMaxY() << endl;
    cout << "Min Coordinates: " << path->getMinX() << "," << path->getMinY() << endl;
    cout << "Range colors: " << path->getColors().getStart() << "-" << path->getColors().getEnd() << endl;
    cout << "---------------------" << endl;
  }
}

int Selection::getSizeX()
{
  return this->sizeX;
}

int Selection::getSizeY()
{
  return this->sizeY;
}

#endif