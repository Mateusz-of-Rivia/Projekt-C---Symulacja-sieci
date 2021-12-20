//
// Created by turgo on 12/20/2021.
//
#include "package.hpp"

ElementID_t Package::findID(){
    if(freed_IDs){
        return freed_IDs[0];
    }
    else{
        return assigned_IDs[-1] + 1;
    }
}
