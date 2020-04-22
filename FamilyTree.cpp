#include "FamilyTree.hpp"
#include <cassert>

using namespace std;
using namespace family;

#define SPACES 10

// find a node by name, return a pointer to its pointer
node** findNode(node** from, string searched){
    //stop conditions: either found or we reached end of tree
    if ((*from == nullptr) || ((*from)->name == searched)){
        return from;
    }
    node** found;
    // recursive call
    found = findNode(&(*from)->father, searched);
    // search from mother's side if father's side gave no result
    if(*found == nullptr){
        found = findNode(&(*from)->mother, searched);
    }
    return found;
}
// findNode used by find function
node* findNode(node* from, int depth, ParentType pt){
    //stop conditions: either found or we reached end of tree
    if (from == nullptr){
        return nullptr;
    }
    else if((from->depth == depth) && (from->type == pt)){
        return from;
    }
    node* found;
    // recursive call
    found = findNode(from->father, depth, pt);
    // search from mother's side if father's side gave no result
    if(found == nullptr){
        found = findNode(from->mother, depth, pt);
    }
    return found;
}

void deleteNodeAndDescendants(node** node){
    if(*node == nullptr){
        return;
    }
    deleteNodeAndDescendants(&(*node)->father);
    deleteNodeAndDescendants(&(*node)->mother);
    delete *node;
    *node = nullptr;
}

Tree::Tree(string rootname){
    if(rootname.length() == 0){
        throw runtime_error("Invalid tree name!");
    }
    root = new node();
    root->name = rootname;
    root->depth = 0;
    root->type = U;
}

Tree::~Tree(){ 
     deleteNodeAndDescendants(&root);
}

Tree& Tree::addFather(string child_name, string father_name){
    if(child_name.length() == 0 || father_name.length() == 0 ){
        throw std::runtime_error("Invalid input!");
    }
    node* child = *findNode(&root, child_name);
    if(child == nullptr){
        throw runtime_error("cannot add father to \""+child_name+"\""+": no such person");
    }
    // if no father create
    if(child->father == nullptr){
        child->father = new node();
        child->father->depth = child->depth + 1;
        child->father->type = F;
    }
    // name new father or rename existing one
    child->father->name = father_name;

    return *this;
}
// same as addFather
Tree& Tree::addMother(string child_name, string mother_name){
    if(child_name.length() == 0 || mother_name.length() == 0 ){
        throw std::runtime_error("Invalid input!");
    }
    node* child = *findNode(&root, child_name);
    if(child == nullptr){
        throw runtime_error("cannot add mother to \""+child_name+"\""+": no such person");
    }
    if(child->mother == nullptr){
        child->mother = new node();
        child->mother->depth = child->depth + 1;
        child->mother->type = M;
    }
    child->mother->name = mother_name;

    return *this;
}
string Tree::relation(string name){
    node* relative = *findNode(&(this->root), name);
    if(relative == nullptr){
        return "unrelated";
    }
    assert ( relative->name == name);
    //cout<<relative->name<<", "<<relative->depth<<endl;
    if(relative->type == U){
        return "me";
    }
    else if(relative->type == M){
        if(relative->depth == 1){
            return "mother";
        }
        else{
            string relation = "";
            for(int i = 2; i < relative->depth; i++){
                relation+="great-";
            }
            relation+="grandmother";
            return relation;
        }
    }
    // relative type is F
    else{
        if(relative->depth == 1){
            return "father";
        }
        else{
            string relation = "";
            for(int i = 2; i < relative->depth; i++){
                relation+="great-";
            }
            relation+="grandfather";
            return relation;
        }
    }
}

string Tree::find(string relat){
    if(relat == "me"){
        return root->name;
    }
    // get depth and type of parent
    // minimum depth is 1, each "great-" prefix adds to the depth
    node* relative;
    int depth = 1;
    ParentType pt = U;
    while((relat.length() > 6) && (relat.substr(0,6).compare("great-") == 0)){
        relat=relat.substr(6);
        depth++;
    }

    
    if(relat == "father"){
        pt = F;
    }
    else if(relat == "grandfather"){
        pt = F;
        depth++;
    }
    else if(relat == "mother"){
        pt = M;
    }
    else if(relat == "grandmother"){
        pt = M;
        depth++;
    }
    if(pt == U){
        throw runtime_error("Cannot handle the \'" + relat + "\' exception");
    }
    relative = findNode(root, depth, pt);
    if(relative == nullptr){
        return "not found";
    }
    return relative->name;
}

void display_helper(node& n, int spaces){
    if(n.father != nullptr){
        display_helper(*(n.father), spaces + SPACES);
    }
    else cout<<endl;

    for(int i = 0; i < spaces; i++){
        cout<<' ';
    }
    cout<<n.name;

    if(n.mother != nullptr){
        display_helper(*(n.mother), spaces + SPACES);
    }
    else cout<<endl;
    
}

void Tree::display(){
    display_helper(*root, 0);
}

Tree& Tree::remove(string name){
    node** n = findNode(&root, name);
    deleteNodeAndDescendants(n);
    return *this;
}