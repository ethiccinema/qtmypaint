/* brushlib - The MyPaint Brush Library (demonstration project)
 * Copyright (C) 2013 POINTCARRE SARL / Sebastien Leon email: sleon at pointcarre.com
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 */

#include "PuMPBrushes.h"

#include <QDir>
#include <QListWidget>

#define BRUSH_CONTENT_EXT ".myb"
#define BRUSH_PREVIEW_EXT "_prev.png"
#define ICON_SZ           64

// utility function:
QStringList GetBrushes(const QString& path)
{
  QStringList bList;
  QFileInfoList lst = QDir(path).entryInfoList ( QStringList()<<(QString("*")+BRUSH_CONTENT_EXT), QDir::Files | QDir::Readable, QDir::Name );
  // We validate only the fact that we found the brush file with the preview
  // (we assume that brush file & preview is correct and do not try here to load them)
  for (int n = 0 ; n<lst.count() ; n++)
  {
    QString previewPath (lst[n].absoluteFilePath());
    previewPath.replace(BRUSH_CONTENT_EXT, BRUSH_PREVIEW_EXT); // little chance for the filename to contain .myb in the middle of its name
    if (QFileInfo(previewPath).exists())
    {
      // content + preview file found : we add the name (without extension) to the list !
      QString name = lst[n].fileName();
      name.chop( QString(BRUSH_CONTENT_EXT).length() );
      bList << name;
    }
  }
  return bList;
}

PuMPBrushes::PuMPBrushes( const QString& brushLibPath, QWidget* p_parent ):
  QTabWidget   (p_parent),
  m_brushesPath(brushLibPath)
{
  // First, we parse the brushLib directory to fill m_brushLib
  QDir bDir(brushLibPath);
  QFileInfoList lst = bDir.entryInfoList ( QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name );
  for (int n = 0 ; n<lst.count() ; n++)
  {
    QStringList brushes = GetBrushes(lst[n].absoluteFilePath());
    if (brushes.isEmpty()) continue; // invalid dir entry, let's try the next one
    m_brushLib.insert(lst[n].fileName(), brushes);
  }
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
      QIcon preview(m_brushesPath + QDir::separator() + caption + QDir::separator() + name + BRUSH_PREVIEW_EXT);
      QListWidgetItem* p_item = new QListWidgetItem(preview, QString(), p_lWdgt, n); // no need to show the name as it is already visible in preview
      //p_item->setIconSize(QSize(128,128));
      p_item->setToolTip(QString("%1 in %2 library").arg(name).arg(caption));
    }
  }
  // for now, no brush is selected. Expecting some order from owner...
}

void PuMPBrushes::itemClicked(QListWidgetItem *p_item)
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
    QFile f( m_brushesPath + QDir::separator() + caption + QDir::separator() + subList[p_item->type()] + BRUSH_CONTENT_EXT );
    if (f.open( QIODevice::ReadOnly ))
    {
      QByteArray content = f.readAll();
      content.append( (char)0 );
      emit BrushSelected(content); // Read the whole file and broadcast is as a char* buffer
    }
  }
}

void PuMPBrushes::SelectDefaultBrush ()
{
  if (!IsValid()) return;
  // we use the first tab page & the first item available:
  QListWidget* p_lWdgt = dynamic_cast<QListWidget*>(widget(0));
  if (p_lWdgt && p_lWdgt->count())
  {
    QListWidgetItem * item = p_lWdgt->item(0);
    p_lWdgt->setCurrentItem (item);
    itemClicked(item);
  }
}