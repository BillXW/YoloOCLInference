//
// Created by ubuntu on 5/10/18.
//

#ifndef YOLOOCLINFERENCE_NETINIFILEOP_H
#define YOLOOCLINFERENCE_NETINIFILEOP_H


#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>
using namespace std;
using namespace boost;

//
class NetIniFileOp
{
    //

    string m_path;
    property_tree::ptree m_data;

public:
    //
    NetIniFileOp(const string & filename);

    ~NetIniFileOp();


    void Write(const string & path="");


    //template <typename T>
    string Get(const string & key);


    template <typename T>
    void Set(const string & key, const T & value);

    std::vector<string> getAllSections();


};



#endif //YOLOOCLINFERENCE_NETINIFILEOP_H
