//
// Created by alfred on 9/3/17.
//

#ifndef KDTREE_KDTREE_H
#define KDTREE_KDTREE_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <deque>
#include <algorithm>
#include "CSVHandler.h"
#include "KDTreeNode.h"

using namespace std;

class KDTree{
public:
    shared_ptr<KDTreeNode> root;
    int Dim;
    vector<string>dataTypes;
    vector<string>dataColumns;

    struct compare{
        KDTree &Myinfo;
        int dimension;
        compare(KDTree &info, int dimension1): Myinfo(info), dimension(dimension1){}
        bool operator()(vector<string> &vec1, vector<string> &vec2){
            auto udimension = (unsigned long)dimension;
            if(Myinfo.dataTypes[udimension] == "numeric"){
                if(stod(vec1.at(udimension)) >= stod(vec2.at(udimension))) return false;
                else if(stod(vec1.at(udimension)) < stod(vec2.at(udimension))) return true;
            } else {
                if(vec1.at(udimension) >= vec2.at(udimension)) return false;
                else if(vec1.at(udimension) < vec2.at(udimension)) return true;
            }
            return false;
        }
    };

    void printVector(vector<string> &vec){
        for (auto &i:vec)cout << i << ' ';
        cout <<  endl;
    }

    void BuildKDTreeNaive(vector<vector<string> >&dataSet, int depth, int ini, int fin, shared_ptr<KDTreeNode> &actual){
        int actualDimension = depth % Dim;
        if(ini > fin) return;
        //sortData(dataSet,ini,fin,actualDimension);
        sort(dataSet.begin()+ini,dataSet.begin()+fin+1,compare(*this,actualDimension));
        int posMedian = (ini + fin) / 2;

        actual = make_shared<KDTreeNode>(dataSet[posMedian]);
        BuildKDTreeNaive(dataSet,depth+1,ini,posMedian-1,actual->sons[0]);
        BuildKDTreeNaive(dataSet,depth+1,posMedian+1,fin,actual->sons[1]);
    }

    void UtilBuildKdTree(vector<vector<string> > &dataSet){
        BuildKDTreeNaive(dataSet,0,0,(int)dataSet.size()-1,root);
    }

    void loadDataFromCSV(string &pathToCSV){
        unique_ptr<CSVHandler> csvHandler = make_unique<CSVHandler>();
        csvHandler->readCSV(pathToCSV);
        vector<vector<string> > dataSet;
        csvHandler->getUtilData(dataSet);
        dataTypes = csvHandler->getDataType();
        dataColumns = csvHandler->getColumnsName();
        Dim = (int)dataTypes.size();
        UtilBuildKdTree(dataSet);
    }
    explicit KDTree(string pathName){
        Dim = 0;
        loadDataFromCSV(pathName);
    }
    void BFS(){
        deque<shared_ptr<KDTreeNode> > Q;
        Q.push_back(root);
        cout << "Start BFS" << endl;
        if(!root)cout << "nuloroot" << endl;
        while(!Q.empty()){
            if(Q[0]->sons[0])Q.push_back(Q[0]->sons[0]);
            if(Q[0]->sons[1])Q.push_back(Q[0]->sons[1]);
            Q[0]->printData();
            Q.pop_front();
        }
    }
    //TODO: Write a function for finding elements and then compare
    //TODO: with a linear container
    bool find(vector<string> dataToFind){
        return false;
    }
};

#endif //KDTREE_KDTREE_H
