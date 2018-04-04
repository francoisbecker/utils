#ifndef STRING_UTILS_HPP_INCLUDED
#define STRING_UTILS_HPP_INCLUDED

/**
 @file string_utils.hpp
 @author François Becker
 
MIT License

Copyright (c) 2017 François Becker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <string>
#include <vector>
#include <sstream>

namespace fbu
{
    namespace string
    {
        //==============================================================================
        inline void find_and_replace(std::string& source, std::string const& find, std::string const& replace)
        {
            for(std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
            {
                source.replace(i, find.length(), replace);
                i += replace.length();
            }
        }
        
        inline std::vector<std::string> string_split(const std::string& pString, char pSplitChar)
        {
            std::istringstream split(pString);
            std::vector<std::string> tokens;
            for (std::string each; std::getline(split, each, pSplitChar); tokens.push_back(each));
            
            return tokens;
        }
        
        //==============================================================================
        inline std::vector<std::string> string_split(std::string pString, const char* pDelimiter)
        {
            std::vector<std::string> strings;
            
            std::string::size_type pos = 0;
            std::string::size_type prev = 0;
            while ((pos = pString.find(pDelimiter, prev)) != std::string::npos)
            {
                strings.push_back(pString.substr(prev, pos - prev));
                prev = pos + 1;
            }
            
            // To get the last substring (or only, if delimiter is not found)
            strings.push_back(pString.substr(prev));
            
            return strings;
        }
        
        //==============================================================================
        template<typename T>
        const std::string convert_to_string(const T &v)
        {
            std::ostringstream ss;
            ss << v;
            return ss.str();
        };
        
        //==============================================================================
        inline bool beginsWith(const std::string& pFullString, const std::string& pRoot)
        {
            return (pFullString.size() >= pRoot.size())
            && equal(pRoot.begin(), pRoot.end(), pFullString.begin());
        }
        
        //==============================================================================
        inline bool endsWith(const std::string& pFullString, const std::string& pEnding)
        {
            return (pFullString.length() >= pEnding.length())
            && (0 == pFullString.compare (pFullString.length() - pEnding.length(), pEnding.length(), pEnding));
        }
        
        //==============================================================================
        inline std::string removeEnding(const std::string& pString, const std::string& pEnding)
        {
            size_t lFound = pString.rfind(pEnding);
            if (lFound != std::string::npos)
            {
                std::string lCopy(pString);
                return lCopy.erase(lFound);
            }
            return pString;
        }
        
#if FBU_UNIT_TESTS
        // TODO: move this to a unit test file
        static struct c_ut
        {
            c_ut()
            {
                assert(removeEnding("aaaaa.bbb", ".bbb") == "aaaaa");
                assert(removeEnding("aaaaa.bbb", ".ccc") == "aaaaa.bbb");
            }
        } ut;
#endif
    }
}

#endif
