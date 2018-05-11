
//https://www.codeproject.com/Articles/10809/A-Small-Class-to-Read-INI-File
//Check the required licensing in the link above

#include "NetIniFileOp.h"
#include "InitUtils.h"
#include <string.h>
#include <cstdint>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception_ptr.hpp>

typedef  uint32_t  DWORD ;


CIniReader::CIniReader(char* szFileName) :iniOp(szFileName){

	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));
}

std::vector<std::string> CIniReader::ReadSections() {

	char sectionNames[1024];

	int nSectionNum = 0;
	m_Sections.clear();


	//DWORD retVal = GetPrivateProfileSectionNamesA(sectionNames, 1024, m_szFileName);
    DWORD  retVal = 0;
	/*for (char * p = sectionNames; *p; ++p)
	{
		std::string sectionName(p);
		m_Sections.push_back(sectionName);
		p += sectionName.size();
	}*/

    m_Sections.push_back("net");
    m_Sections.push_back("convolutional_0");
    m_Sections.push_back("maxpool_0");
    m_Sections.push_back("convolutional_1");
    m_Sections.push_back("maxpool_1");
    m_Sections.push_back("convolutional_2");
    m_Sections.push_back("maxpool_2");
    m_Sections.push_back("convolutional_3");
    m_Sections.push_back("maxpool_3");
    m_Sections.push_back("convolutional_4");
    m_Sections.push_back("maxpool_4");
    m_Sections.push_back("convolutional_5");
    m_Sections.push_back("maxpool_5");
    m_Sections.push_back("convolutional_6");
    m_Sections.push_back("convolutional_7");
    m_Sections.push_back("convolutional_8");
    m_Sections.push_back("region_0");

	return m_Sections;
}

int CIniReader::ReadInteger(char* szSection, char* szKey, int iDefaultValue) {

	//int iResult = GetPrivateProfileIntA(szSection, szKey, iDefaultValue, m_szFileName);
    string tmp1(szSection);
    string tmp2(szKey);
    string  section_key = tmp1 + "." + tmp2;
    int iResult = iDefaultValue;
    try {
        iResult =  atoi(iniOp.Get(section_key).c_str());
    } catch (boost::exception &exception1) {
        std::cout << "cfg file no such node, default value will be used!\n" << std::endl;
       // std::cerr << boost::diagnostic_information(exception1) ;
        iResult = iDefaultValue;
    }

	return iResult;
}

float CIniReader::ReadFloat(char* szSection, char* szKey, float fltDefaultValue) {

	char szResult[255];
	char szDefault[255];
	float fltResult;
	sprintf(szDefault, "%f", fltDefaultValue);
	//GetPrivateProfileStringA(szSection, szKey, szDefault, szResult, 255, m_szFileName);

    string tmp1(szSection);
    string tmp2(szKey);
    string section_key = tmp1 + "." + tmp2;

    string retValue = iniOp.Get(section_key);
    fltResult = atof(retValue.c_str());

    //fltResult = atof(szResult);

	return fltResult;
}

bool CIniReader::ReadBoolean(char* szSection, char* szKey, bool bolDefaultValue) {

	char szResult[255];
	char szDefault[255];
	bool bolResult;
	sprintf(szDefault, "%s", bolDefaultValue ? "True" : "False");
	//GetPrivateProfileStringA(szSection, szKey, szDefault, szResult, 255, m_szFileName);
	bolResult = (strcmp(szResult, "True") == 0 ||
		strcmp(szResult, "true") == 0) ? true : false;
	return bolResult;
}

void CIniReader::ReadString(char* szSection, char* szKey, const char* szDefaultValue, char *outValue)
{
	outValue[0] = '\0';
	//GetPrivateProfileStringA(szSection, szKey, szDefaultValue, outValue, 255, m_szFileName);

    string tmp1(szSection);
    string tmp2(szKey);
    string section_key = tmp1 + "." + tmp2;
    string retValue = iniOp.Get(section_key);
    strcpy(outValue, retValue.c_str());

}

CIniWriter::CIniWriter(const char* szFileName) : iniOp(szFileName) {

	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));

}

void CIniWriter::WriteInteger(char* szSection, char* szKey, int iValue){

	char szValue[255];
	sprintf(szValue, "%d", iValue);
	//WritePrivateProfileStringA(szSection, szKey, szValue, m_szFileName);
}
void CIniWriter::WriteFloat(char* szSection, char* szKey, float fltValue) {

	char szValue[255];
	sprintf(szValue, "%f", fltValue);
	//WritePrivateProfileStringA(szSection, szKey, szValue, m_szFileName);
}

void CIniWriter::WriteBoolean(char* szSection, char* szKey, bool bolValue) {

	char szValue[255];
	sprintf(szValue, "%s", bolValue ? "True" : "False");
	//WritePrivateProfileStringA(szSection, szKey, szValue, m_szFileName);
}

void CIniWriter::WriteString(char* szSection, char* szKey, char* szValue){

	//WritePrivateProfileStringA(szSection, szKey, szValue, m_szFileName);
}