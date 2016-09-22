//
// Created by bensoer on 20/09/16.
//

#ifndef INC_8505_A1_COVERTSOCKETS_ARGPARSER_H
#define INC_8505_A1_COVERTSOCKETS_ARGPARSER_H

#include <string>

#include <cstdlib>
#include <iostream>
#include <sstream>


using namespace std;

/**
* ArgParser makes retrieving commandline arguments easy. Pass the appropriate method the tag before the item you would
* like to retrieve from the command line args, and pass the argv array along with argc.
*/
class ArgParcer{

public:
    //finds param passed tag then gets associated value and returns it as a string
    //returns "-1" on failure to find tag
    string GetTagData(string preTag, char *argArray[], int length)
    {
        for(int i = 1; i < length; ++i)
        {
            if(preTag.compare(argArray[i])==0)
            {
                int t = i +1;
                return argArray[t];
            }
        }
        return "-1";

    }

    //finds param passed tag then gets associated value and returns it as an int
    //returns -1 on failure to find tag
    int GetTagVal(string preTag, char *argArray[], int length)
    {
        for(int i = 1; i < length; ++i)
        {
            if(preTag.compare(argArray[i])==0)
            {
                int t = i+1;

                string number = (argArray[t]);

                int num;

                istringstream( number) >> num;

                return num;
            }

        }
        return -1;

    }

    /**
     * GetTagVal fetches a parameter value and then converts it to an integer to be returned. If the value
     * can not be found, the defaultVal is returned
     * @param preTag String - Represents the tag that comes before the desired to be parsed value
     * @param argArray Char** - Array of arguments possibly containing the preTag and a value
     * @param length int - The number of entries in the argArray
     * @param defaultVal Int - The default value to be returned if the tag cannot be found
     * @return Int - The value associated with the preTag
     */
    int GetTagVal(string preTag, char *argArray[], int length, int defaultVal)
    {
        for(int i = 1; i < length; ++i)
        {
            if(preTag.compare(argArray[i])==0)
            {
                int t = i+1;

                string number = (argArray[t]);

                int num;

                istringstream( number) >> num;

                return num;
            }

        }
        return defaultVal;

    }

    /**
     * HasTagVal determines whether a tag exists in the parameters. This does not check if a value is also set
     * with the key. It only looks at whether the tag exists or not. This can be useful in scenarios where
     * the tag itself represents a boolean setting
     * @param preTag String - The tag being searched for if it exists
     * @param argArray Char** - The array of tags
     * @param length Int - The number of entries in the argArray
     * @return Bool - The state of whether the preTag exists in the argArray or not. True = It does exist
     */
    bool HasTagVal(string preTag, char *argArray[], int length){
        for(int i = 1; i < length; ++i)
        {
            if(preTag.compare(argArray[i])==0)
            {
                return true;
            }

        }
        return false;

    }

private:

};

#endif //INC_8505_A1_COVERTSOCKETS_ARGPARSER_H
