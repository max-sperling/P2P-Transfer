#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IView.hpp"

#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>

#include <vector>

namespace view::view_qt
{
    class ViewQt : public QObject, public IView
    {
        Q_OBJECT

    public:
        ViewQt();
        ~ViewQt() override;

        // --- IView -----------------------------------
        bool exec() override;
        void logIt(const std::string& msg) override;
        bool attach(IViewListener* lis) override;
        bool detach(IViewListener* lis) override;
        // ---------------------------------------------

    private:
        QWidget* m_widWin;
        QGridLayout* m_lytWin;
        QListWidget* m_lstLog;
        QPushButton* m_btnSend;

        std::vector<IViewListener*> m_viewLis;

        private slots:
            void onSendClicked();
    };
}
