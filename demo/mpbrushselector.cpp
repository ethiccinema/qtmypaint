/* brushlib - The MyPaint Brush Library (demonstration project)
 * Copyright (C) 2013 POINTCARRE SARL / Sebastien Leon email: sleon at pointcarre.com
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 */
#include "mpbrushselector.h"

#include <QDir>
#include <QListWidget>

#define BRUSH_CONTENT_EXT ".myb"
#define BRUSH_PREVIEW_EXT "_prev.png"
#define BRUSH_LIST        "brushes.conf"
#define ICON_SZ           64

MPBrushSelector::MPBrushSelector(const QString &brushLibPath, QWidget *p_parent):
  QTabWidget   (p_parent),
  m_brushesPath(brushLibPath)
{
    // First, we parse the "order.conf" file to fill m_brushLib
    QFile fileOrder(brushLibPath + QDir::separator() + BRUSH_LIST);
    if (fileOrder.open(QIODevice::ReadOnly))
    {
        // Decode the order info. This code replace the auto-parse code (commented below)
        // Note about encoding : we consider this is ASCII file (UTF8 would be safer
        // but this is libMyPaint dev team decision)
        QString     currentGroup; // no group for now.
        QStringList brushesGroup;
        while (!fileOrder.atEnd())
        {
            QString line ( fileOrder.readLine().trimmed() ); // Get a line without begin/end extra space chars
            if (line.isEmpty() || line.startsWith("#")) continue; // empty line or starting with # are ignored
            if (line.startsWith("Group:")) // brushes below this line are owned by this group:
            {
                // first, we store the last brushesGroup (if any). Note that declaring 2 groups with the same name is wrong (only the last one will be visible)
                if (!currentGroup.isEmpty() && !brushesGroup.isEmpty()) m_brushLib.insert(currentGroup, brushesGroup);
                // Now, we prepare to get the brushes for this new group:
                currentGroup = line.section(':',1).trimmed(); // Get the name after the first ':' separator
                brushesGroup.clear();
                continue;
            }
            // Ok, line contains a (partial) file path. Let's check that the file exists before we include it:
            if (QFileInfo(brushLibPath + QDir::separator() + line + BRUSH_CONTENT_EXT).isReadable()) brushesGroup << line;
        }
        // last group :
        if (!currentGroup.isEmpty() && !brushesGroup.isEmpty()) m_brushLib.insert(currentGroup, brushesGroup);

        // Now we create a QListWidget (displaying icons) for each stringList
        foreach (const QString &caption, m_brushLib.keys())
        {
            const QStringList subList = m_brushLib.value(caption);
            if (subList.isEmpty()) continue; // this should not happen...
            QListWidget* p_lWdgt = new QListWidget();
            p_lWdgt->setUniformItemSizes(true);
            p_lWdgt->setViewMode        (QListView::IconMode);
            p_lWdgt->setResizeMode      (QListView::Adjust);
            p_lWdgt->setMovement        (QListView::Static);
            p_lWdgt->setFlow            (QListView::LeftToRight);
            p_lWdgt->setSelectionMode   (QAbstractItemView::SingleSelection);
            p_lWdgt->setIconSize        (QSize(ICON_SZ,ICON_SZ));
            connect(p_lWdgt, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(itemClicked(QListWidgetItem*)));
            // Add this ListWidget to the TabWidget:
            addTab(p_lWdgt, caption);
            // Populate the ListWidget with brushes (and their preview):
            for (int n = 0 ; n < subList.count() ; n++)
            {
                QString name (subList[n]);
                QIcon preview(m_brushesPath + QDir::separator() + name + BRUSH_PREVIEW_EXT);
                QListWidgetItem* p_item = new QListWidgetItem(preview, QString(), p_lWdgt, n); // no need to show the name as it is already visible in preview
                //p_item->setIconSize(QSize(128,128));
                p_item->setToolTip(QString("%1 in \"%2\".").arg(name).arg(caption));
            }
        }
        // for now, no brush is selected. Expecting some order from owner...
    }
}

void MPBrushSelector::itemClicked(QListWidgetItem *p_item)
{
    QListWidget* p_lWdgt = p_item->listWidget();
    if (p_lWdgt)
    {
        QString caption;
        // first of all, we will deselect all other items in other panels :
        for (int p = 0 ; p < count() ; p++)
        {
            QListWidget* p_lWdgt2 = dynamic_cast<QListWidget*>(widget(p));
            if (p_lWdgt2 != p_lWdgt) p_lWdgt2->clearSelection(); else caption = tabText(p);
        }
        // fine, let's read this one and emit the content to any receiver:
        const QStringList subList = m_brushLib.value(caption);
        QFile f( m_brushesPath + QDir::separator() + subList.at(p_item->type()) + BRUSH_CONTENT_EXT );
        //    qDebug(f.fileName().toAscii());
        if (f.open( QIODevice::ReadOnly ))
        {
            QByteArray content = f.readAll();
            content.append( (char)0 );
            emit brushSelected(content); // Read the whole file and broadcast is as a char* buffer
        }
    }
}

void MPBrushSelector::selectBrush (QString brushName)
{
    if (!isValid()) return;
    QListWidget*      p_page = NULL;
    QListWidgetItem * p_item = NULL;
    // We search for the brush requested :
    for (int page = count()-1 ; page >= 0 && !p_item ; page--)
    {
        // reverse loop so we leave it with first page
        p_page = dynamic_cast<QListWidget*>(widget(page));
        QString caption = tabText(page);
        const QStringList subList = m_brushLib.value(caption);
        if (!brushName.isEmpty()) for (int idx = 0 ; idx < subList.count() ; idx++)
        {
            if (subList.at(idx) == brushName) { p_item = p_page->item(idx); break; }
        }
    }
    // default one : we use the first tab page & the first item available:
    if (!p_item && p_page && p_page->count()) p_item = p_page->item(0);
    // Update GUI + load the brush (if any)
    if (p_item)
    {
        setCurrentWidget(p_page);
        p_page->setCurrentItem (p_item);
        itemClicked(p_item);
    }
}
