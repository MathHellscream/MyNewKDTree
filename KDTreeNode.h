//
// Created by alfred on 9/3/17.
//

#ifndef KDTREE_KDTREENODE_H
#define KDTREE_KDTREENODE_H

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <memory>
using namespace std;


class KDTreeNode{
public:
    vector<string> nodeData;
    vector<shared_ptr<KDTreeNode> > sons;
    vector<string> getNodeData(){
        return nodeData;
    }
    string getDataAt(long pos){
        return nodeData.at((unsigned long)pos);
    }
    shared_ptr<KDTreeNode> getSonAt(long pos){
        return sons[(unsigned long) pos];
    }
    void setSonAt(unsigned long pos, shared_ptr<KDTreeNode> copyT){
        if(pos < 0)return;
        if(pos >= sons.size())return;
        sons[pos] = std::move(copyT);
    }
    void setDataVector(vector<string> &vector1){
        nodeData = vector1;
    }

    explicit KDTreeNode(vector<string> &vector1){
        nodeData = vector1;
        sons.push_back(nullptr);
        sons.push_back(nullptr);
    }
    void printData(){
        for (const auto &i : nodeData) {
            cout << i << ' ';
        }
        cout << endl;
    }
};

#endif //KDTREE_KDTREENODE_H
