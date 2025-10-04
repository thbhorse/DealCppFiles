/***************************************************************
 * Name:      DealCppFilesMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    thb (qq1552989@126.com)
 * Created:   2025-10-01
 * Copyright: thb (kerysoft.com)
 * License:
 **************************************************************/

#include "DealCppFilesMain.h"
#include <wx/msgdlg.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <regex>

//(*InternalHeaders(DealCppFilesDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(DealCppFilesDialog)
const wxWindowID DealCppFilesDialog::ID_STATICTEXT1 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_TEXTCTRL1 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_STATICTEXT2 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_TEXTCTRL2 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_STATICTEXT3 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_TEXTCTRL3 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_STATICTEXT4 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_STATICTEXT5 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_BUTTON1 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_BITMAPBUTTON1 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_BUTTON2 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_BUTTON3 = wxNewId();
const wxWindowID DealCppFilesDialog::ID_STATICTEXT6 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DealCppFilesDialog,wxDialog)
    //(*EventTable(DealCppFilesDialog)
    //*)
END_EVENT_TABLE()

DealCppFilesDialog::DealCppFilesDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(DealCppFilesDialog)
    Create(parent, wxID_ANY, _("DealCppFiles"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(977,760));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Path"), wxPoint(16,24), wxSize(56,25), 0, _T("ID_STATICTEXT1"));
    TextPath = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(80,16), wxSize(744,32), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Old Function Name:"), wxPoint(16,56), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    TextOldFunc = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxPoint(232,56), wxSize(592,32), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("New Function Express:"), wxPoint(24,112), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    TextNewFunc = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(232,112), wxSize(592,192), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Result:"), wxPoint(16,336), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticResult = new wxStaticText(this, ID_STATICTEXT5, wxEmptyString, wxPoint(88,328), wxSize(848,104), wxBORDER_SIMPLE, _T("ID_STATICTEXT5"));
    Button1 = new wxButton(this, ID_BUTTON1, _("Start"), wxPoint(56,480), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BitmapButton1 = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxNullBitmap, wxPoint(232,488), wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
    Button2 = new wxButton(this, ID_BUTTON2, _("Quit"), wxPoint(208,480), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button3 = new wxButton(this, ID_BUTTON3, _("About"), wxPoint(360,480), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    StaticText5 = new wxStaticText(this, ID_STATICTEXT6, _("example:\nOld Function Name:\t\t_llseek\nNew Function Express: \t\tSetFilePointer((HANDLE)%1, %2, 0, %3)\n\t\t\t\tSetFilePointer(%1, %2, 0, %3 = 0 ? FILE_BEGIN)"), wxPoint(72,560), wxSize(872,128), 0, _T("ID_STATICTEXT6"));

    Connect(ID_BUTTON1, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&DealCppFilesDialog::OnStartClick);
    Connect(ID_BUTTON2, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&DealCppFilesDialog::OnQuit);
    Connect(ID_BUTTON3, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&DealCppFilesDialog::OnAbout);
    //*)
}

DealCppFilesDialog::~DealCppFilesDialog()
{
    //(*Destroy(DealCppFilesDialog)
    //*)
}

void DealCppFilesDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DealCppFilesDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

int DealCppFile(const std::string& filepath, const wxString& oldFunc, const wxString& newFunc);


int TraverseCppFiles(const wxString& mypath, const wxString& oldFunc, const wxString& newFunc, int& replaceCount) {
    int count = 0;
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator(mypath.ToStdString())) {
        std::string ext = entry.path().extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); // 转为小写
        if (entry.is_regular_file() && (ext == ".cpp" || ext == ".h")) {
            count++;
            replaceCount += DealCppFile(entry.path().string(), oldFunc, newFunc);
        }
    }
    return count;
}

void DealCppFilesDialog::OnStartClick(wxCommandEvent& event)
{
    wxString mypath = TextPath->GetValue();
    wxString oldFunc = TextOldFunc->GetValue();
    wxString newFunc = TextNewFunc->GetValue();
    int replaceCount = 0;
    int count = TraverseCppFiles(mypath, oldFunc, newFunc, replaceCount);
    StaticResult->SetLabel(wxString::Format("Processed %d cpp/h files, Replaced %d lines", count, replaceCount));
}

#include <list>
#include <sstream>

std::list<std::string> SplitParamsToList(const std::string& params) {
    std::list<std::string> paramList;
    std::stringstream ss(params);
    std::string item;
    while (std::getline(ss, item, ',')) {
        // 去除前后空格
        size_t start = item.find_first_not_of(" \t");
        size_t end = item.find_last_not_of(" \t");
        if (start != std::string::npos && end != std::string::npos)
            item = item.substr(start, end - start + 1);
        paramList.push_back(item);
    }
    return paramList;
}

