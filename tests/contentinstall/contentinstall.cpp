/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "contentcatalog.h"
#include "contentsha256.h"

#include "doctest/doctest.h"

#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>


#ifndef CONTENT_MANIFEST
#error CONTENT_MANIFEST is the workers/content/manifest.json path
#endif


namespace
{

std::string Read_Manifest(void)
{
	std::ifstream file(CONTENT_MANIFEST, std::ios::binary);
	std::ostringstream text;
	text << file.rdbuf();
	return(text.str());
}


int Name_Count(std::string const & text)
{
	int count = 0;
	std::string needle = "\"name\"";
	std::size_t from = 0;
	while (true) {
		from = text.find(needle, from);
		if (from == std::string::npos) {
			break;
		}
		count++;
		from += needle.size();
	}
	return(count);
}

}


TEST_CASE("sha256 matches the empty string and abc")
{
	ContentSha256 sha;
	unsigned char digest[32];
	sha.Final(digest);
	CHECK_MESSAGE(Content_Sha256_Matches("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855", digest), "the empty string hashes to the standard value");

	sha.Reset();
	sha.Update("abc", 3);
	sha.Final(digest);
	CHECK_MESSAGE(Content_Sha256_Matches("ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad", digest), "abc hashes to the standard value");
}


TEST_CASE("the catalog pins the freeware files and tibsun is last")
{
	std::span<ContentFile const> files = Content_Files();
	CHECK_MESSAGE(files.size() == 25, "the freeware set has 25 files");
	CHECK_MESSAGE(std::string(files.back().Name) == "TIBSUN.MIX", "TIBSUN.MIX is saved last, so a cancelled install can resume");
	CHECK_MESSAGE(files.back().Size == 75094736, "TIBSUN.MIX is the freeware archive");
	CHECK_MESSAGE(std::string(files.back().Sha256) == "23431290b211cd039315095e1987f1c411ecd3b6440861c4874572c92e5f6b2a", "TIBSUN.MIX keeps its pinned checksum");

	std::string manifest = Read_Manifest();
	CHECK_MESSAGE(Name_Count(manifest) == (int)files.size(), "the worker manifest lists the same files");
	for (ContentFile const & file : files) {
		CHECK_MESSAGE(manifest.find(std::string("\"") + file.Name + "\"") != std::string::npos, file.Name);
		CHECK_MESSAGE(manifest.find(file.Sha256) != std::string::npos, file.Name);
		CHECK_MESSAGE(manifest.find(std::to_string(file.Size)) != std::string::npos, file.Name);
	}
}


TEST_CASE("firestorm and movies add their own files without counting them twice")
{
	std::uint64_t base = Content_Download_Bytes(false, false);
	std::uint64_t movies = Content_Download_Bytes(true, false);
	std::uint64_t firestorm = Content_Download_Bytes(false, true);
	std::uint64_t both = Content_Download_Bytes(true, true);

	CHECK_MESSAGE(base == Content_Base_Bytes(), "base game and music are always included");
	CHECK_MESSAGE(movies > base, "campaign movies add bytes");
	CHECK_MESSAGE(firestorm > base, "firestorm adds bytes");
	CHECK_MESSAGE(both > movies, "firestorm still adds bytes when movies are selected");
	CHECK_MESSAGE(both > firestorm, "movies still add bytes when firestorm is selected");
	CHECK_MESSAGE(movies - base == Content_Movies_Marginal(false), "the movies line is the bytes movies add without firestorm");
	CHECK_MESSAGE(both - firestorm == Content_Movies_Marginal(true), "with firestorm, the movies line includes firestorm's movies");
	CHECK_MESSAGE(firestorm - base == Content_Firestorm_Marginal(false), "the firestorm line is the bytes firestorm adds without movies");
	CHECK_MESSAGE(both - movies == Content_Firestorm_Marginal(true), "with movies, the firestorm line includes firestorm's movies");
	CHECK_MESSAGE(Content_Size_Text(1024ull * 1024ull * 1024ull) == "1.0 GB", "a gibibyte is shown as 1.0 GB");
	CHECK_MESSAGE(Content_Speed_Text(1.5 * 1024.0 * 1024.0) == "1.5 MB/s", "speed uses the same units");
}


TEST_CASE("the download host is the worker origin without its scheme")
{
	std::string root = Content_Download_Root();
	std::string host = Content_Download_Host();
	CHECK_MESSAGE(root.find(host) != std::string::npos, "the host is taken from the download origin");
	CHECK_MESSAGE(host.find("://") == std::string::npos, "the screen shows the host without a scheme");
}
