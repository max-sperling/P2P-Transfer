#pragma once
/************************/
/* Author: Max Sperling */
/************************/

#include <QDialog>
#include <QFileSystemModel>
#include <QTreeView>

namespace view::view_qt
{
    class SelectDialog : public QDialog
    {
        Q_OBJECT

    public:
        SelectDialog(QWidget* parent = nullptr);

        std::vector<std::string> selectedItems() const;

    private:
        QFileSystemModel* fileSystemModel;
        QTreeView* treeView;
    };
}
