#include "exportwindow.h"
#include "ui_exportwindow.h"

ExportWindow::ExportWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExportWindow)
{
    ui->setupUi(this);

    //felulet beallitas
    ui->pdfRadioButton->setChecked(true);
    ui->jpgRadioButton->setChecked(true);

    ui->stackedWidget->setCurrentWidget(ui->uresPage);
}

ExportWindow::~ExportWindow()
{
    delete ui;
}

bool ExportWindow::getTipus() const
{
    return tipus;
}

bool ExportWindow::getFormatum() const
{
    return formatum;
}

string ExportWindow::getUtvonal() const
{
    return utvonal;
}

void ExportWindow::on_exportalasPushButton_clicked()
{
    if(ui->utLineEdit->text().toStdString() != "")
    {
        accept();
    }else{
        QMessageBox::warning(this, "Figyelmeztetés!", "Nincs megadva elérési útvonal!");
    }
}

void ExportWindow::on_megsePushButton_clicked()
{
    reject();
}

void ExportWindow::on_pdfRadioButton_toggled(bool checked)
{
    tipus = checked;

    if(checked)
    {
        ui->stackedWidget->setCurrentWidget(ui->uresPage);
    }else{
        ui->stackedWidget->setCurrentWidget(ui->kepekPage);
    }
}

void ExportWindow::on_jpgRadioButton_toggled(bool checked)
{
    formatum = checked;
}

void ExportWindow::on_keresesPushButton_clicked()
{
    QString text = QFileDialog::getExistingDirectory();

    ui->utLineEdit->setText(text);
    utvonal = text.toStdString();
}
