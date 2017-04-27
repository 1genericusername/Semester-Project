#ifndef FINDPATHS_H
#define FINDPATHS_H
#include <ftw.h>
#include <string>
#include <fnmatch.h>
#include <algorithm>
#include <vector>

using namespace std;

class findpaths{

    private:

        static constexpr const char *filters[] = {"*.pdf"};
        static vector<string> paths;

    public:

        static int callback(const char *, const struct stat *, int);
        vector<string> returnPaths();

};

#endif // FINDPATHS_H
