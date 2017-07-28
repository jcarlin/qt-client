/*
 * This file is part of the xTuple ERP: PostBooks Edition, a free and
 * open source Enterprise Resource Planning software suite,
 * Copyright (c) 1999-2014 by OpenMFG LLC, d/b/a xTuple.
 * It is licensed to you under the Common Public Attribution License
 * version 1.0, the full text of which (including xTuple-specific Exhibits)
 * is available at www.xtuple.com/CPAL.  By using this software, you agree
 * to be bound by its terms.
 */

#ifndef _locationCluster_h
#define _locationCluster_h

#include "virtualCluster.h"

class LocationCluster;

class XTUPLEWIDGETS_EXPORT  LocationList : public VirtualList
{
  Q_OBJECT

  friend class LocationLineEdit;

  public:
    LocationList(QWidget*, Qt::WindowFlags = 0);

  private:
    LocationCluster* _parent;
};

class XTUPLEWIDGETS_EXPORT  LocationSearch : public VirtualSearch
{
  Q_OBJECT

  friend class LocationLineEdit;

  public:
    LocationSearch(QWidget*, Qt::WindowFlags = 0);

  private:
    LocationCluster* _parent;
};

class XTUPLEWIDGETS_EXPORT LocationLineEdit : public VirtualClusterLineEdit
{
  Q_OBJECT

  friend class LocationCluster;

  public:
    LocationLineEdit(QWidget*, const char* = 0);

  public slots:
    virtual void setId(const int);
    
  private:
	  int	_itemid;
	  bool	_strict;
};

class XTUPLEWIDGETS_EXPORT LocationCluster : public VirtualCluster
{
  Q_OBJECT
  
  friend class LocationLineEdit;

  public:
    LocationCluster(QWidget*, const char* = 0);

};

#endif
