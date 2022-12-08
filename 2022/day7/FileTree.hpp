#include <vector>
#include <boost/algorithm/string.hpp>

#ifndef FileTree_HPP
#define FileTree_HPP

using namespace std;

class FileTree
{
    public:
        string name;
        int size;
        vector<FileTree*> subfolders;
        FileTree* parent;
        FileTree(string name_, int size_, FileTree* parent_);
        int updateSize();
        FileTree* getSubfolder(string name_);
        int calcAllFolderSum(int threshold);
        vector<int> getAllFolderSizes();

};
#endif

















