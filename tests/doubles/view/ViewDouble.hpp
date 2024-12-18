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
    bool exec() override;
    void logIt(const std::string& msg) override;
    bool attach(IViewListener* lis) override;
    bool detach(IViewListener* lis) override;
    // ---------------------------------------

    /**
     * @param[in] files ... File paths
     */
    void simulateSend(const std::vector<std::string>& files);

  private:
    std::vector<IViewListener*> m_viewLis;
  };
}
