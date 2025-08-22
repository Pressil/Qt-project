#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QtGui>
#include <QLabel>



QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class CustomPageWidget : public QWidget {
    Q_OBJECT
public:
    explicit CustomPageWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    void showEvent(QShowEvent *event) override {
        QWidget::showEvent(event);
        emit shown();
    }

    void hideEvent(QHideEvent *event) override {
        QWidget::hideEvent(event);
        emit hidden();
    }

signals:
    void shown();
    void hidden();
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QLabel *gifLabel;


public slots:
    void switchpage_2();
    void backtopage_2();
    void backtopage_1();
    void navigateToNextPage();
    void saveDataToDatabase();
    void backtopage_3();
    void backtopage_4();
    void backtopage_5();
    void labelClicked();
    void labelClicked1();
    void labelClicked2();
    void switchpage_1();
    void backtopage_0();
    void switchpage();
    void switchtopage_9();

private slots:
    void retrieveDataFromDatabase();
    void updateDataInDatabase();
    void deleteDataFromDatabase();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;


};

#endif // WIDGET_H
