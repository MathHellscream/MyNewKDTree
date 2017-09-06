#include <iostream>
#include "KDTree.h"
int main() {
    unique_ptr<KDTree> arbol = make_unique<KDTree>("newTestData.csv");
    for (const auto &dataType : arbol->dataTypes) {
        cout << dataType << endl;
    }
    return 0;
}
