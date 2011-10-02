/*
 *   mheader.h
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Copyright 2010  Vitaly Bodzhgua
 */

#ifndef _MHEADER_H_
#define _MHEADER_H_

#include <QtGui>

class HMultiHeader;

class colspan {
 friend class HMultiHeader;
 protected:
  colspan(const QString &atext="",int astart=0,int astop=0) 
    {text=atext;start=astart,stop=astop;sizeHint=0;next=sub=0;}
  int start;
  int stop;
  int sizeHint;
  QString text;
  colspan *next;
  colspan *sub;
};

class HMultiHeader : public  QHeaderView {
 Q_OBJECT
public:

 HMultiHeader(QWidget *parent=0, Qt::Orientation orientation1=Qt::Horizontal);
 ~HMultiHeader();
 virtual QSize sizeHint () const;
 bool spanCols(const QString &text,int start,int stop);

protected:
 virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
 virtual void paintEvent ( QPaintEvent * event );
 int findMinSize(colspan *root,int minimum,int li,bool atop=false) const;
 virtual QSize sectionSizeFromContents ( int logicalIndex ) const;
 
 void spanSizeHint(colspan *c);
 bool spanCols(const QString &text,int start,int stop,colspan *&root,int &maxlevel);
 virtual int paintSubSections(QPainter *painter,QStyleOptionHeader &opt,int logicalIndex,colspan *root,int baseX, int baseY) const;
 
 colspan * setRect(const QRect &rect,QRect &newrect) const;
 colspan * getTopSpan(int idx) const;
 void freeSpans(colspan *&root);
 
 bool lockPaint;
 
 int level;
 QVector<int> level_sizes;
 
 mutable colspan *spans;

 Qt::Orientation orientation;
 
};

#endif
