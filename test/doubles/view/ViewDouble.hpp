#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include "view/IView.hpp"
#include <string>
#include <vector>

namespace view
{
  class ViewDouble : public IView
  {
  public:
    // --- IView -----------------------------
    bool start() override;
    void logIt(const std::string& msg) override;
    bool attach(IViewListener* lis) override;
    bool detach(IViewListener* lis) override;
    // ---------------------------------------

    /**
     * @param[in] file ... File path
     */
    void simulateSend(const std::string& file);

  private:
    std::vector<IViewListener*> m_viewLis;
  };
}
