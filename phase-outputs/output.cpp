#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget *comp0 = new QWidget();
    comp0->setWindowTitle("Login");
    comp0->resize(400, 300);
    comp0->setStyleSheet("background-color: gray;");
    QVBoxLayout *layoutcomp0 = new QVBoxLayout();
    QVBoxLayout *comp1 = new QVBoxLayout();
    QLabel *comp2 = new QLabel();
    comp2->setStyleSheet("color: black;");
    comp2->setText("Welcome Back");
    comp2->setStyleSheet("color: black;");
    comp1->addWidget(comp2);
    QLineEdit *comp3 = new QLineEdit();
    comp3->setPlaceholderText("Username");
    comp1->addWidget(comp3);
    QLineEdit *comp4 = new QLineEdit();
    comp4->setPlaceholderText("Password");
    comp1->addWidget(comp4);
    QPushButton *comp5 = new QPushButton();
    comp5->setStyleSheet("color: green;");
    comp5->setText("Sign In");
    comp5->setStyleSheet("color: green;");
    comp1->addWidget(comp5);
    layoutcomp0->addLayout(comp1);
    comp0->setLayout(layoutcomp0);
    comp0->show();
    comp0->setAutoFillBackground(true);
    return app.exec();
}
