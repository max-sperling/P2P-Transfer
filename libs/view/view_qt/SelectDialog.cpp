/************************/
/* Author: Max Sperling */
/************************/

#include "view/view_qt/SelectDialog.hpp"

#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QLabel>
#include <QTreeView>
#include <QVBoxLayout>

namespace view::view_qt
{
    SelectDialog::SelectDialog(QWidget* parent) : QDialog(parent)
    {
        auto* layout = new QVBoxLayout(this);

        auto* label = new QLabel("Select files or directories:", this);
        layout->addWidget(label);

        fileSystemModel = new QFileSystemModel(this);
        fileSystemModel->setRootPath(QDir::rootPath());

        treeView = new QTreeView(this);
        treeView->setModel(fileSystemModel);
        treeView->setRootIndex(fileSystemModel->index(QDir::homePath()));
        treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

        layout->addWidget(treeView);

        auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &SelectDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &SelectDialog::reject);

        layout->addWidget(buttonBox);
    }

    std::vector<std::string> SelectDialog::selectedItems() const
    {
        std::vector<std::string> selectedItems;
        QModelIndexList indexes = treeView->selectionModel()->selectedIndexes();
        QSet<QModelIndex> uniqueIndexes;
        for (const QModelIndex &index : indexes)
        {
            // Ensure we only consider the first column
            if (index.column() == 0)
            {
                uniqueIndexes.insert(index);
            }
        }

        for (const QModelIndex &index : uniqueIndexes)
        {
            if (fileSystemModel->fileInfo(index).isFile() || fileSystemModel->fileInfo(index).isDir())
            {
                selectedItems.push_back(fileSystemModel->filePath(index).toStdString());
            }
        }

        return selectedItems;
    }
}
