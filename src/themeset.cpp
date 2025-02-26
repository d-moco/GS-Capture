#include "themeset.h"
#include "ui_themeset.h"

ThemeSet::ThemeSet(qcss::QtCustomStylesheet* theme, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThemeSet),
    m_currentTheme(theme)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint);
    initCtrl();
}

ThemeSet::~ThemeSet()
{
    delete ui;
}

void ThemeSet::initCtrl()
{
    ui->combox_theme->addItems(m_currentTheme->themes());
    connect(ui->combox_theme, &QComboBox::currentTextChanged, [=](const QString &text){
        m_currentTheme->setCurrentTheme(text);
        m_currentTheme->updateStylesheet();
    });
}
