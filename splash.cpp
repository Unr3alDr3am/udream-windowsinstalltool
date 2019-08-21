#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "splash.h"
#include "ui_splash.h"
#include "QMessageBox"
#include "QApplication"
#include <stdio.h>
#include <dismapi.h>
#include <wimgapi.h>
#include <qdebug.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include <ShlObj.h>

bool isok;
using namespace std;
splash::splash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::splash)
{
    ui->setupUi(this);
    isok = false;
    HRESULT hres;
    hres = DismInitialize(DismLogErrorsWarningsInfo,L"./udream_dismlog.txt",NULL);
    if(hres!=S_OK)
    {
        QMessageBox::critical(this,"init failed","dism init error");
        QApplication::quit();
    }
    char buffer[MAX_PATH];
    char strout[] = "";
    GetSystemDirectoryA(buffer,MAX_PATH);
    strout[0] = buffer[0];
    DWORD nbuffer = MAX_PATH;
    CHAR lpbuffer[MAX_PATH];
    DWORD res;
    res = GetLogicalDriveStringsA(nbuffer,lpbuffer);
    if(res >0 && res <MAX_PATH)
    {
        CHAR *ptr;
        ptr = lpbuffer;
        while(*ptr)
        {
            QString str(ptr);
            qDebug()<<str;
            if(str[0] == strout[0])
            {
                isok = false;
                 ui->comboBox_2->addItem(str + "[will not work on this partition]");
            }
            else
            {
                 ui->comboBox_2->addItem(str);
            }
            ptr+=strlen(ptr)+1;
        }
        ui->label_6->setText("");
    }
    else
    {
        QMessageBox::critical(this,"udream software init error","can't get partition table or partition table is null");
        QApplication::quit();
    }
}

splash::~splash()
{
    delete ui;
}