int DealCppFile(const std::string& filepath, const wxString& oldFunc, const wxString& newFunc) {
    int lineNum = 0;
    int replaceCount = 0;
    std::ofstream log("d:\\temp\\DealCppFiles.log", std::ios::app);
    std::string newFuncName;
    std::list<std::string> newFuncParams;
    {
        std::string newFuncStr = newFunc.ToStdString();
        size_t paramStart = newFuncStr.find_first_of('(');
        size_t paramEnd = newFuncStr.find_last_of(')');
        if (paramStart != std::string::npos && paramEnd != std::string::npos && paramEnd > paramStart) {
            newFuncName = newFuncStr.substr(0, paramStart);
            std::string params = newFuncStr.substr(paramStart + 1, paramEnd - paramStart - 1);
            newFuncParams = SplitParamsToList(params);
        } else {
            newFuncName = newFuncStr; // 没有参数
        }
    }
    std::ifstream fileIn(filepath);
    if (!fileIn.is_open()) {
        return 0;
    }
    std::vector<std::string> lines; // 用于保存所有行
    std::string line;
    std::string oldFuncStr = oldFunc.ToStdString();
    std::regex funcRegex("\\b" + oldFuncStr + "\\b");
    while (std::getline(fileIn, line)) {
        lineNum++;
        std::smatch match;
        if (std::regex_search(line, match, funcRegex)) {//正则匹配函数名
            size_t pos = match.position(0);
            size_t endFun = std::string::npos;
            int kh = 0;
            for(size_t i=pos; i < line.length(); i++) {
                if(line[i] == '(')
                    kh++;
                else if(line[i] == ')') {
                    kh--;
                    if(kh == 0) {
                        endFun = i;
                        break;
                    }
                }
            }
            while(endFun == std::string::npos) {
                std::string nextLine;
                if (std::getline(fileIn, nextLine)) {
                    line += "\n" + nextLine;
                    lineNum++;
                    int kh = 0;
                    for(size_t i=pos; i < line.length(); i++) {
                        if(line[i] == '(')
                            kh++;
                        else if(line[i] == ')') {
                            kh--;
                            if(kh == 0) {
                                endFun = i;
                                break;
                            }
                        }
                    }
                } else {
                    break;
                }
            }
            if (endFun != std::string::npos) {
                size_t param_beg = line.find_first_of('(', pos);
                size_t param_end = std::string::npos;
                if(param_beg != std::string::npos) {
                    int kh = 0;
                    for(size_t i=1; i < endFun; i++) {
                        if(line[param_beg + i] == '(')
                            kh++;
                        else if(line[param_beg + i] == ')') {
                            kh--;
                            if(kh < 0) {
                                param_end = i + param_beg;
                                break;
                            }
                        }
                    }
                }
                if (param_beg != std::string::npos && param_end != std::string::npos && param_end > param_beg) {
                    bool notFit = false;
                    std::string params = line.substr(param_beg + 1, param_end - param_beg - 1);
                    std::list<std::string> oldParamList = SplitParamsToList(params);
                    int oldParamCount = oldParamList.size();
                    int newParamCount = newFuncParams.size();
                    std::list<std::string> newFuncParamsCopy = newFuncParams;
                    for(int j=0; j < newParamCount; j++) {
                        std::string newParam = *std::next(newFuncParamsCopy.begin(), j);
                        // 去除newParam中所有空格
                        newParam.erase(std::remove(newParam.begin(), newParam.end(), ' '), newParam.end());
                        size_t eque = newParam.find('=');
                        size_t ques = newParam.find('?');
                        size_t perc = newParam.find('%');
                        if(eque != std::string::npos && ques != std::string::npos && perc != std::string::npos && perc < eque && eque < ques) {
                            // 处理类似 %1=0?FILE_END 的三元表达式
                            int index = atoi(newParam.substr(perc + 1).c_str());
                            if(index <= oldParamCount && index >= 1) {
                                std::string oldParam = *std::next(oldParamList.begin(), index - 1);
                                std::string condi = newParam.substr(eque + 1, ques - eque - 1);
                                std::string newParam2 = newParam.substr(ques + 1);
                                if(condi == oldParam) {
                                    newParam = newParam2;
                                    size_t percentPos = newParam.find('%');
                                    if(percentPos != std::string::npos) {
                                        int index2 = atoi(newParam.substr(percentPos + 1).c_str());
                                        if(index2 <= oldParamCount && index2 >= 1) {
                                            oldParam = *std::next(oldParamList.begin(), index2 - 1);
                                            char key[10];
                                            sprintf(key, "%%%d", index2);
                                            newParam.replace(percentPos, strlen(key), oldParam);
                                        }
                                        else {
                                            //notFit = true;  有错误，但继续处理，编译器可以发现错误
                                        }
                                    }
                                } else {
                                    newParam = oldParam;
                                    notFit = true;
                                }
                                *std::next(newFuncParamsCopy.begin(), j) = newParam;
                            }
                            else {
                                // index 不合法，直接使用 newParam
                                notFit = true;
                            }
                        }
                        else if(perc != std::string::npos) {                     // 处理类似 %1, %2 的占位符
                            int index = atoi(newParam.substr(perc + 1).c_str());
                            if(index <= oldParamCount && index >= 1) {
                                std::string oldParam = *std::next(oldParamList.begin(), index - 1);
                                char key[10];
                                sprintf(key, "%%%d", index);
                                size_t keyPos = newParam.find(key);
                                if(keyPos != std::string::npos) {
                                    newParam.replace(keyPos, strlen(key), oldParam);
                                    *std::next(newFuncParamsCopy.begin(), j) = newParam;
                                }
                            }
                        }
                    }
                    std::string newParamsStr;
                    for (const auto& p : newFuncParamsCopy) {
                        if (!newParamsStr.empty()) {
                            newParamsStr += ", ";
                        }
                        newParamsStr += p;
                    }
                    if(!notFit) {//对于条件判断不符合的行，不进行替换
                        std::string newFuncWithParams = newFuncName + "(" + newParamsStr + ")";
                        line.replace(pos, param_end - pos + 1, newFuncWithParams);
                        replaceCount++;
                        log << "Replaced in file: " << filepath << " LineNum: " << lineNum << " Line: " << line << std::endl;
                    }
                }
            }
        }
        lines.push_back(line); // 保存处理后的行
    }
    fileIn.close();

    // 写回原文件
    if(replaceCount > 0) {
        std::ofstream fileOut(filepath, std::ios::trunc);
        for (const auto& l : lines) {
            fileOut << l << std::endl;
        }
        fileOut.close();
    }
    return replaceCount;
}
