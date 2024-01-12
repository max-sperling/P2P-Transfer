#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <memory>
#include <vector>

enum TransType { P2P };

class ITrans;
class IConnectionListener;

typedef std::shared_ptr<ITrans> ITransSPtr;
typedef std::vector<IConnectionListener*> IConLisVec;
