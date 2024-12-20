/************************/
/* Author: Max Sperling */
/************************/

#include "view/view_qt/ViewQt.hpp"

#include "view/view_qt/SelectDialog.hpp"

#include <QFileDialog>

#include <algorithm>
#include <iostream>

namespace view::view_qt
{
    // ***** Public ***************************************************************************************************
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

    void ViewQt::logIt(const std::string& msg)
    {
        std::cout << msg << std::endl;
        m_lstLog->addItem(QString::fromStdString(msg));
    }
    // ****************************************************************************************************************

    // ***** Slots ****************************************************************************************************
    void ViewQt::onSendClicked()
    {
        SelectDialog dialog(m_widWin);
        if (dialog.exec() != QDialog::Accepted) { return; }

        std::vector<std::string> selectedItems = dialog.selectedItems();
        if (selectedItems.empty()) { return; }

        for (IViewListener* lis : m_viewLis)
        {
            lis->onSendTriggered(selectedItems);
        }
    }
    // ****************************************************************************************************************
}
