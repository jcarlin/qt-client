/*
 * This file is part of the xTuple ERP: PostBooks Edition, a free and
 * open source Enterprise Resource Planning software suite,
 * Copyright (c) 1999-2017 by OpenMFG LLC, d/b/a xTuple.
 * It is licensed to you under the Common Public Attribution License
 * version 1.0, the full text of which (including xTuple-specific Exhibits)
 * is available at www.xtuple.com/CPAL.  By using this software, you agree
 * to be bound by its terms.
 */

#include "locationcluster.h"

#include <QMessageBox>
#include <QSqlError>

#include "xsqlquery.h"
#include "xtreewidget.h"

LocationList::LocationList(QWidget* pParent, Qt::WindowFlags flags)
  : VirtualList(pParent, flags)
{
  setObjectName("locationList");

  _listTab->headerItem()->setText(0, tr("Location Name"));
  _listTab->headerItem()->setText(1, tr("Description"));
}

LocationSearch::LocationSearch(QWidget* pParent, Qt::WindowFlags flags)
  : VirtualSearch(pParent, flags)
{
  setObjectName("locationSearch");

  _listTab->headerItem()->setText(0, tr("Location Name"));
  _listTab->headerItem()->setText(1, tr("Description"));
}

LocationCluster::LocationCluster(QWidget* pParent, const char* pName)
  : VirtualCluster(pParent, pName)
{
  LocationLineEdit* lle = new LocationLineEdit(this, pName);
  addNumberWidget(lle);
}

LocationLineEdit::LocationLineEdit(QWidget* pParent, const char* pName) :
    VirtualClusterLineEdit(pParent, "location", "location_id", "location_formatname", 0, "location_descrip", 0, pName, "location_active")
{
  /*_query = QString("SELECT location_id, location_formatname " 
                   "FROM location "
                   "WHERE TRUE ");
                   /*"WHERE ( (location_warehous_id=35) "
                   "  AND (NOT location_restrict) "
                   "  AND (location_active) ) "
                   "UNION SELECT location_id, location_formatname "
                   "FROM location, locitem "
                   "WHERE ( (location_warehous_id=35) "
                   "  AND (location_restrict) "
                   "  AND (location_active) "
                   "  AND (locitem_location_id=location_id) "
                   "  AND (locitem_item_id=:item_id) ) "
                   "ORDER BY locationname;");*/

  setEditPriv("MaintainLocations");
  setNewPriv("MaintainLocations");
  setViewPriv("ViewLocations");
}

void LocationLineEdit::setId(const int pLocationId)
{
  XSqlQuery query;
  query.prepare("SELECT location_formatname AS number, "
                " location_formatname AS name, "
                " location_descrip AS description "
                " FROM location "
                " WHERE location_id=:id");
  query.bindValue(":id", pLocationId);
  query.exec();
  setStrikeOut(!query.size());
  if(query.first())
  {
    _id = pLocationId;
    _valid = true;
    _name = query.value("name").toString();
    _description = query.value("description").toString();
    setText(_name);
  }
  else
  {
    _id = -1;
    _valid = false;
    _name = QString();
    _description = QString();
  }

  emit newId(_id);
  emit valid(_valid);
  emit parsed();
  _parsed = true;
}


