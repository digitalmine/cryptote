/*******************************************************************************
 * src/cryptote/wcntprop.cpp
 *
 * Part of CryptoTE, see http://panthema.net/2007/cryptote
 *******************************************************************************
 * Copyright (C) 2008-2014 Timo Bingmann <tb@panthema.net>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 ******************************************************************************/

#include "wcntprop.h"
#include "wcryptote.h"

#include "common/tools.h"

// begin wxGlade: ::extracode
// end wxGlade

WContainerProperties::WContainerProperties(WCryptoTE* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long WXUNUSED(style))
    : wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxTHICK_FRAME),
      wmain(parent)
{
    // begin wxGlade: WContainerProperties::WContainerProperties
    textFilename = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    textSize = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    textSubFileNum = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    textCTime = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    textMTime = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    const wxString choiceCompression_choices[] = {
        _("None"),
        _("ZLib"),
        _("BZ2")
    };
    choiceCompression = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 3, choiceCompression_choices, 0);
    const wxString choiceEncryption_choices[] = {
        _("None (Don't Use)"),
        _("Serpent 256 keybits")
    };
    choiceEncryption = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 2, choiceEncryption_choices, 0);
    checkboxRestoreView = new wxCheckBox(this, wxID_ANY, _("Restore open subfiles and editor\npositions on reload."));
    textAuthor = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    textSubject = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    textDescription = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    buttonOK = new wxButton(this, wxID_OK, wxEmptyString);
    buttonCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade

    if (wmain->container_filename.IsOk())
    {
        textFilename->SetValue(wmain->container_filename.GetFullPath());
        textSize->SetValue(wxString::Format(_T("%u"), wmain->container.CountSubFile()));
    }
    else
    {
        textFilename->SetValue(_("<unsaved>"));
        textSize->SetValue(_("<unsaved>"));
    }

    textSubFileNum->SetValue(wxString::Format(_T("%u"), wmain->container.CountSubFile()));

    std::string timestr = wmain->container.GetGlobalEncryptedProperty("CTime");
    if (timestr.size() == sizeof(time_t)) {
        wxDateTime ctime(*(time_t*)timestr.data());
        textCTime->SetValue(ctime.Format(_("%c")));
    }

    timestr = wmain->container.GetGlobalEncryptedProperty("MTime");
    if (timestr.size() == sizeof(time_t)) {
        wxDateTime mtime(*(time_t*)timestr.data());
        textMTime->SetValue(mtime.Format(_("%c")));
    }

    unsigned long enccomp;
    if (strSTL2WX(wmain->container.GetGlobalEncryptedProperty("DefaultCompression")).ToULong(&enccomp)) {
        choiceCompression->SetSelection(enccomp);
    }
    else {
        choiceCompression->SetSelection(1);
    }

    if (strSTL2WX(wmain->container.GetGlobalEncryptedProperty("DefaultEncryption")).ToULong(&enccomp)) {
        choiceEncryption->SetSelection(enccomp);
    }
    else {
        choiceEncryption->SetSelection(1);
    }

    unsigned long restoreview;
    if (strSTL2WX(wmain->container.GetGlobalEncryptedProperty("RestoreView")).ToULong(&restoreview)) {
        checkboxRestoreView->SetValue(restoreview != 0);
    }
    else {
        checkboxRestoreView->SetValue(true);
    }

    textAuthor->SetValue(strSTL2WX(wmain->container.GetGlobalUnencryptedProperty("Author")));
    textSubject->SetValue(strSTL2WX(wmain->container.GetGlobalUnencryptedProperty("Subject")));
    textDescription->SetValue(strSTL2WX(wmain->container.GetGlobalUnencryptedProperty("Description")));
}

void WContainerProperties::set_properties()
{
    // begin wxGlade: WContainerProperties::set_properties
    SetTitle(_("Container Properties"));
    textFilename->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    textSize->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    textSubFileNum->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    textCTime->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    textMTime->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    choiceCompression->SetSelection(0);
    choiceEncryption->SetSelection(0);
    // end wxGlade
}

