#include "Utility.h"
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

static string appFilePathSuffix()
{
    static const unsigned short s_MaxCount = 1024;
    char buf[s_MaxCount] = {'\0'};
    int ret = readlink("/proc/self/exe", buf, s_MaxCount);
    string suffix("");
    if ((ret < 0) || (ret > s_MaxCount)) {
        suffix = string("");
    } else {
        string tmp(buf);
        int pos = tmp.find_last_of(char('/'));
        if (-1 == pos) {
            suffix = string("");
        }
        suffix = tmp.substr(pos + 1, tmp.length() - 1);
    }
    return suffix;
}

void singleApplication(const std::string &key)
{
    string app;
    if (0 == key.size()) {
        app = appFilePathSuffix();
    } else {
        app = key;
    }
    bool ret = true;
    string error("instance success!");
    if (app.empty()) {
        error = string("app is Empty!");
        ret = false;
    } else {
        string tmp = app;
        //        stringstream pidStr;
        //        pidStr << getpid();
        //        string pid;
        //        pidStr >> pid;
        tmp = string("/tmp/") + tmp;
        int fd = open(tmp.c_str(), O_RDWR | O_CREAT, 0666);\
        if (fd < 0) {
            error =  string("open ") + tmp + string(" error!");
            ret = false;
        } else {
            struct flock lock;
            lock.l_type = F_WRLCK;
            lock.l_start = 0;
            lock.l_whence = SEEK_SET;
            lock.l_len = 0;
            if(fcntl(fd, F_SETLK, &lock) < 0) {
                close(fd);
                error = string("app already instance!");
                ret = false;
            }
        }
    }
    cout << " singleApplication: " << app << " " << error << endl;
    if (!ret) {
        exit(EXIT_FAILURE);
    }
}

static HANDLER m_Callback(NULL);
static void* m_Parameter(NULL);

HANDLER acquirePreemptiveResource(HANDLER callback, void *parameter)
{
    HANDLER lastHandler = m_Callback;
    if ((NULL != m_Callback) && (callback != m_Callback)) {
        m_Callback(m_Parameter);
    }
    m_Callback = callback;
    m_Parameter = parameter;
    return lastHandler;
}

void clearOwner()
{
    m_Callback = NULL;
    m_Parameter = NULL;
}

