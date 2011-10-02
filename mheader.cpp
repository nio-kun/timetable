/*
 *   mheader.cpp
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

#include <mheader.h>
#include <QMessageBox>

HMultiHeader::HMultiHeader(QWidget *parent, Qt::Orientation orientation1) : QHeaderView(orientation1 ,parent) {
 lockPaint=false;
 setHighlightSections (true);    
 setClickable(true);
 spans=0;
 level=1;
 level_sizes.resize(level+1);
 orientation=orientation1;
}

HMultiHeader::~HMultiHeader() {
 freeSpans(spans);
}

int HMultiHeader::paintSubSections(QPainter *painter,QStyleOptionHeader &opt,int logicalIndex,colspan *root,int baseX, int baseY) const {
 if (!root) return 0;
 int draws=0;
 QRect saved_rect=opt.rect;
 
 if (orientation==Qt::Horizontal){
    opt.rect.setY(saved_rect.y()+saved_rect.height());
 }else{
    opt.rect.setX(saved_rect.x()+saved_rect.width());
 }

 while(root) {
    if (logicalIndex>=root->start && logicalIndex<=root->stop) {
     if (!draws) draws=1;
     int x=baseX;
     int y=baseY;
     int w=0;
     
     for (int i=logicalIndex-1; i>=root->start; i--) {
      x-=sectionSize(i);
      y-=sectionSize(i);
     }
     
     for (int i=root->start; i<=root->stop;i++) {
      w+=sectionSize(i);
     }
     if (orientation==Qt::Horizontal){
        opt.rect.setX(x);
        opt.rect.setWidth(w);
        opt.rect.setHeight(saved_rect.height());
     }else{
         opt.rect.setY(y);
         opt.rect.setHeight(w);
         opt.rect.setWidth(saved_rect.width());
     }
     opt.text=root->text;
     style()->drawControl(QStyle::CE_Header, &opt, painter, this);
     draws+=paintSubSections(painter,opt,logicalIndex,root->sub,baseX,baseY); //paint sub headers
     opt.rect=saved_rect; //restore rect
    }
    root=root->next;
 }
 
 return draws; //reurns how much sub headers were drawn
 
}

void HMultiHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const {
 if (!rect.isValid()) return;
 
 QRect newrect=rect;
 
 if (spans) {
  colspan *root=setRect(rect,newrect); //recalculate section rect
  if (root) {
   int baseHeight=rect.height()/(level+1); //adjust height for single row
   int baseWidth=rect.width()/(level+1); //adjust width for single column
     
   QStyleOptionHeader opt;
   initStyleOption(&opt);
  
   opt.rect=newrect;
   opt.section=logicalIndex;
   opt.position = QStyleOptionHeader::OnlyOneSection;
   opt.orientation = orientation;
   opt.textAlignment = Qt::AlignCenter;

   opt.text=root->text;
   if (orientation==Qt::Horizontal){
       opt.rect.setHeight(baseHeight);
   }else{
       opt.rect.setWidth(baseWidth);
//       opt.rect.setWidth(style()->sizeFromContents(QStyle::CT_HeaderSection, &opt, QSize(), this).rwidth());
   }
   style()->drawControl(QStyle::CE_Header, &opt, painter, this); //draw a top level span first
   
   int adrawed=paintSubSections(painter,opt,logicalIndex,root->sub,rect.x(),rect.y()); //draw sub spans

   newrect=rect;

   int aY=rect.y()+baseHeight+adrawed*baseHeight; //calculate new Y position for the default header's data drawing
   int aX=rect.x()+baseWidth+adrawed*baseWidth; //calculate new X position for the default header's data drawing
   if (orientation==Qt::Horizontal){
       newrect.setY(aY); //adjust Y position for the default header's data drawing
       newrect.setHeight(rect.y()+rect.height()-aY); //adjust height for the default header's data drawing
   }else{
       newrect.setX(aX); //adjust X position for the default header's data drawing
       newrect.setWidth(rect.x()+rect.width()-aX); //adjust width for the default header's data drawing
   }
  }
 }
 
 QHeaderView::paintSection(painter,newrect,logicalIndex);

}

QSize HMultiHeader::sizeHint() const
{
   QSize size = QHeaderView::sizeHint();
   if (spans) {
       if (orientation==Qt::Horizontal){
           size.rheight() *= (level+1);
       }else{
           size.rwidth() *= (level+1);
       }
   }
   return size;
}

void HMultiHeader::paintEvent ( QPaintEvent * event ) {
 if (!spans) {
  QHeaderView::paintEvent(event);
  return;
 }
 
 while(lockPaint); //mutex emulation - ugly way to avoid recursion
 
 QRect newrect;
 setRect(event->rect(),newrect);
 if (event->rect()!=newrect) {
     lockPaint=true;
     setDirtyRegion(newrect); //adjust rect for spanned headers
     QHeaderView::paintEvent(event); //More slow painting when do not call to this function
     lockPaint=false;
     return;
 }

 QHeaderView::paintEvent(event);

}

colspan * HMultiHeader::setRect(const QRect &rect,QRect &newrect) const {
 newrect=rect;

 int start, end;
 if (orientation==Qt::Horizontal){
    start=visualIndexAt(newrect.left());
    end=visualIndexAt(newrect.right());
 }else{
     start=visualIndexAt(newrect.top());
     end=visualIndexAt(newrect.bottom());
 }
 
 int w=newrect.width();
 int h=newrect.height();
 int x=newrect.x();
 int y=newrect.y();

 colspan *si;

 si=getTopSpan(start);
 if (si) {
  for (int i=start-1; i>=si->start; i--) {
     x-=sectionSize(i);
     y-=sectionSize(i);
     w+=sectionSize(i);
     h+=sectionSize(i);
  }
 }
 
 if (start!=end) si=getTopSpan(end);
 if (si) {
   for (int i=end+1; i<=si->stop; i++) {
     w+=sectionSize(i);
     h+=sectionSize(i);
   }
 }

//extend section rect
 if (orientation==Qt::Horizontal){
    newrect.setX(x);
    newrect.setWidth(w);
 }else{
     newrect.setY(y);
     newrect.setHeight(h);
 }
 //newrect.setHeight(100);

 return si; 
}

int HMultiHeader::findMinSize(colspan *root,int minimum,int li,bool atop) const {
 if (!root) return minimum;

 if (!atop) {
  minimum=findMinSize(root->next,minimum,li);
 }

 if (li>=root->start && li<=root->stop) {  
  minimum=findMinSize(root->sub,minimum,li);  
  int w=0;
  for (int i=root->start;i<=root->stop; i++) if (!isSectionHidden(i)) w++;
  if (w) w=root->sizeHint/w;
  if (w>minimum) minimum=w;
 }
 
 return minimum;
 
}

QSize HMultiHeader::sectionSizeFromContents ( int logicalIndex ) const {
 
 QSize size=QHeaderView::sectionSizeFromContents(logicalIndex); 
 //size.rwidth()=findMinSize(getTopSpan(logicalIndex),size.width(),logicalIndex,true);
 int s=0;
 for (int i=1; i<=level;i++){
     //s+=level_sizes.at(i);
     if (s<level_sizes.at(i)) s=level_sizes.at(i);
 }
 size.rwidth()=s;
 //size.rwidth()=200;
 //size.rheight()=100;
 return size;
}

void HMultiHeader::spanSizeHint(colspan *c) {
 if (!c) return;
 QStyleOptionHeader opt;
 initStyleOption(&opt);
 opt.text=c->text+"  ";
 QSize size = style()->sizeFromContents(QStyle::CT_HeaderSection, &opt, QSize(), this);
 c->sizeHint=size.rwidth();
 //c->sizeHint=200;
}

bool HMultiHeader::spanCols(const QString &text,int start,int stop,colspan *&root,int &maxlevel) {
 if (root) {
  if (stop==root->stop && start==root->start) {//equal, just replace text and adjust sizeHint
   root->text=text;
   spanSizeHint(root);
   return true;
  }
  
  if (
      (start>=root->start && start<=root->stop && stop>root->stop) || 
      (start<root->start && stop>=root->start && stop<=root->stop)
     )  return false;//overlaps
  
  if (start>root->stop || stop<root->start) {//next span
    return spanCols(text,start,stop,root->next,maxlevel);
  }     
  
  if (start>=root->start && stop<=root->stop) {//sub span
    maxlevel++;
    return spanCols(text,start,stop,root->sub,maxlevel);
  } 
 }
 
//set span data if root==NULL
 colspan *tmp=new colspan(text,start,stop);
 spanSizeHint(tmp);
 if (maxlevel>level) {
     level_sizes.resize(maxlevel+1);
 }
 if (tmp->sizeHint > level_sizes.at(maxlevel)) level_sizes[maxlevel]=tmp->sizeHint;
 root=tmp;
 
 return true;
 
}

bool HMultiHeader::spanCols(const QString &text,int start,int stop) {
 
 if (start<0 || start>=stop) return false;
 if (stop>=count()) return false;

 int maxlevel=1;
 bool res=spanCols(text,start,stop,spans,maxlevel);
 if (maxlevel>level) {
     level=maxlevel;
//     QMessageBox::information(0, "Kanji",QString::number(maxlevel), 0,0,0);
 }
 return res;
}

void HMultiHeader::freeSpans(colspan *&root) {
 if (!root) return;
 freeSpans(root->next);
 freeSpans(root->sub);
 delete root;
 root=0;
}

colspan *HMultiHeader::getTopSpan(int idx) const {
 colspan *root=spans;  
 while (root) { 
   if (root->start<=idx && root->stop>=idx) break; //found span for idx
   root=root->next;
 }
 return root;
}
