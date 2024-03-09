#ifndef EXPORTWINDOW_H
#define EXPORTWINDOW_H

#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <string>

using namespace std;

namespace Ui {
class ExportWindow;
}

class ExportWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ExportWindow(QWidget *parent = nullptr);
    ~ExportWindow();
    bool getTipus() const;
    bool getFormatum() const;
    string getUtvonal() const;

private slots:
    void on_exportalasPushButton_clicked();

    void on_megsePushButton_clicked();

    void on_pdfRadioButton_toggled(bool checked);

    void on_jpgRadioButton_toggled(bool checked);

    void on_keresesPushButton_clicked();

private:
    Ui::ExportWindow *ui;

    bool tipus = true; // 0=kepek, 1=pdf
    bool formatum = true; //0=png, 1=jpg
    string utvonal;
};

#endif // EXPORTWINDOW_H
