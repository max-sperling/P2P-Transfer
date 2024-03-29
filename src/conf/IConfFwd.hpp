#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>

enum ConfType { Json };

class IConf;
struct ConnectionDetails;

typedef std::shared_ptr<IConf> IConfSPtr;
