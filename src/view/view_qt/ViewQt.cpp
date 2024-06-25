/************************/
/* Author: Max Sperling */
/************************/

#include "view/view_qt/ViewQt.hpp"
#include <QFileDialog>
#include <algorithm>
#include <iostream>

using namespace std;

namespace view
{
    namespace view_qt
    {
        ViewQt::ViewQt()
        {
            m_widWin = new QWidget();
            m_lytWin = new QGridLayout();
            m_lstLog = new QListWidget();
            m_btnSend = new QPushButton("Send");
        }

        ViewQt::~ViewQt()
        {
            delete m_btnSend;
            delete m_lstLog;
            delete m_lytWin;
            delete m_widWin;
        }

        bool ViewQt::exec()
        {
            connect(m_btnSend, SIGNAL(pressed()), this, SLOT(onSendClicked()));

            m_lytWin->addWidget(m_lstLog);
            m_lytWin->addWidget(m_btnSend);

            m_widWin->setLayout(m_lytWin);
            m_widWin->show();

            return true;
        }

        void ViewQt::logIt(const string& msg)
        {
            std::cout << msg << std::endl;
            m_lstLog->addItem(QString::fromStdString(msg));
        }

        bool ViewQt::attach(IViewListener* lis)
        {
            auto iter = std::find(m_viewLis.begin(), m_viewLis.end(), lis);
            if (iter != m_viewLis.end()) { return false; }
            m_viewLis.push_back(lis);

            return true;
        }

        bool ViewQt::detach(IViewListener* lis)
        {
            auto iter = std::find(m_viewLis.begin(), m_viewLis.end(), lis);
            if (iter == m_viewLis.end()) { return false; }
            m_viewLis.erase(iter);

            return true;
        }

        void ViewQt::onSendClicked()
        {
            QString fileName = QFileDialog::getOpenFileName(m_widWin, "Send", QDir::homePath());

            if (fileName == "") { return; }

            for (IViewListener* lis : m_viewLis)
            {
                lis->onSendTriggered(fileName.toStdString());
            }
        }
    }
}
