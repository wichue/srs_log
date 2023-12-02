#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "srs_kernel_log.hpp"
#include "srs_app_log.hpp"
ISrsLog* _srs_log = NULL;
ISrsContext* _srs_context = NULL;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _srs_context = new ISrsContext();
    _srs_log = new SrsFileLog();
    _srs_log->initialize();

    srs_trace("hello");
}

MainWindow::~MainWindow()
{
    delete ui;
}

