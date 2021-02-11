// Hacker rank attribute parser C++ problem

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h> 

using namespace std;

/*
    Thought process =>

    <tag1 name = "amogh"> // tags
    <tag2 name = "name">
    </tag2>
    </tag1> 
    <tag3 another="another" final="final">
    </tag3>
    => 
    tag1~name = amogh // queries
    tag2~name = name
    tag3~another = another
    tag3~final = final

    Create array -> parentTags = []
    Create hashmap to store parsed tags attributes and their values
    Loop through tags =>
        If opening tag -> parentTags.push_back(tagName) -> [tag1, tag2]
        If ending tag -> remove last element of parentTags -> parentTags.pop_back(tagName) -> [tag1]
        In each tagline find attribute name and value -> (attrName = name, value = amogh)
        Generate prefix for that line by joining parentTags-> [tag1,tag2] -> tag1.tag2
        For each attrName, join withit  prefix using "~" -> tag1.tag2~name
        Insert the resultant attrName and its value as key and value respectively in hashmap
        i.e -> {
                    "tag1.tag2~name" : "name",
                }
        Read through queries and for each query check if it exists in hashmap
        If exists print its value, if not print "Not found!"
*/

int main () {
    // freopen ("input.txt", "r", stdin); 
    int n, k;
    string z;
    cin >> n >> k;
    cin.ignore();
    map<string, string> umap;
    vector<string> parentTags; 

    for (int i = 0; i < n; i++) {
        getline(cin, z);
        if (z[1] == '/') {
            parentTags.pop_back(); 
        } else {
            bool foundTag = false;
            string attr = "", value = "";
            int lastSpaceIdx;
            for (int x = 0; x < z.size(); x++) {
                if (z[x] == ' ' || z[x] == '>') {
                    if (!foundTag) {
                        parentTags.push_back(z.substr(1, x - 1));
                        foundTag = true;
                        lastSpaceIdx = x;
                    } else {
                        if (attr.size() == 0) {
                            attr = z.substr(lastSpaceIdx + 1, x - lastSpaceIdx - 1);
                            string modifiedAttr = "";
                            for (int r = 0; r < parentTags.size(); r++) {
                                modifiedAttr += parentTags[r] + ".";
                            }
                            attr = modifiedAttr.substr(0, modifiedAttr.size() - 1) + "~" + attr;
                        } else {
                            if (!(x - lastSpaceIdx == 2)) {
                                value =  z.substr(lastSpaceIdx + 1, x - lastSpaceIdx - 1);
                                umap[attr] = value;
                                attr = "";
                                value = "";
                            } 
                        }
                        lastSpaceIdx = x;
                    }
                }
            }
        }
    } 

    for (int i = 0; i < k; i++) {
        cin >> z;
        if (umap.count(z)) {
            cout << umap[z].substr(1, umap[z].size() - 2) << endl;
        } else {
            cout << "Not Found!" << endl;
        }
    }
}
