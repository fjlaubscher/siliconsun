/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include <cstdint>
#include <span>
#include <string>


enum ContentPart
{
	CONTENT_PART_BASE,
	CONTENT_PART_MOVIES,
	CONTENT_PART_FIRESTORM,
	CONTENT_PART_FIRESTORM_MOVIES,
};


struct ContentFile
{
	char const * Name;
	std::uint64_t Size;
	char const * Sha256;
	ContentPart Part;
};


std::span<ContentFile const> Content_Files(void);

char const * Content_Download_Root(void);

std::string Content_Download_Host(void);

bool Content_File_Selected(ContentFile const & file, bool movies, bool firestorm);

std::uint64_t Content_Base_Bytes(void);

std::uint64_t Content_Movies_Marginal(bool firestorm);

std::uint64_t Content_Firestorm_Marginal(bool movies);

std::uint64_t Content_Download_Bytes(bool movies, bool firestorm);

std::string Content_Size_Text(std::uint64_t bytes);

std::string Content_Speed_Text(double bytes_per_second);
