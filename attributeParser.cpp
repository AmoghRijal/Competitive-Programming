// Hacker rank attribute parser C++ problem

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h> 

using namespace std;

/*
    Thought process =>

    <tag1 value = "value">
    <tag2 name = "name">
    </tag2>
    </tag1> 
    <tag3 another="another" final="final">
    </tag3>

    => 
    tag1~value = value
    tag2~name = name
    tag3~another = another
    tag3~final = final

    =>  
    line 1 => parentTags.push(tag1) => [tag1] ; { tag1~value : value }
    line 2 => if (parentTags exist) => 'tag1' => tag1.tag2~name : name => {tag1~value : value, tag1.tag2~name : name } => parenttag.push(tag2)
    line 3 => [tag1, tag2], { tag1~value : value, tag1.tag2~name : name } => [tag1]
    line 4 => [tag1] => []; 
    line 5 => {tag1~value : value, tag1.tag2~name : name, tag3~another: another, tag3~final: final } => [tag3]
    line 6 => [tag3] => [];
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
