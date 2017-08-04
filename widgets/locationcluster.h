/*
 * This file is part of the xTuple ERP: PostBooks Edition, a free and
 * open source Enterprise Resource Planning software suite,
 * Copyright (c) 1999-2017 by OpenMFG LLC, d/b/a xTuple.
 * It is licensed to you under the Common Public Attribution License
 * version 1.0, the full text of which (including xTuple-specific Exhibits)
 * is available at www.xtuple.com/CPAL.  By using this software, you agree
 * to be bound by its terms.
 */

#ifndef _locationCluster_h
#define _locationCluster_h

#include "virtualCluster.h"

class LocationCluster;

class XTUPLEWIDGETS_EXPORT LocationLineEdit : public VirtualClusterLineEdit
{
  Q_OBJECT

  friend class LocationCluster;

  inline int itemId() { return _itemid; };
  inline int whId() { return _whid; };

  public:
    LocationLineEdit(QWidget*, const char* = 0);

  public slots:
    void setItemId(int);
    void setWhId(int);

  protected:
    void buildExtraClause();

  private:
    int _itemid;
    int _whid;
};

class XTUPLEWIDGETS_EXPORT LocationCluster : public VirtualCluster
{
  Q_OBJECT
  
  friend class LocationLineEdit;

  public:
    LocationCluster(QWidget*, const char* = 0);

    inline int itemId() { return static_cast<LocationLineEdit*>(_number)->itemId(); }
    inline int whId() { return static_cast<LocationLineEdit*>(_number)->whId(); }

  public slots:
    void setItemId(int);
    void setWhId(int);
};

#endif
