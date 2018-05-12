//
// Created by ubuntu on 5/10/18.

//

#include "NetIniFileOp.h"

using namespace boost;
using namespace std;


NetIniFileOp::NetIniFileOp(const string & filename)
  {

    //m_path = "/home/ubuntu/CLionProjects/boostCmake/" + filename;
    m_path = filename;
    property_tree::ini_parser::read_ini(m_path, m_data);

  }

  NetIniFileOp::~NetIniFileOp()
  {
    //Write();
  }

  std::vector<string> NetIniFileOp::getAllSections() {
      std::ifstream in(this->m_path);
      std::vector<std::string> sections;
      sections.clear();

      if(!in.is_open()) {
          return sections;
      }

      string s;

      while(in >> s) {
          size_t start = s.find_first_of('[');
          if(string::npos != start) {
              size_t end = s.find_first_of(']', start);
              if(string::npos != end) {
                  std::string str = s.substr(start+1, end-start-1);
                  sections.push_back(str);
              }

          }
      } // end while

      return sections;
  }

 void NetIniFileOp::Write(const string & path)
  {

    string save_path = "/home/ubuntu/CLionProjects/boostCmake/yolo.cfg_new";
    property_tree::ini_parser::write_ini(save_path, m_data);
  }


  //template <typename T>
  string NetIniFileOp::Get(const string & key)
  {
    return m_data.get<string>(key);
  }


  template <typename T>
  void NetIniFileOp:: Set(const string & key, const T & value){
    m_data.put(key, value);
  }



/*
int main() {
    CIniFile ini("tiny-yolo.cfg");
    cout << ini.Get<string>("net.batch") << endl;
    ini.Set("convolutional_0.size", 9999);
    ini.Write();
}
*/

