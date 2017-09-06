//
// Created by alfred on 9/3/17.
//

#ifndef KDTREE_CSVHANDLER_H
#define KDTREE_CSVHANDLER_H

#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class CSVHandler{
private:
    vector<vector<string> >whereToSaveData;

    vector<string> dataParser(const string &stringToParse) {
        vector<string>ans;
        string fillString;
        unsigned long itr = 0;
        for(auto character:stringToParse){
            if(character != ',')
							fillString+=character;
            else {
                ans.push_back(fillString);
                fillString = "";
            }
						if(itr==stringToParse.length()-1){
							ans.push_back(fillString);
						}
            itr++;
        }
        return ans;
    }
    string getDataTypeOfOneString(string &StringtoAnalize){
        int Numpoints = 0;
				//if(StringtoAnalize == "N/A" || StringtoAnalize=="NULL")return "numeric";
        for (unsigned int i = 0; i < StringtoAnalize.length(); ++i) {
            if(i==0 && StringtoAnalize.length()>1 && StringtoAnalize[i]=='-')continue;
            else if(StringtoAnalize[i]>47 && StringtoAnalize[i]<58) continue;
            else if(StringtoAnalize[i]=='.' && Numpoints==0){++Numpoints;continue;}
            else return "text";
        }
        return "numeric";
    }

public:
    vector<string> getColumnsName(){
        return whereToSaveData.at(0);
    }
    void getUtilData(vector<vector<string> > &SaveHere){
        for (unsigned int i = 1; i < whereToSaveData.size(); ++i) {
            SaveHere.push_back(whereToSaveData[i]);
        }
    }
    void cleanData() {
        cout << "Limpiar data" << endl;
    }

    void printAllData(){
        for (auto &i : whereToSaveData) {
            for (const auto &j : i) {
                cout << j << " , ";
            }
            cout << endl;
        }
    }

    vector<string> getDataType(){
        vector<string> dataType(whereToSaveData[0].size(),"numeric");
        for (unsigned int i = 1; i < whereToSaveData.size() - 1; ++i) {
            for (unsigned int j = 0; j < whereToSaveData[i].size(); ++j) {
                if(getDataTypeOfOneString(whereToSaveData[i][j]) == "text") dataType[j] = "text";
            }
        }
        return dataType;
    }

    void readCSV(const string &pathToFile){
        if(pathToFile.empty())return;
        ifstream csvFile(pathToFile);
        string auxString;
        while(getline(csvFile,auxString)){
            whereToSaveData.push_back(dataParser(auxString));
        }
        csvFile.close();
    }
};

#endif //KDTREE_CSVHANDLER_H
