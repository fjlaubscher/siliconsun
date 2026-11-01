/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include <memory>
#include <string>


class ContentTransfer
{
	public:
		ContentTransfer(void);
		~ContentTransfer(void);
		ContentTransfer(ContentTransfer const &) = delete;
		ContentTransfer & operator = (ContentTransfer const &) = delete;

		void Start_Download(bool movies, bool firestorm);
		void Start_Copy(std::string const & folder, bool movies, bool firestorm);
		void Cancel(void);
		void Tick(void);
		bool Active(void) const;
		bool Succeeded(void) const;
		int Percent(void) const;
		std::string const & Status(void) const;
		std::string const & Error(void) const;

	private:
		struct State;
		std::unique_ptr<State> Data;
};


bool Content_Data_Present(void);
