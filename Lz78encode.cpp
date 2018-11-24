//Contributed by Xueyan Li
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

class TreeNode{
    public:
    int index;
    char entry;
    TreeNode *parent;
    TreeNode *firstChild;
    TreeNode *sibling;
    
    TreeNode()
    {
        entry = NULL;
        index = NULL;
        parent = NULL;
        firstChild = NULL;
        sibling = NULL;
    };
    TreeNode(char e, int inx, TreeNode *par)
    {
        entry = e;
        index = inx;
        par = parent;
        firstChild = NULL;
        sibling = NULL;
    };
    TreeNode* findChild(char c)
    {
        if (firstChild == NULL) return NULL;
        TreeNode *kid = firstChild;
        while (kid != NULL)
        {
            if (kid -> entry == c) return kid;
            kid = kid -> sibling;
        }
        return NULL;
    };
    void addChild(char c, int mycount)
    {
        if (firstChild == NULL)
        {
            firstChild = new TreeNode(c, mycount, this);
        }
        else
        {
            TreeNode *kid = firstChild;
            while(kid -> sibling!= NULL) kid = kid -> sibling;
            kid -> sibling = new TreeNode(c, mycount, this);
        }
    };
    
};

void encode(string address)
{
    int mycount = 0;
    ifstream infile;
    ofstream outfile;
    infile.open(address.data());
    outfile.open("LZ78encoding.txt");
    
    char c;
    infile >> noskipws;
    TreeNode *root = new TreeNode(NULL, 0, NULL);
    TreeNode *cur = root;
    TreeNode *loc = cur;
    while (!infile.eof())
    {
        infile >> c;
        loc = cur -> findChild(c);
        
        if (loc == NULL) //Œ¥’“µΩ
        {
            mycount ++;
            cur -> addChild(c, mycount);
            outfile << cur -> index << c << " ";
            cur = root;
        }
        else {cur = loc;}
    }
    infile.close();
    outfile.close();
}

int main()
{
    encode("OriginCode.txt");
    return 0;
}

