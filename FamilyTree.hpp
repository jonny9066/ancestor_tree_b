#pragma once
#include <iostream>
using std::string;

namespace family{
    // mother, father, undefined
    enum ParentType{  M, F, U};
    struct node{
        string name;
        ParentType type;
        int depth;
        node* father = nullptr;
        node* mother = nullptr;
    };
    class Tree{
        private:
        node* root;
        //node& findNode(string);
        public:

        Tree(string);
        ~Tree();
        // adds father, if father exists changes his name
        Tree& addFather(string son, string father);
        // same as add father
        Tree& addMother(string son, string mother);
        // gets name and displays relation
        string relation(string);
        // gets relation and displays name
        string find(string);
        void display();
        Tree& remove(string);

    };
}