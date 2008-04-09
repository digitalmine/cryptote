// -*- C++ -*- generated by wxGlade 0.6.3 on Mon Mar  3 22:57:31 2008
// $Id$

#include <wx/wx.h>
// begin wxGlade: ::dependencies
#include <wx/statline.h>
// end wxGlade

#ifndef WCNTPROP_H
#define WCNTPROP_H

// begin wxGlade: ::extracode
// end wxGlade

class WContainerProperties : public wxDialog
{
public:
    // begin wxGlade: WContainerProperties::ids
    // end wxGlade

    WContainerProperties(class WCryptoTE* parent, int id=wxID_ANY, const wxString& title=wxEmptyString, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

protected:

    /// Reference to main window
    class WCryptoTE* wmain;

private:
    // begin wxGlade: WContainerProperties::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: WContainerProperties::attributes
    wxTextCtrl* textFilename;
    wxTextCtrl* textSize;
    wxTextCtrl* textSubFileNum;
    wxTextCtrl* textCTime;
    wxTextCtrl* textMTime;
    wxChoice* choiceCompression;
    wxChoice* choiceEncryption;
    wxCheckBox* checkboxRestoreView;
    wxTextCtrl* textAuthor;
    wxTextCtrl* textSubject;
    wxTextCtrl* textDescription;
    wxButton* buttonOK;
    wxButton* buttonCancel;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    virtual void OnButtonOK(wxCommandEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class

#endif // WCNTPROP_H
