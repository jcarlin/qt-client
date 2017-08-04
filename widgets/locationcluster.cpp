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

LocationCluster::LocationCluster(QWidget* pParent, const char* pName)
  : VirtualCluster(pParent, pName)
{
  addNumberWidget(new LocationLineEdit(this, pName));
}

void LocationCluster::setItemId(int pItemId)
{
  static_cast<LocationLineEdit*>(_number)->setItemId(pItemId);
}

void LocationCluster::setWhId(int pWhId)
{
  static_cast<LocationLineEdit*>(_number)->setWhId(pWhId);
}

LocationLineEdit::LocationLineEdit(QWidget* pParent, const char* pName) :
    VirtualClusterLineEdit(pParent, "location", "location_id", "number", 0, "description", 0, pName)
{
  setEditPriv("MaintainLocations");
  setNewPriv("MaintainLocations");
  setViewPriv("ViewLocations");

  setTitles(tr("Location"), tr("Locations"));

  _itemid = 0;
  _whid = 0;

  _query = "SELECT * "
           "FROM ( "
           "  SELECT location_id, location_formatname AS number, location_descrip AS description, NULL AS locitem_item_id, location_warehous_id "
           "  FROM location "
           "  WHERE NOT location_restrict "
           "    AND location_active "
           "UNION "
           "SELECT location_id, location_formatname, location_descrip, locitem_item_id, location_warehous_id "
           "FROM location, locitem "
           "WHERE location_restrict "
           "  AND location_active "
           "  AND locitem_location_id=location_id "
           ") AS query "
           "WHERE true ";
}

void LocationLineEdit::setItemId(int pItemId)
{
  if (pItemId > 0)
  {
    _itemid = pItemId;
    buildExtraClause();
  }
}

void LocationLineEdit::setWhId(int pWhId)
{
  if (pWhId > 0)
  {
    _whid = pWhId;
    buildExtraClause();
  }
}

void LocationLineEdit::buildExtraClause()
{
  QString extraClause = _extraClause;
  
  if (!extraClause.isEmpty())
    extraClause.append(" AND ");

  if (_itemid > 0)
    extraClause.append(QString(" CASE WHEN locitem_item_id > 0 THEN locitem_item_id = %1 ELSE TRUE END ").arg(_itemid));

  if (_whid > 0)
  {
    if (!extraClause.isEmpty())
      extraClause.append(" AND ");
    extraClause.append(QString(" location_warehous_id = %1 ").arg(_whid));
  }

  VirtualClusterLineEdit::setExtraClause(extraClause);
}




