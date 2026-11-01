/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "ui/screens/install/uiinstall.h"

#include "contentcatalog.h"
#include "contentnet.h"
#include "ui/rml/rmlview.h"


UIInstallPresenterClass::UIInstallPresenterClass(void)
{
	Update_Sizes();
}


void UIInstallPresenterClass::Update_Sizes(void)
{
	BaseSize = Content_Size_Text(Content_Base_Bytes());
	MovieSize = Content_Size_Text(Content_Movies_Marginal(Firestorm));
	FirestormSize = Content_Size_Text(Content_Firestorm_Marginal(Movies));
	TotalSize = Content_Size_Text(Content_Download_Bytes(Movies, Firestorm));
	Notice = "These files are Electronic Arts' freeware Tiberian Sun release. They are not covered by the siliconsun license.\nThey are downloaded from ";
	Notice += Content_Download_Host();
	Notice += ".";
}


void UIInstallPresenterClass::Execute(UIIntent const & intent)
{
	if (intent.Name == "movies") {
		Movies = intent.Value != 0;
		Update_Sizes();
	} else if (intent.Name == "firestorm") {
		Firestorm = intent.Value != 0;
		Update_Sizes();
	} else if (intent.Name == "download" && !Busy) {
		HasError = false;
		Error.clear();
		Transfer.Start_Download(Movies, Firestorm);
		Busy = Transfer.Active();
		Status = Transfer.Status();
		Percent = 0;
		if (!Busy) {
			Error = Transfer.Error();
			HasError = !Error.empty();
		}
	} else if (intent.Name == "folder" && !Busy) {
		std::string folder;
		if (!Content_Pick_Folder(folder)) {
			return;
		}
		HasError = false;
		Error.clear();
		Transfer.Start_Copy(folder, Movies, Firestorm);
		Busy = Transfer.Active();
		Status = Transfer.Status();
		Percent = 0;
		if (!Busy) {
			Error = Transfer.Error();
			HasError = !Error.empty();
		}
	} else if (intent.Name == "cancel") {
		Transfer.Cancel();
		Busy = false;
		Status.clear();
	} else if (intent.Name == "quit") {
		Transfer.Cancel();
		Result = UI_RESULT_CANCELLED;
	}
}


void UIInstallPresenterClass::Refresh(void)
{
}


namespace
{

class UIInstallViewClass : public UIRmlViewClass
{
	public:
		explicit UIInstallViewClass(UIInstallPresenterClass & presenter) :
			UIRmlViewClass(presenter, "install.rml", "install"),
			Data(presenter)
		{
		}

		virtual void Sync(void) override
		{
			Model.DirtyVariable("notice");
			Model.DirtyVariable("basesize");
			Model.DirtyVariable("movies");
			Model.DirtyVariable("moviesize");
			Model.DirtyVariable("firestorm");
			Model.DirtyVariable("firestormsize");
			Model.DirtyVariable("totalsize");
			Model.DirtyVariable("busy");
			Model.DirtyVariable("status");
			Model.DirtyVariable("percent");
			Model.DirtyVariable("error");
			Model.DirtyVariable("haserror");
		}

	protected:
		virtual bool Bind(Rml::DataModelConstructor & model) override
		{
			return(model.Bind("notice", &Data.Notice)
				&& model.Bind("basesize", &Data.BaseSize)
				&& model.Bind("movies", &Data.Movies)
				&& model.Bind("moviesize", &Data.MovieSize)
				&& model.Bind("firestorm", &Data.Firestorm)
				&& model.Bind("firestormsize", &Data.FirestormSize)
				&& model.Bind("totalsize", &Data.TotalSize)
				&& model.Bind("busy", &Data.Busy)
				&& model.Bind("status", &Data.Status)
				&& model.Bind("percent", &Data.Percent)
				&& model.Bind("error", &Data.Error)
				&& model.Bind("haserror", &Data.HasError));
		}

	private:
		UIInstallPresenterClass & Data;
};

}


std::unique_ptr<UIViewClass> UI_Install_View(UIInstallPresenterClass & presenter)
{
	return(std::make_unique<UIInstallViewClass>(presenter));
}
