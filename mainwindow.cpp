#include "mainwindow.h"
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  time();
}

void MainWindow::time() {
  QTimer* timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
  timer->start(1000);
}

void MainWindow::showTime() {
  // local time
  QTime time = QTime::currentTime();
  QString time_string =
      time.toString("hh:mm:ss");  // ("hh:mm:ss") is an array !
  if (time.second() % 2 == 0) {
    time_string[2] = ' ';
    time_string[5] = ' ';
  }
  ui->lineEdit_6->setText(time_string);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() { close(); }

void MainWindow::on_pushButton_2_clicked() {
  double awc = -0.066;  // Allowance for 0.1 mm adhesive
  double ric = 1.517;
  // Refractive Index Correction for glass shim (n = 1.517):
  QString bestf = ui->lineEdit->text();
  double bestfocus = bestf.toDouble();
  QString firstread = ui->lineEdit_2->text();
  double firstreading = firstread.toDouble();
  QString secread = ui->lineEdit_3->text();
  double secoundreading = secread.toDouble();
  if (secoundreading <= firstreading) {
    double mag1st = (bestfocus - firstreading + 0.1);  // Minimum gap
    QString result1st = QString::number(mag1st);
    ui->lineEdit_4->setText(result1st);
    double req1st = (((bestfocus - firstreading + 0.1) + awc) * ric);
    // Thickness of required glass
    QString requ1st = QString::number(req1st);
    if (req1st >= 0.9 && req1st <= 2.2) {
      ui->lineEdit_5->setText(requ1st);
      ui->progressBar->setValue(req1st * 100);
      ui->lineEdit_5->setFocus();
    } else {  // QMessageBox autohide function
      QMessageBox* mbox = new QMessageBox;
      QString popup = "Please check your measuring gauge readings.";
      mbox->setText(popup);
      mbox->show();
      QTimer::singleShot(4000, mbox, SLOT(hide()));
      QString zero = "";
      ui->lineEdit->setText(zero);
      ui->lineEdit_2->setText(zero);
      ui->lineEdit_3->setText(zero);
      ui->lineEdit_4->setText(zero);
      ui->lineEdit_5->setText(zero);
      ui->progressBar->setValue(0);
      ui->lineEdit->setFocus();  // sets focus to lineEdit
    }
  }
  if (secoundreading > firstreading) {
    double mag = (bestfocus - secoundreading + 0.1);  // Minimum air gap
    QString result = QString::number(mag);
    ui->lineEdit_4->setText(result);
    double req = (((bestfocus - secoundreading + 0.1) + awc) *
                  ric);  // Thickness of required glass
    QString requ = QString::number(req);
    if (req >= 0.9 && req <= 2.2) {
      ui->lineEdit_5->setText(requ);
      ui->progressBar->setValue(req * 100);
      ui->lineEdit_5->setFocus();
    } else {
      // QMessageBox autohide function
      QMessageBox* mbox = new QMessageBox;
      QString popup = "Please check your measuring gauge readings.";
      mbox->setText(popup);
      mbox->show();
      QTimer::singleShot(4000, mbox, SLOT(hide()));
      QString zero = "";
      ui->lineEdit->setText(zero);
      ui->lineEdit_2->setText(zero);
      ui->lineEdit_3->setText(zero);
      ui->lineEdit_4->setText(zero);
      ui->lineEdit_5->setText(zero);
      ui->progressBar->setValue(0);
      ui->lineEdit->setFocus();  // sets focus to lineEdit
    }
  }
}

void MainWindow::on_pushButton_3_clicked() {
  QString zero = "";
  ui->lineEdit->setText(zero);
  ui->lineEdit_2->setText(zero);
  ui->lineEdit_3->setText(zero);
  ui->lineEdit_4->setText(zero);
  ui->lineEdit_5->setText(zero);
  ui->progressBar->setValue(89);
  ui->lineEdit->setFocus();  // sets focus to lineEdit
}

void MainWindow::on_pushButton_4_clicked() {
  ui->lineEdit_5->selectAll();
  ui->lineEdit_5->copy();
}

void MainWindow::on_pushButton_5_clicked() {
  ui->lineEdit_4->selectAll();
  ui->lineEdit_4->copy();
}

void MainWindow::on_radioButton_2_clicked() { ui->lineEdit_3->setDisabled(1); }

void MainWindow::on_radioButton_clicked() { ui->lineEdit_3->setEnabled(1); }
