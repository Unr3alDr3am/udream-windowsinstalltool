#ifndef SPLASH_H
#define SPLASH_H

#include <QDialog>
#include <QCloseEvent>
namespace Ui {
class splash;
}

class splash : public QDialog
{
    Q_OBJECT

public:
    explicit splash(QWidget *parent = nullptr);
    ~splash();
private slots:
    void on_pushButton_2_clicked();
    void on_commandLinkButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::splash *ui;
protected:
    void closeEvent(QCloseEvent *e);
};

#endif // SPLASH_H