void WContainerProperties::do_layout()
{
    // begin wxGlade: WContainerProperties::do_layout
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    wxGridSizer* sizer4 = new wxGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* sizer3 = new wxFlexGridSizer(4, 2, 0, 0);
    wxFlexGridSizer* sizer2 = new wxFlexGridSizer(8, 2, 0, 0);
    wxStaticText* label1 = new wxStaticText(this, wxID_ANY, _("Filename:"));
    sizer2->Add(label1, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
    sizer2->Add(textFilename, 0, wxALL | wxEXPAND, 2);
    wxStaticText* label2 = new wxStaticText(this, wxID_ANY, _("Size:"));
    sizer2->Add(label2, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
    sizer2->Add(textSize, 0, wxALL | wxEXPAND, 2);
    wxStaticText* label3 = new wxStaticText(this, wxID_ANY, _("Contained SubFiles:"));
    sizer2->Add(label3, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
    sizer2->Add(textSubFileNum, 0, wxALL | wxEXPAND, 2);
    wxStaticText* label4 = new wxStaticText(this, wxID_ANY, _("Created:"));
    sizer2->Add(label4, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
    sizer2->Add(textCTime, 0, wxALL | wxEXPAND, 2);
    wxStaticText* label5 = new wxStaticText(this, wxID_ANY, _("Last Modified:"));
    sizer2->Add(label5, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
    sizer2->Add(textMTime, 0, wxALL | wxEXPAND, 2);
    wxStaticText* label6 = new wxStaticText(this, wxID_ANY, _("Default Compression:"));
    sizer2->Add(label6, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
    sizer2->Add(choiceCompression, 0, wxALL, 2);
    wxStaticText* label7 = new wxStaticText(this, wxID_ANY, _("Default Encryption:"));
    sizer2->Add(label7, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
    sizer2->Add(choiceEncryption, 0, wxALL, 2);
    sizer2->Add(4, 4, 0, wxALL | wxALIGN_RIGHT, 2);
    sizer2->Add(checkboxRestoreView, 0, wxALL, 2);
    sizer2->AddGrowableCol(1);
    sizer1->Add(sizer2, 0, wxALL | wxEXPAND, 8);
    wxStaticLine* staticline1 = new wxStaticLine(this, wxID_ANY);
    sizer1->Add(staticline1, 0, wxEXPAND, 0);
    wxStaticText* label9 = new wxStaticText(this, wxID_ANY, _("WARNING:"));
    sizer3->Add(label9, 0, wxALL | wxALIGN_RIGHT, 2);
    wxStaticText* label9b = new wxStaticText(this, wxID_ANY, _("The following properties are stored _unencrypted_.\nThey can be used to quickly determine the\ncontainer's contents e.g. in directory listings."));
    sizer3->Add(label9b, 0, wxALL, 2);
    wxStaticText* label10 = new wxStaticText(this, wxID_ANY, _("Author:"));
    sizer3->Add(label10, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
    sizer3->Add(textAuthor, 0, wxALL | wxEXPAND, 2);
    wxStaticText* label11 = new wxStaticText(this, wxID_ANY, _("Subject:"));
    sizer3->Add(label11, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
    sizer3->Add(textSubject, 0, wxALL | wxEXPAND, 2);
    wxStaticText* label12 = new wxStaticText(this, wxID_ANY, _("Description:"));
    sizer3->Add(label12, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 2);
    sizer3->Add(textDescription, 0, wxALL | wxEXPAND, 2);
    sizer3->AddGrowableRow(3);
    sizer3->AddGrowableCol(1);
    sizer1->Add(sizer3, 1, wxALL | wxEXPAND, 8);
    wxStaticLine* staticline2 = new wxStaticLine(this, wxID_ANY);
    sizer1->Add(staticline2, 0, wxEXPAND, 0);
    sizer4->Add(buttonOK, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 4);
    sizer4->Add(buttonCancel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 4);
    sizer1->Add(sizer4, 0, wxEXPAND, 0);
    SetSizer(sizer1);
    sizer1->Fit(this);
    Layout();
    Centre();
    // end wxGlade
}

BEGIN_EVENT_TABLE(WContainerProperties, wxDialog)
    // begin wxGlade: WContainerProperties::event_table
    EVT_BUTTON(wxID_OK, WContainerProperties::OnButtonOK)
    // end wxGlade
END_EVENT_TABLE();

void WContainerProperties::OnButtonOK(wxCommandEvent& WXUNUSED(event))
{
    wmain->container.SetGlobalUnencryptedProperty("Author", strWX2STL(textAuthor->GetValue()));
    wmain->container.SetGlobalUnencryptedProperty("Subject", strWX2STL(textSubject->GetValue()));
    wmain->container.SetGlobalUnencryptedProperty("Description", strWX2STL(textDescription->GetValue()));

    wxString enccomp = wxString::Format(_T("%u"), choiceCompression->GetSelection());
    wmain->container.SetGlobalEncryptedProperty("DefaultCompression", strWX2STL(enccomp));

    enccomp = wxString::Format(_T("%u"), choiceEncryption->GetSelection());
    wmain->container.SetGlobalEncryptedProperty("DefaultEncryption", strWX2STL(enccomp));

    wmain->container.SetGlobalEncryptedProperty("RestoreView", checkboxRestoreView->GetValue() ? "1" : "0");
    wmain->copt_restoreview = checkboxRestoreView->GetValue();

    EndModal(wxID_OK);
}

// wxGlade: add WContainerProperties event handlers

/******************************************************************************/
