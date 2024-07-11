/************************/
/* Author: Max Sperling */
/************************/

#include "view/view_qt/SelectDialog.hpp"
#include <QFileDialog>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QDialog>

namespace view
{
    namespace view_qt
    {
        SelectDialog::SelectDialog(QWidget* parent) : QDialog(parent)
        {
            QVBoxLayout *layout = new QVBoxLayout(this);

            QLabel *label = new QLabel("Select files or directories:", this);
            layout->addWidget(label);

            fileSystemModel = new QFileSystemModel(this);
            fileSystemModel->setRootPath(QDir::rootPath());

            treeView = new QTreeView(this);
            treeView->setModel(fileSystemModel);
            treeView->setRootIndex(fileSystemModel->index(QDir::homePath()));
            treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

            layout->addWidget(treeView);

            QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
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
                // Ensure we only consider the first column (column 0)
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
}
