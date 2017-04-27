#include "findpaths.h"

//this recursive file iteration method was adapted from
//http://stackoverflow.com/questions/983376/recursive-folder-scanning-in-c

int findpaths::callback(const char *fpath, const struct stat *sb, int typeflag)
{
        /* if it's a file */
        if (typeflag == FTW_F) {
            int i;
            /* for each filter, */
            for (i = 0; i < sizeof(filters) / sizeof(filters[0]); i++) {
                /* if the filename matches the filter, */
                if (fnmatch(filters[i], fpath, FNM_CASEFOLD) == 0) {
                    /* do something */
                    fpath=fpath+2;
                    paths.emplace_back((string)fpath);



                    //paths.push_back(fpath);
                    break;
                }
            }
        }

        /* tell ftw to continue */
        return 0;
}

vector<string> findpaths::returnPaths()
{
    return paths;
}

vector<string> findpaths::paths;

