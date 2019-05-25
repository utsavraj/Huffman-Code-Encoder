#include<iostream>
#include<fstream>
#include<iomanip>

#include<string>
#include<map>
#include<vector>

#include<iterator>

#include<algorithm>


using namespace std;








struct treeNode //Basic Tree Structure
{
    string key;
    int feq;
};

//Compare the 2 nodes (a & b) of the tree
bool comp(const treeNode &a, const treeNode &b)
{
    if (a.feq == b.feq) //if frequency is the same
    {
        int min_a = a.key[0];
        int min_b = b.key[0];

        for (int i = 0; i < a.key.length(); i++)
        {
            if (min_a >= a.key[i])
            {
                
                min_a = a.key[i];
            }
        }

        for (int i = 0; i < b.key.length(); i++)
        {
            if (min_b >= b.key[i])
            {
                min_b = b.key[i];
            }
        }

      
      
      return min_a < min_b;
      
    }

    return a.feq < b.feq;
}

int main(int argc, char* argv[])
{
    ifstream file;
    ofstream file2; //Character codes file
    ofstream file3; //Encrypted file 
    file.open(argv[1]);
    
    
    char character;
    
    
    map<char, treeNode> m;
    int numofchar = 0;
    int totalbitsused = 0; //total bits used

    while(file.get(character)) //get character from input and increase the frequency of that character by 1 if found once etc.
    {
        if (m.count(character) > 0)
        {
            m[character].feq++;
        }
        else
        {
            m[character].feq = 1;
            
            m[character].key = "";
        }
        numofchar++;
    }

    file.close();

    map<char, treeNode>::iterator itr;
    vector<treeNode> tree;
    vector<treeNode>:: iterator itr2;

    for (itr = m.begin(); itr != m.end(); itr++)
    {
        treeNode temp;
        string s;
        s.push_back((*itr).first);
        temp.key = s;
        temp.feq = ((*itr).second.feq);
        
        tree.push_back(temp);
    }

    sort(tree.begin(), tree.end(), comp);

    while(tree.size() > 1)
    {
        int freq2 = tree[0].feq + tree[1].feq;
        string key2;
        
        
        string left = tree[0].key, right = tree[1].key;
        int minleft = left[0], minright = right[0];

        for (int i = 1; i < left.length(); i++)
        {
            if (minleft > left[i])
            {
                minleft = left[i];
            }
        }

        for (int i = 1; i < right.length(); i++)
        {
            if (minright > right[i])
            {
                minright = right[i];
            }
        }

        if (minleft > minright)
        {
            string temp = left;
            left = right;
            right = temp;
        }

        key2 = left + right;

        treeNode t;
        t.key = key2;
        t.feq = freq2;
         
         tree.push_back(t);

        for (int i = 0; i < left.length(); i++)
        {
            m[left[i]].key = "0" + m[left[i]].key; //assign 1 to the left part of tree
        }

        for (int i = 0; i < right.length(); i++)
        {
            m[right[i]].key = "1" + m[right[i]].key; //assign 0 to the right part of tree
        }

        tree.erase(tree.begin(), (tree.begin() + 2));

        
        sort(tree.begin(), tree.end(), comp);
    }

    file.open(argv[1]);
    string input = "";

    while (file.get(character))
    {
        input += m[character].key;
        totalbitsused += m[character].key.length();
    }

    file.close();

    
    
    
    file3.open("encodemsg.txt");

    int count2 = 0;
    for (int i = 0; i < input.length(); i++)
    {
        file3 << input[i];
        count2++;
        
        
        if (count2 == 80)
        {
            
            
            count2 = 0;
            file3 << endl; //To fit in the terminal - Otherwise 82%
        }
    }

    file3.close();

    file2.open("code.txt");

    for (itr = m.begin(); itr != m.end(); itr++)
    {
        string character2(1, (*itr).first);
        if (character2 == " ")
        {
            character2 = "Space"; // Based on the given output in word
        }

        string huffman_code = (*itr).second.key;
        file2 << character2 << ": " << huffman_code << endl;
    }

    file2 << "Ave = " << setprecision(3) /* if (2) 52%  */ << (float) totalbitsused /(float) numofchar << " bits per symbol";

    file2.close();
}
