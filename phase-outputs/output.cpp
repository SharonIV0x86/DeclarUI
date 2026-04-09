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
    comp0->setWindowTitle("Secure Login");
    comp0->resize(500, 500);
    comp0->setStyleSheet("background-color: #415132;");
    QVBoxLayout *layoutcomp0 = new QVBoxLayout();
    QVBoxLayout *comp1 = new QVBoxLayout();
    QLabel *comp2 = new QLabel();
    comp2->setStyleSheet("color: #ffffff;");
    comp2->setText("Secure Access Portal");
    comp2->setStyleSheet("color: #ffffff;");
    comp1->addWidget(comp2);
    QLabel *comp3 = new QLabel();
    comp3->setStyleSheet("color: #bbbbbb;");
    comp3->setText("Please login to continue");
    comp3->setStyleSheet("color: #bbbbbb;");
    comp1->addWidget(comp3);
    QVBoxLayout *comp4 = new QVBoxLayout();
    QLabel *comp5 = new QLabel();
    comp5->setStyleSheet("color: #ffffff;");
    comp5->setText("Username");
    comp5->setStyleSheet("color: #ffffff;");
    comp4->addWidget(comp5);
    QLineEdit *comp6 = new QLineEdit();
    comp6->setPlaceholderText("Enter your username");
    comp4->addWidget(comp6);
    QLabel *comp7 = new QLabel();
    comp7->setStyleSheet("color: #ffffff;");
    comp7->setText("Password");
    comp7->setStyleSheet("color: #ffffff;");
    comp4->addWidget(comp7);
    QLineEdit *comp8 = new QLineEdit();
    comp8->setPlaceholderText("Enter your password");
    comp4->addWidget(comp8);
    comp1->addLayout(comp4);
    QHBoxLayout *comp9 = new QHBoxLayout();
    QPushButton *comp10 = new QPushButton();
    comp10->setStyleSheet("color: #00c853;");
    comp10->setText("Sign In");
    comp10->setStyleSheet("color: #00c853;");
    comp9->addWidget(comp10);
    QPushButton *comp11 = new QPushButton();
    comp11->setStyleSheet("color: #ff5252;");
    comp11->setText("Reset");
    comp11->setStyleSheet("color: #ff5252;");
    comp9->addWidget(comp11);
    comp1->addLayout(comp9);
    QVBoxLayout *comp12 = new QVBoxLayout();
    QLabel *comp13 = new QLabel();
    comp13->setStyleSheet("color: #888888;");
    comp13->setText("──────────── OR ────────────");
    comp13->setStyleSheet("color: #888888;");
    comp12->addWidget(comp13);
    QHBoxLayout *comp14 = new QHBoxLayout();
    QPushButton *comp15 = new QPushButton();
    comp15->setStyleSheet("color: #4285F4;");
    comp15->setText("Login with Google");
    comp15->setStyleSheet("color: #4285F4;");
    comp14->addWidget(comp15);
    QPushButton *comp16 = new QPushButton();
    comp16->setStyleSheet("color: #ffffff;");
    comp16->setText("Login with GitHub");
    comp16->setStyleSheet("color: #ffffff;");
    comp14->addWidget(comp16);
    comp12->addLayout(comp14);
    comp1->addLayout(comp12);
    QVBoxLayout *comp17 = new QVBoxLayout();
    QLabel *comp18 = new QLabel();
    comp18->setStyleSheet("color: #4fc3f7;");
    comp18->setText("Forgot Password?");
    comp18->setStyleSheet("color: #4fc3f7;");
    comp17->addWidget(comp18);
    QLabel *comp19 = new QLabel();
    comp19->setStyleSheet("color: #4fc3f7;");
    comp19->setText("Create New Account");
    comp19->setStyleSheet("color: #4fc3f7;");
    comp17->addWidget(comp19);
    comp1->addLayout(comp17);
    QLabel *comp20 = new QLabel();
    comp20->setStyleSheet("color: #777777;");
    comp20->setText("© 2026 Unambigous Lexemes. All rights reserved.");
    comp20->setStyleSheet("color: #777777;");
    comp1->addWidget(comp20);
    layoutcomp0->addLayout(comp1);
    comp0->setLayout(layoutcomp0);
    comp0->show();
    comp0->setAutoFillBackground(true);
    return app.exec();
}
