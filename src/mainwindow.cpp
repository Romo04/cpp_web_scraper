//
// Created by rpena on 7/1/25.
//

#include "mainwindow.hpp"
#include <QString>
#include "html_parser.hpp"
#include "http_client.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchButton_clicked()
{
    ui->resultsTextEdit->clear();
    try
    {
        HttpClient client;
        std::string html = client.fetch(ui->urlLineEdit->text().toStdString());

        HtmlParser parser(html);
        int total = parser.countOcurrences(ui->keywordLineEdit->text().toStdString());
        auto snippets = parser.getSnippets(ui->keywordLineEdit->text().toStdString());

        ui->resultsTextEdit->append("Found " + QString::number(total) + " ocurrences:\n");

        for (const auto &s : snippets)
        {
            ui->resultsTextEdit->append("..." + QString::fromStdString(s) + "... \n");
        }
    }
    catch (const std::exception& e)
    {
        ui->resultsTextEdit->append("Error: " + QString::fromUtf8(e.what()));
    }
}