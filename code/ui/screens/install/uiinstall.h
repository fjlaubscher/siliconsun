/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "contentinstall.h"
#include "ui/uiscreen.h"

#include <memory>
#include <string>

class UIViewClass;


enum UIInstallResult
{
	UI_INSTALL_READY,
	UI_INSTALL_QUIT,
	UI_INSTALL_UNAVAILABLE,
};


class UIInstallPresenterClass : public UIPresenterClass
{
	public:
		UIInstallPresenterClass(void);
		virtual void Execute(UIIntent const & intent) override;
		virtual void Refresh(void) override;
		void Update_Sizes(void);

		ContentTransfer Transfer;
		bool TsMovies = true;
		bool Firestorm = true;
		bool FsMovies = true;
		bool Busy = false;
		bool HasError = false;
		int Percent = 0;
		std::string Notice;
		std::string BaseSize;
		std::string TsMoviesSize;
		std::string FirestormSize;
		std::string FsMoviesSize;
		std::string TotalSize;
		std::string Status;
		std::string Error;
};


std::unique_ptr<UIViewClass> UI_Install_View(UIInstallPresenterClass & presenter);

UIInstallResult UI_Install_Dialog(void);
