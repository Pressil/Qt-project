#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QWidget>

namespace Ui {
class notification;
}

class notification : public QWidget
{
    Q_OBJECT

public:
    explicit notification(QWidget *parent = nullptr);
    ~notification();

signals:
    void permissionGranted();
    void permissionDenied();


private:
    Ui::notification *ui;
};

#endif // NOTIFICATION_H
