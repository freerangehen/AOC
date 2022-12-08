#include "FileTree.hpp"
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

FileTree::FileTree(string name_, int size_, FileTree* parent_)
{
    name = name_;
    size = size_;
    parent = parent_;

}

int FileTree::updateSize()
{
    int totalSize = 0;
    for (const auto &item: subfolders)
    {
        if (item->subfolders.size() == 0)
        {
            // leaf node -  just a file
            totalSize += item->size;
        } else
        {
            totalSize += item->updateSize();
        }
    }
    this->size = totalSize;
    return totalSize;
};

FileTree* FileTree::getSubfolder(string name_)
{
    for (int n=0; n<subfolders.size(); n++)
    {
        if (subfolders[n]->name == name_)
        {
            return subfolders[n];
        }
    }
}


vector<int> FileTree::getAllFolderSizes()
{
    vector<int> sizes, subfolderSize;
    if (this->subfolders.size() > 0)
    {
        for (const auto &item: this->subfolders) 
        {
            subfolderSize = item->getAllFolderSizes();
            sizes.reserve(sizes.size() + distance(subfolderSize.begin(), subfolderSize.end()));
            sizes.insert(sizes.end(), subfolderSize.begin(), subfolderSize.end());
        }
        sizes.push_back(this->size);
    }
    return sizes;

}


int FileTree::calcAllFolderSum(int threshold)
{
    int totalSize = 0;
    // if folder
    if (this->subfolders.size() > 0)
    {
        for (const auto &item: this->subfolders)
        {
            totalSize += item->calcAllFolderSum(threshold);
        }

        if (this->size < threshold)
        {
            return this->size + totalSize;
        }
        else
        {
            return totalSize;
        }
    }else
    {
        // not a folder
        return 0;
    }
}

