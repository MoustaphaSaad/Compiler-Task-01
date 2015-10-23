#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream>
#include "onlineprocessor.hpp"
#include <QDebug>

std::vector<CTools::Position> MainWindow::error_positions = std::vector<CTools::Position>();
std::vector<std::string> MainWindow::error_msgs = std::vector<std::string>();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CTools::Services::init();
    m_walker = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
    CTools::Services::terminate();
    delete m_walker;
}

void error(std::string str, CTools::Position pos){
    //int c = ui->ErrorList->children().size()+1;
    int c = MainWindow::error_msgs.size()+1;
    std::string msg = "Error #"+std::to_string(c)+":"+ str +"caused lexer error @ row: "+std::to_string(pos.row)+", col: "+std::to_string(pos.col);
    //ui->ErrorList->insertItem(c,QString::fromStdString(msg));
    MainWindow::error_positions.push_back(pos);
    MainWindow::error_msgs.push_back(msg);
    qDebug()<<msg.c_str();
    //error_positions.push_back(pos);
}

void MainWindow::CreateMachine(){
    if(m_walker)
        delete m_walker;

    std::string content = ui->LexIn->toPlainText().toStdString();
    CTools::ScanMachine* scanner = CTools::ScannerFactory::createFromString(content);
    OnlineProcessor* processor = new OnlineProcessor();
    m_walker = new CTools::MachineWalker(scanner,processor);
    m_walker->errorFunction = error;
}

void MainWindow::walk()
{
    if(!m_walker)
       return;
    //walk

    populateLists();
}

void MainWindow::populateLists()
{
    MainWindow::error_positions.clear();
    MainWindow::error_msgs.clear();
    m_symbolSet.clear();
    std::string content = ui->LangIn->toPlainText().toStdString();
    std::stringstream stream(content);

    if(!m_walker)
        return;

    CTools::MachineWalker* walker = m_walker;
    walker->reset();
    if(!walker)
        return;

    ui->TokenList->clearContents();
    ui->TokenList->setRowCount(0);
    ui->CommentList->clear();
    ui->SymbolList->clear();
    ui->ErrorList->clear();


    int row=0, col=0;
    int comments_rows = 0;
    int Symbol_rows = 0;
    int increment = 0;
    while(true){

        CTools::Token t = walker->token(stream);
        if(!t.valid)
            break;
        if(t.tag == "COMMENT"){
            ui->CommentList->insertItem(comments_rows++,QString::fromStdString(t.lexeme));
        }else{
            ui->TokenList->insertRow(row++);

            auto lexeme = new QTableWidgetItem(QString::fromStdString(t.lexeme));
            auto tag = new QTableWidgetItem(QString::fromStdString(t.tag));
            lexeme->setFlags(lexeme->flags() ^ Qt::ItemIsEditable);
            tag->setFlags(tag->flags() ^ Qt::ItemIsEditable);
            ui->TokenList->setItem(row-1,0,lexeme);
            ui->TokenList->setItem(row-1,1,tag);

            if(t.tag == "ID"){
                if(m_symbolSet.find(t.lexeme) == m_symbolSet.end()){
                    m_symbolSet.insert(t.lexeme);
                    ui->SymbolList->insertItem(Symbol_rows++, QString::fromStdString(t.lexeme));
                }
            }
        }


    }

    for(int i=0;i<MainWindow::error_positions.size();i++){
        ui->ErrorList->insertItem(i,QString::fromStdString(MainWindow::error_msgs[i]));
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->CreateMachine();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->walk();
}

void MainWindow::on_ErrorList_itemClicked(QListWidgetItem *item)
{
    int i = ui->ErrorList->currentRow();
    QTextCursor tmpCursor = ui->LangIn->textCursor();
    tmpCursor.movePosition(QTextCursor::Start);
    CTools::Position p = MainWindow::error_positions[i];
    tmpCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, p.absolute_location);
    ui->LangIn->setFocus();
    ui->LangIn->setTextCursor(tmpCursor);
}
