/*
 * This file is part of the xTuple ERP: PostBooks Edition, a free and
 * open source Enterprise Resource Planning software suite,
 * Copyright (c) 1999-2014 by OpenMFG LLC, d/b/a xTuple.
 * It is licensed to you under the Common Public Attribution License
 * version 1.0, the full text of which (including xTuple-specific Exhibits)
 * is available at www.xtuple.com/CPAL.  By using this software, you agree
 * to be bound by its terms.
 */

#include "lotSerial.h"
#include "lotSerialRegistration.h"

#include <QSqlError>
#include <QVariant>
#include <QMessageBox>

#include <openreports.h>
#include <comments.h>
#include <errorReporter.h>

lotSerial::lotSerial(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : XDialog(parent, name, modal, fl)
{
    setupUi(this);

    _print = _buttonBox->addButton(tr("Print Label"),QDialogButtonBox::ActionRole);

    connect(_buttonBox, SIGNAL(accepted()), this, SLOT(sSave()));
    connect(_lotSerial, SIGNAL(valid(bool)), this, SLOT(populate()));
    connect(_notes, SIGNAL(textChanged()), this, SLOT(sChanged()));
    connect(_deleteReg,  SIGNAL(clicked()), this, SLOT(sDeleteReg()));
    connect(_editReg,    SIGNAL(clicked()), this, SLOT(sEditReg()));
    connect(_newReg,     SIGNAL(clicked()), this, SLOT(sNewReg()));
    connect(_print, SIGNAL(clicked()), this, SLOT(sPrint()));
    
    _charass->setType("LS");
    _charass->findChild<QPushButton*>("_newCharacteristic")->setEnabled(false);
    
    _reg->addColumn(tr("Number")      ,        _orderColumn,  Qt::AlignLeft, true, "lsreg_number" );
    _reg->addColumn(tr("Account#"),            _itemColumn,  Qt::AlignLeft, true, "crmacct_number" );
    _reg->addColumn(tr("Name"        ),	      -1,   Qt::AlignLeft, true, "crmacct_name" );
    _reg->addColumn(tr("First Name"  ),        80,  Qt::AlignLeft, true, "cntct_first_name" );
    _reg->addColumn(tr("Last Name"   ),        80,  Qt::AlignLeft, true, "cntct_last_name" );
    _reg->addColumn(tr("Phone"       ),        80,  Qt::AlignLeft, true, "cntct_phone" );
  
    _changed=false;
}

lotSerial::~lotSerial()
{
    // no need to delete child widgets, Qt does it all for us
}

void lotSerial::languageChange()
{
    retranslateUi(this);
}

enum SetResponse lotSerial::set(const ParameterList &pParams)
{
  QVariant param;
  bool     valid;

  param = pParams.value("item_id", &valid);
  if (valid)
  {
    _item->setId(param.toInt());
  }
  
  param = pParams.value("ls_id", &valid);
  if (valid)
  {
    _lotSerial->setId(param.toInt());
  }
  
  return NoError;
}

void lotSerial::populate()
{
  XSqlQuery lotpopulate;
  if (_changed)
  {
    if (QMessageBox::question(this, tr("Save changes?"),
                              tr("<p>Notes were changed without saving. "
                                 "If you continue your changes will be lost. "
                                 "Would you like an opportunity to save your changes first?"),
                              QMessageBox::Yes | QMessageBox::Default,
                              QMessageBox::No) == QMessageBox::Yes)
    {
      disconnect(_lotSerial, SIGNAL(valid(bool)), this, SLOT(populate()));
      _item->setId(_itemidCache);
      _lotSerial->setId(_lsidCache);
      connect(_lotSerial, SIGNAL(valid(bool)), this, SLOT(populate()));
      return;
    }
  }

  lotpopulate.prepare( "SELECT ls_item_id,ls_notes "
             "FROM ls "
             "WHERE (ls_id=:ls_id );" );
  lotpopulate.bindValue(":ls_id", _lotSerial->id());
  lotpopulate.exec();
  if (lotpopulate.first())
  {
    _lsidCache=_lotSerial->id();
    _documents->setId(_lsidCache);
    _charass->setId(_lsidCache);
    if (_item->id() == -1)
      _item->setId(lotpopulate.value("ls_item_id").toInt());
    _itemidCache=_item->id();
    _notes->setText(lotpopulate.value("ls_notes").toString());
    _changed=false;
  }
  else if (ErrorReporter::error(QtCriticalMsg, this, tr("Error Retrieving Lot/Serial Information"),
                                lotpopulate, __FILE__, __LINE__))
  {
    return;
  }
  _charass->findChild<QPushButton*>("_newCharacteristic")->setEnabled(_lotSerial->isValid());
  sFillList();
}

void lotSerial::sSave()
{
  XSqlQuery lotSave;
  lotSave.prepare("UPDATE ls SET"
            " ls_notes=:notes "
            "WHERE (ls_id=:ls_id);");
  lotSave.bindValue(":notes",_notes->toPlainText());
  lotSave.bindValue(":ls_id", _lotSerial->id());
  lotSave.exec();
  if (ErrorReporter::error(QtCriticalMsg, this, tr("Error Saving Lot/Serial Information"),
                                lotSave, __FILE__, __LINE__))
  {
    return;
  }
  _notes->clear();
  _changed=false;
  _item->setId(-1);
  _charass->setId(-1);
}

void lotSerial::sChanged()
{
  if (_notes->toPlainText().length() > 0)
    _changed=true;
}

void lotSerial::sNewReg()
{
  ParameterList params;
  params.append("mode", "new");
  params.append("item_id", _item->id());
  params.append("ls_id", _lotSerial->id());

  lotSerialRegistration newdlg(this, "", true);
  newdlg.set(params);
  
  newdlg.exec();
  sFillList();
}

void lotSerial::sEditReg()
{
  ParameterList params;
  params.append("mode", "edit");
  params.append("lsreg_id", _reg->id());

  lotSerialRegistration newdlg(this, "", true);
  newdlg.set(params);
  
  newdlg.exec();
  sFillList();
}

void lotSerial::sDeleteReg()
{
  XSqlQuery lotDeleteReg;
  lotDeleteReg.prepare( "DELETE FROM lsreg "
             "WHERE (lsreg_id=:lsreg_id);"
             "DELETE FROM charass "
             "WHERE ((charass_target_type='LSR') "
             "AND (charass_target_id=:lsreg_id))" );
  lotDeleteReg.bindValue(":lsreg_id", _reg->id());
  lotDeleteReg.exec();
  if (ErrorReporter::error(QtCriticalMsg, this, tr("Error Deleting Lot/Serial Information"),
                                lotDeleteReg, __FILE__, __LINE__))
  {
    return;
  }

  sFillList();
}


void lotSerial::sFillList()
{
  _charass->setId(_lotSerial->id());
  XSqlQuery lotFillList;
  lotFillList.prepare( "SELECT lsreg_id,lsreg_number,crmacct_number,crmacct_name,"
             "  cntct_first_name,cntct_last_name,cntct_phone "
             "FROM lsreg "
             "  LEFT OUTER JOIN crmacct ON (lsreg_crmacct_id=crmacct_id), "
             "  cntct "
             "WHERE ((lsreg_cntct_id=cntct_id) "
             "AND (lsreg_ls_id=:ls_id));");
  lotFillList.bindValue(":ls_id", _lotSerial->id());
  lotFillList.exec();
  _reg->clear();
  _reg->populate(lotFillList);
  if (ErrorReporter::error(QtCriticalMsg, this, tr("Error Retrieving Lot/Serial Information"),
                                lotFillList, __FILE__, __LINE__))
  {
    return;
  }
}

void lotSerial::sPrint()
{
  XSqlQuery lotPrint;
  QString lot(tr("Lot#:"));
  QString serial(tr("Serial#:"));
  ParameterList params;
  params.append("ls_id", _lotSerial->id());

  // Try to infer whether this requires a lot or serial number label
  lotPrint.prepare("SELECT DISTINCT itemsite_controlmethod "
            "FROM itemsite "
            "WHERE ((itemsite_item_id=:item_id)"
            " AND (itemsite_controlmethod IN ('L','S')));");
  lotPrint.bindValue(":item_id", _item->id());
  lotPrint.exec();
  if (lotPrint.size() == 1) {
    lotPrint.first();
    if (lotPrint.value("itemsite_controlmethod").toString() == "L")
      params.append("label", lot);
    else
      params.append("label", serial);
  }
  else if (ErrorReporter::error(QtCriticalMsg, this, tr("Error Retrieving Lot/Serial Information"),
                                lotPrint, __FILE__, __LINE__))
  {
    return;
  }
  else {
    QString msg(tr("Is this a Lot or a Serial number?"));
    QMessageBox msgbox;
    msgbox.setText(msg);
    msgbox.addButton(tr("Lot"),QMessageBox::AcceptRole);
    msgbox.addButton(tr("Serial"),QMessageBox::RejectRole);
    if (msgbox.exec() == QDialog::Accepted)
      params.append("label", serial);
    else
      params.append("label", lot);
  }

  orReport report("LotSerialLabel",params);
  if (report.isValid())
    report.print();
  else
    report.reportError(this);
}
