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
        bool attach(const IViewLisWPtr& lis) override;
        bool detach(const IViewLisWPtr& lis) override;
        // ---------------------------------------------

        // --- ILogger ---------------------------------
        void logIt(const std::string& msg) override;
        // ---------------------------------------------

    private:
        QWidget* m_widWin;
        QGridLayout* m_lytWin;
        QListWidget* m_lstLog;
        QPushButton* m_btnSend;

        IViewLisVec m_viewLis;

        private slots:
            void onSendClicked();
    };
}
