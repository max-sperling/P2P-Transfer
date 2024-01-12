#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "trans/ITrans.hpp"
#include "view/IView.hpp"
#include "conf/IConfFwd.hpp"
#include <QObject>
#include <memory>
#include <string>

class Client : public QObject, public IViewListener
{
    Q_OBJECT

public:
    /**
     * @param[in] view ... View
     * @param[in] det  ... Connection details
     * @param[in] lis  ... Connection listener
     */
    Client(IViewSPtr view, const std::shared_ptr<ConnectionDetails>& det,
           const std::shared_ptr<IConLisVec>& lis);
    ~Client();

    // --- IViewListener ---------------------
    virtual void onSendTriggered(const std::string& file) override;
    // ---------------------------------------

private:
    IViewSPtr m_view;

    std::shared_ptr<ConnectionDetails> m_conDet;
    std::shared_ptr<IConLisVec> m_conLis;
};
