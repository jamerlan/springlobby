/**
    This file is part of springsettings,
    Copyright (C) 2007
    Original work by Kloot
    cross-plattform/UI adaptation and currently maintained by koshi (Ren� Milk)
    visit http://springrts.com/phpbb/viewtopic.php?t=12104
    for more info/help

    SpringLobby is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    springsettings is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with springsettings.  If not, see <http://www.gnu.org/licenses/>.
**/

#include "tab_render_detail.h"
#include "se_utils.h"
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/event.h>
#include <wx/defs.h>
#include <wx/slider.h>

#include "ctrlconstants.h"

void tab_render_detail::initRendererSizer(wxFlexGridSizer* sizerL,wxFlexGridSizer* sizerR ) {
	const int extrema[] = {
		1024, 8192,   600, 3000,   20, 120,   100, 600,   0, 30,   0, 5,   100, 1000,   0, 20000,   0, 20000
	};

	for (int i = 0; i < ctrl_detail_sliders_size/2; i++) {
		ctrl_detail_sliders[i] = new wxSlider(
			this, RO_SLI[i].id, 0, extrema[i * 2],  extrema[(i * 2) + 1], WX_DEF_P, wxSize(180, -1), SLI_STYLE, WX_DEF_V		);
		//ctrl_detail_sliders[i]->SetTickFreq((extrema[(i*2)+1] - extrema[i * 2]) / 10  ,1);
		ctrl_detail_sliders[i]->SetToolTip(RO_SLI[i].tTip[0]);
		sizerL->Add(new wxStaticText(this, -1,  (RO_SLI[i].lbl)), 1,wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND);
		sizerL->Add(ctrl_detail_sliders[i], 0,wxALIGN_CENTER_VERTICAL|wxALL);
	}
	for (int i = ctrl_detail_sliders_size/2; i < ctrl_detail_sliders_size; i++) {
		ctrl_detail_sliders[i] = new wxSlider(
			this, RO_SLI[i].id, 0, extrema[i * 2],  extrema[(i * 2) + 1], WX_DEF_P, wxSize(180, -1), SLI_STYLE, WX_DEF_V);
		//ctrl_detail_sliders[i]->SetTickFreq((extrema[(i*2)+1] - extrema[i * 2]) / 10  ,1);
		ctrl_detail_sliders[i]->SetToolTip(RO_SLI[i].tTip[0]);
		sizerR->Add(new wxStaticText(this, -1,  (RO_SLI[i].lbl)), 1,wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND);
		sizerR->Add(ctrl_detail_sliders[i], 0,wxALIGN_CENTER_VERTICAL|wxALL);
	}
}

tab_render_detail::tab_render_detail(wxWindow *parent, wxWindowID id , const wxString &title , const wxPoint& pos , const wxSize& size, long style)
                : abstract_panel(parent, id , title , pos , size, style) {
	ctrl_detail_sliders = new wxSlider*[ctrl_detail_sliders_size];
	renderSizer = new wxGridSizer(2,15,5);
	parentSizer = new wxGridSizer(1,0,0);
	rendererSizerA = new wxFlexGridSizer(2,35,10);
	rendererSizerB = new wxFlexGridSizer(2,35,10);
	box = new wxStaticBoxSizer(wxVERTICAL ,this,_("Rendering detail levels"));
	rendererSizerA->AddGrowableCol(0);
	rendererSizerA->AddGrowableCol(1);
	rendererSizerB->AddGrowableCol(0);
	rendererSizerB->AddGrowableCol(1);
	initRendererSizer(rendererSizerA,rendererSizerB);
	rendererSizerA->Fit(this);
	rendererSizerA->SetSizeHints(this);
	rendererSizerB->Fit(this);
	rendererSizerB->SetSizeHints(this);

	renderSizer->Add(rendererSizerA,0,wxALIGN_LEFT|wxALL,5);
	renderSizer->Add(rendererSizerB,0,wxALIGN_RIGHT|wxALL,5);

	box->Add(renderSizer,0,wxALL,5);
	parentSizer->Add(box,0,wxALL,15);

	updateControls(UPDATE_ALL);
	SetSizer(parentSizer); // true --> delete old sizer if present

}

void tab_render_detail::updateControls(int /*what_to_update*/)
{
	for (int i = 0; i < ctrl_detail_sliders_size; i++) {
		ctrl_detail_sliders[i]->SetValue(intSettings[RO_SLI[i].key]);
	}

}

tab_render_detail::~tab_render_detail(void) {

}

BEGIN_EVENT_TABLE(tab_render_detail, abstract_panel)
	EVT_SLIDER(wxID_ANY,            tab_render_detail::OnSliderMove)
//	EVT_TEXT(wxID_ANY,              tab_render_detail::OnTextUpdate)
	//EVT_CHECKBOX(wxID_ANY,          tab_render_detail::OnCheckBoxTick)
//	EVT_RADIOBUTTON(wxID_ANY,       tab_render_detail::OnRadioButtonToggle)
//	EVT_IDLE(                       tab_render_detail::update)
END_EVENT_TABLE()
