#ifndef WAITDIALOG_H
#define WAITDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QMovie>

class WaitDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WaitDialog(QDialog *parent = 0);
    ~WaitDialog();

signals:

public slots:

private:
    QLabel *label;
    QMovie *movie;

};

#endif // WAITDIALOG_H
