// Server.cpp : Defines the entry point for the console application.
//

#include "winsock2.h"
#include "questionbank.h"
#include "question.h"
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

const int NUM_PER_GAME = 10;
const int BUF_SIZE = 64;
const string account_str = "";

string Q2s(Question *ques)
{   
    string con = "";
    con += ques.body;
    con.push_back(' ');
    con += ques.option_A;
    con.push_back(' ');
    con += ques.option_B;
    con.push_back(' ');
    con += ques.option_C;
    con.push_back(' ');
    con += ques.option_D;
    return con;
}

bool check_account(string account,string password)
{   
    string file_str = account_str + account;
    ifstream fin(file_str);
    string p;
    getline(fin,p);
    if(p == password)return true;
    return false;
}

int main(int argc, char *argv[])
{
    Questionbank bank;
    srand(time(NULL));
    WSADATA wsd;    //WSADATA变量
    SOCKET sServer; //服务器套接字
    SOCKET sClient; //客户端套接字
    SOCKADDR_IN addrServ;
    ;                       //服务器地址
    char buf[BUF_SIZE];     //接收数据缓冲区
    char sendBuf[BUF_SIZE]; //返回给客户端得数据
    int retVal;             //返回值
    //初始化套结字动态库
    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
    {
        cout << "WSAStartup failed!" << endl;
        return 1;
    }

    //创建套接字
    sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == sServer)
    {
        cout << "socket failed!" << endl;
        WSACleanup(); //释放套接字资源;
        return -1;
    }

    //服务器套接字地址
    addrServ.sin_family = AF_INET;
    addrServ.sin_port = htons(4999);
    addrServ.sin_addr.s_addr = INADDR_ANY;
    //绑定套接字
    retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
    if (SOCKET_ERROR == retVal)
    {
        cout << "bind failed!" << endl;
        closesocket(sServer); //关闭套接字
        WSACleanup();         //释放套接字资源;
        return -1;
    }

    //开始监听
    cout << "listening" << endl;
    retVal = listen(sServer, 1);
    if (SOCKET_ERROR == retVal)
    {
        cout << "listen failed!" << endl;
        closesocket(sServer); //关闭套接字
        WSACleanup();         //释放套接字资源;
        return -1;
    }

    //接受客户端请求
    sockaddr_in addrClient;
    int addrClientlen = sizeof(addrClient);
    sClient = accept(sServer, (sockaddr FAR *)&addrClient, &addrClientlen);
    if (INVALID_SOCKET == sClient)
    {
        cout << "accept failed!" << endl;
        closesocket(sServer); //关闭套接字
        WSACleanup();         //释放套接字资源;
        return -1;
    }

    int op;//设置操作标志符
    char answer;//设置答案
    bool flag = false;//是否登录成功
    while (true)
    {
        //接收客户端数据
        ZeroMemory(buf, BUF_SIZE);
        retVal = recv(sClient, buf, BUF_SIZE, 0);
        if (SOCKET_ERROR == retVal)
        {
            cout << "recv failed!" << endl;
            closesocket(sServer); //关闭套接字
            closesocket(sClient); //关闭套接字
            WSACleanup();         //释放套接字资源;
            return -1;
        }
        if (buf[0] == '0')
            break;
        //cout << "receive from client:" << buf << endl;
        op = get_op(flag,buf);
        swicth(op)
        {
            case 0://登录
                sendBuf = "Please enter your account id: ";
                send(sClient, sendBuf, strlen(sendBuf), 0);
                //接收客户端数据
                ZeroMemory(buf, BUF_SIZE);
                retVal = recv(sClient, buf, BUF_SIZE, 0);
                if (SOCKET_ERROR == retVal)
                {
                    cout << "recv failed!" << endl;
                    closesocket(sServer); //关闭套接字
                    closesocket(sClient); //关闭套接字
                    WSACleanup();         //释放套接字资源;
                    return -1;
                }
                if (buf[0] == '0')
                    break;
                account = buf;//设置账号。

                sendBuf = "Please enter your password: ";
                send(sClient, sendBuf, strlen(sendBuf), 0);
                //接收客户端数据
                ZeroMemory(buf, BUF_SIZE);
                retVal = recv(sClient, buf, BUF_SIZE, 0);
                if (SOCKET_ERROR == retVal)
                {
                    cout << "recv failed!" << endl;
                    closesocket(sServer); //关闭套接字
                    closesocket(sClient); //关闭套接字
                    WSACleanup();         //释放套接字资源;
                    return -1;
                }
                if (buf[0] == '0')
                    break;
                bool res = check_account(account,buf);
                if(res == true)
                {
                    sendBuf = "You have login in the system.";
                    send(sClient, sendBuf, strlen(sendBuf), 0);
                    flag == true;
                }
                else
                {
                    sendBuf = "Your password and your account_id is not match.";
                    send(sClient, sendBuf, strlen(sendBuf), 0);
                }
                break;
            case 4://注册
                while(1)
                {
                    sendBuf = "Please enter your account id: ";
                    send(sClient, sendBuf, strlen(sendBuf), 0);
                    //接收客户端数据
                    ZeroMemory(buf, BUF_SIZE);
                    retVal = recv(sClient, buf, BUF_SIZE, 0);
                    if (SOCKET_ERROR == retVal)
                    {
                        cout << "recv failed!" << endl;
                        closesocket(sServer); //关闭套接字
                        closesocket(sClient); //关闭套接字
                        WSACleanup();         //释放套接字资源;
                        return -1;
                    }
                    if (buf[0] == '0')
                        break;
                    account = buf;//设置账号。
                    string file_str = account_str + account;
                    fstream f;
                    f.open(file_str, ios::in);
                    if(f)
                    {
                        sendBuf = "This account_id is already existed.";
                        send(sClient, sendBuf, strlen(sendBuf), 0);
                        continue;
                    }
                    else break;
                }
                sendBuf = "Please enter your password: ";
                send(sClient, sendBuf, strlen(sendBuf), 0);
                //接收客户端数据
                ZeroMemory(buf, BUF_SIZE);
                retVal = recv(sClient, buf, BUF_SIZE, 0);
                if (SOCKET_ERROR == retVal)
                {
                    cout << "recv failed!" << endl;
                    closesocket(sServer); //关闭套接字
                    closesocket(sClient); //关闭套接字
                    WSACleanup();         //释放套接字资源;
                    return -1;
                }
                if (buf[0] == '0')
                    break;
                ofstream fout(file_str);
                if(!fout)
                {
                    sendBuf = "Create account error.";
                    send(sClient, sendBuf, strlen(sendBuf), 0);
                }
                else
                {
                    fout<<buf<<endl;
                }
                fout.close();
                break;
            case 1://开始
                sendBuf = "The game begins.Enjoy yourself.";
                send(sClient, sendBuf, strlen(sendBuf), 0);
                break;
            case 2://答题
                for(int i=0;i<NUM_PER_GAME;i++)
                {
                    int s = rand()%bank.num;
                    Question temp = get_question(s);
                    answer = temp.get_answer();
                    sendBuf = Q2s(temp);
                    send(sClient, sendBuf, strlen(sendBuf), 0);
                    //接收客户端数据
                    ZeroMemory(buf, BUF_SIZE);
                    retVal = recv(sClient, buf, BUF_SIZE, 0);
                    if (SOCKET_ERROR == retVal)
                    {
                        cout << "recv failed!" << endl;
                        closesocket(sServer); //关闭套接字
                        closesocket(sClient); //关闭套接字
                        WSACleanup();         //释放套接字资源;
                        return -1;
                    }
                    if (buf[0] == '0')
                        break;

                    check_answer(answer,buf);
                }
                sendBuf = "Game over.";
                send(sClient, sendBuf, strlen(sendBuf), 0);
                break;
            case 3://退出
                sendBuf = "Exit.";
                send(sClient, sendBuf, strlen(sendBuf), 0);
            default :
                sendBuf = "Error.";
                send(sClient, sendBuf, strlen(sendBuf), 0);
        }
    }

    //退出
    closesocket(sServer); //关闭套接字
    closesocket(sClient); //关闭套接字
    WSACleanup();         //释放套接字资源;

    return 0;
}