void splash::on_pushButton_2_clicked()
{
    if(QMessageBox::question(this,"are you sure?","please make sure software isn't working.",QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        DismShutdown();
        QApplication::quit();
    }
}

void splash::closeEvent(QCloseEvent *e)
{
    if(QMessageBox::question(this,"are you sure?","please make sure software isn't working.",QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
       DismShutdown();
       e->accept();
    }
    else {
        e->ignore();
    }
}

void splash::on_commandLinkButton_clicked()
{
    ui->label_6->setText("writing image to partition,the ui maybe freeze during applying");
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMinimum(0);
    if(ui->lineEdit->text() == "")
    {
        QMessageBox::critical(this,"udream software error","invalid image file path");
        ui->lineEdit->setText("");
        ui->progressBar->setMaximum(100);
        ui->progressBar->setMinimum(0);
    }
    else
    {
        if(isok == false)
        {
            QMessageBox::critical(this,"udream software error","can't be null");
            ui->progressBar->setMaximum(100);
            ui->progressBar->setMinimum(0);
        }
        else
        {
            DWORD  dwCreateFlags = 0,
                    dwCreateResult = 0,
                    dwImageIndex = 1;
            std::string str = ui->lineEdit->text().toStdString();
            std::wstring wstr(str.length(), L' ');
            std::copy(str.begin(), str.end(), wstr.begin());
            LPCWSTR path = wstr.c_str();
            HANDLE hWim;
            hWim = WIMCreateFile(path,WIM_GENERIC_READ,WIM_OPEN_EXISTING,dwCreateFlags,0,&dwCreateResult);
            if(hWim == NULL)
            {
                ui->progressBar->setMaximum(100);
                ui->progressBar->setMinimum(0);
                QMessageBox::critical(this,"udream software error","can't access image file");
                return;
            }
            else
            {
                WIM_INFO wiminfo= {0};
                BOOL bret;
                bret = WIMGetAttributes(hWim,&wiminfo,sizeof (wiminfo));
                if(!bret)
                {
                    ui->progressBar->setMaximum(100);
                    ui->progressBar->setMinimum(0);
                    QMessageBox::critical(this,"udream software error","get info error");
                    return;
                }

                std::string str1 = QString(ui->comboBox_2->currentText()).toStdString();
                std::wstring wstr1(str1.length(), L' ');
                std::copy(str1.begin(), str1.end(), wstr1.begin());
                LPCWSTR path1 = wstr1.c_str();

                BOOL succ = WIMSetTemporaryPath(hWim,path1);
                if(succ == false)
                {
                    ui->progressBar->setMaximum(100);
                    ui->progressBar->setMinimum(0);
                    QMessageBox::critical(this,"udream software error","set temp directory error");
                    return;
                }
                dwImageIndex = ui->comboBox->currentIndex()+1;
                HANDLE himage;
                himage = 0;
                himage = WIMLoadImage(hWim,dwImageIndex);
                if(!himage)
                { 
                    ui->progressBar->setMaximum(100);
                    ui->progressBar->setMinimum(0);
                    QMessageBox::critical(this,"udream software error","parse image error");
                    return;
                }
                else
                {
                    ui->progressBar->setMaximum(0);
                    ui->progressBar->setMinimum(0);
                    qDebug()<<himage;
                    qDebug()<<"OK";
                    BOOL ares;
                    ares = WIMApplyImage(himage,path1,WIM_FLAG_INDEX);
                    if(!ares)
                    {
                         ui->label_6->setText("apply image failed");
                    }
                    else
                    {
                        ui->label_6->setText("apply image successful");
                    }
                }
            }
        }
    }
}

void splash::on_lineEdit_textChanged(const QString &arg1)
{
   string path;
   path = ui->lineEdit->text().toStdString();
   qDebug()<<QString::fromStdString(path);
   if(path.find(".wim",0) < path.length() || path.find(".vhd",0) < path.length())
   {
       ui->label_6->setText("parsing files");
       char c[MAX_PATH];
       strcpy(c,path.c_str());
       qDebug()<<c;
       if(access(c,0) == -1)
       {
           QMessageBox::critical(this,"udream software error","file does not exist or access denied");
           ui->lineEdit->setText("");
           ui->progressBar->setMaximum(100);
           ui->label_6->setText("parse file error");
       }
       else
       {
            DismImageInfo *imageinfo;
            uint count;
            HRESULT hres;
            std::wstring wstr(path.length(), L' ');
            std::copy(path.begin(), path.end(), wstr.begin());
            LPCWSTR path = wstr.c_str();
            hres = DismGetImageInfo(path,&imageinfo,&count);
            if(hres != S_OK)
            {
                QMessageBox::critical(this,"udream software error","get image information error");
                ui->progressBar->setMaximum(100);
                ui->label_6->setText("get information error");
            }
            else
            {
                ui->comboBox->clear();
                for(int i = 0;i < count;i++)
                {
                    ui->comboBox->addItem(QString::fromStdWString(imageinfo[i].ImageName));
                }
                ui->label_6->setText("");
                isok = true;
            }
       }
   }
   else if(path.find(".iso",0) < path.length())
   {
       ui->progressBar->setMaximum(0);
       ui->progressBar->setMinimum(0);
       ui->label_6->setText("mount iso image ");
       char c[MAX_PATH];
       strcpy(c,path.c_str());
       if(access(c,0) == -1)
       {
           QMessageBox::critical(this,"udream software error","file does not exist or access denied");
           ui->lineEdit->setText("");
           ui->progressBar->setMaximum(100);
           ui->label_6->setText("mount iso failed");
           ui->progressBar->setMaximum(100);
           ui->progressBar->setMinimum(0);
       }
       else
       {
           QString cmd = "powershell mount-diskimage -ImagePath \""+ ui->lineEdit->text() + "\"";
           string str = cmd.toStdString();
           const char* ch = str.c_str();
           if(system(ch) == -1)
           {
               QMessageBox::critical(this,"udream software error","mount iso file error");
               ui->lineEdit->setText("");
               ui->label_6->setText("mount iso failed");
               ui->progressBar->setMaximum(100);
               ui->progressBar->setMinimum(0);
           }
           else
           {
               DWORD nbuffer = MAX_PATH;
               CHAR lpbuffer[MAX_PATH];
               DWORD res;
               res = GetLogicalDriveStringsA(nbuffer,lpbuffer);
               if(res >0 && res <MAX_PATH)
               {
                   int tag = 0;
                   QString prt;
                   CHAR *ptr;
                   ptr = lpbuffer;
                   while(*ptr)
                   {
                       QString str(ptr);
                       qDebug()<<str;
                       for (int i = 0 ; i < ui->comboBox_2->count() -1; i++) {
                           if(str == ui->comboBox_2->itemText(i))
                           {
                               tag = 0;
                           }
                           else
                           {
                               tag = 1;
                               prt = str;
                               break;
                           }
                       }
                       ptr+=strlen(ptr)+1;
                   }
                   if(tag == 1)
                   {
                        qDebug()<<"mount ok";
                        qDebug()<<"image path:" + prt;
                        string path;
                        path = prt.toStdString() + "\\sources\\install.wim";
                        qDebug()<< QString::fromStdString(path);
                        char c[MAX_PATH];
                        strcpy(c,path.c_str());
                        //Sleep(3000);
                        if(access(c,0) == -1)
                        {
                            QMessageBox::critical(this,"udream software error","can't find image file on default path:" + prt  + "sources\\install.wim");
                            ui->lineEdit->setText("");
                            ui->label_6->setText("mount iso failed");
                            ui->progressBar->setMaximum(100);
                            ui->progressBar->setMinimum(0);
                        }
                        else
                        {
                            //Sleep(1000);
                            ui->lineEdit->setText(prt + "\\sources\\install.wim");
                        }
                   }

               }
               else
               {
                   QMessageBox::critical(this,"udream software load error","can't get partition table or partition table is null");
               }
           }
       }
   }
}

void splash::on_pushButton_clicked()
{
        ui->progressBar->setMaximum(0);
        ui->progressBar->setMinimum(0);
        ui->label_6->setText("opening format window");
        DWORD fres;
        qDebug()<<ui->comboBox_2->currentText().at(0).toLatin1();
        fres = SHFormatDrive((HWND)this->winId(),ui->comboBox_2->currentText().at(0).toLatin1() -65,SHFMT_ID_DEFAULT,SHFMT_OPT_FULL);
        if(fres == SHFMT_ERROR || fres == SHFMT_CANCEL || fres == SHFMT_NOFORMAT)
        {
            ui->progressBar->setMinimum(0);
            ui->progressBar->setMaximum(100);
            ui->progressBar->setValue(100);
            ui->label_6->setText("format error");
        }
        else
        {
            ui->progressBar->setMinimum(0);
            ui->progressBar->setMaximum(100);
            ui->progressBar->setValue(100);
            ui->label_6->setText("successful format");
        }
}
