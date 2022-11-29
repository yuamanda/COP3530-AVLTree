#include <iostream>
#include <string>
#include <sstream>
#include "AVLTree.h"
using namespace std;

int main()
{
    AVLTree testTree = AVLTree();

    // read one line of input from cin
    string line;
    getline(cin, line);

    // create an input stream from that line
    istringstream in(line);

    // read in the number from the input stream
    int command;
    in >> command;

    for(int i = 0; i < command; i++)
    {
        // read up to the next quotation mark
        string next;
        getline(cin, next);

        istringstream in(next);

        string instruction;
        instruction = next.substr(0, next.find(' '));

        //cout << "the instruction is " << instruction << endl;

        if(instruction == "insert")
        {
            string name;
            string id;

            int second = next.find('"', 8);

            name = next.substr(8, second - 8);
            id = next.substr(second + 2);

            testTree.insert(name, id);
        }

        else if(instruction == "printInorder")
        {
            testTree.printInOrder();
        }

        else if(instruction == "printPreorder")
        {
            testTree.printPreOrder();
        }

        else if(instruction == "printPostorder")
        {
            testTree.printPostOrder();
        }

        else if(instruction == "printLevelCount")
        {
            testTree.printLevelCount();
        }

        else if(instruction == "search")
        {
            string search;

            if(next.at(7) == '"')
            {
                int second = next.find('"', 8);
                search = next.substr(8, second - 8);
                testTree.searchName(search);
            }
            else
            {
                search = next.substr(7);
                cout << testTree.searchID(search) << endl;
            }
        }

        else if(instruction == "remove")
        {
            string id;
            id = next.substr(7);
            testTree.removeID(id);
        }

        else if(instruction == "removeInorder")
        {
            bool valid = true;
            string n;
            n = next.substr(14);

            for(int i = 0; i < n.length(); i++)
            {
                if(!isdigit(n[i]))
                {
                    valid = false;
                }
            }

            if(valid)
            {
                testTree.removeInOrder(stoi(n));
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
    }

    return 0;
}
