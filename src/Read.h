/**
 * @file Read.h
 * Funções para ler ficheiros
 */

#ifndef _READ_H_
#define _READ_H_

#include <list>
#include <vector>

#include "Structs.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

class Read
{
  public:
    vector<airlines> read_airlines();
    vector<airports> read_airports();
    vector<flights> read_flights();
};