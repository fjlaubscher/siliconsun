/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "version.h"

#include "opents_build.h"
#include "siliconsun_version.h"

#include <cstdio>
#include <cstring>


// The crash report may be the first caller, so filling this must not allocate.
static char VersionDisplay[128];
static bool VersionDisplayReady = false;


/// <summary>
/// Returns the siliconsun version line shown to the player.
/// An official build, and a build whose commit is unknown, shows the declared version alone.
/// Any other build appends its commit and architecture, and a tree with modified tracked files says so.
/// </summary>
/// <returns>The version line. The text stays valid for the rest of the run.</returns>
char const * Version_Name(void)
{
	if (!VersionDisplayReady) {
#if SILICONSUN_OFFICIAL_BUILD
		std::snprintf(VersionDisplay, sizeof(VersionDisplay), "siliconsun %s", SILICONSUN_VERSION);
#else
		if (std::strcmp(OPENTS_COMMIT, "unknown") == 0) {
			std::snprintf(VersionDisplay, sizeof(VersionDisplay), "siliconsun %s", SILICONSUN_VERSION);
		} else if (OPENTS_COMMIT_DIRTY) {
			std::snprintf(VersionDisplay, sizeof(VersionDisplay), "siliconsun %s (%s, modified, %s)",
				SILICONSUN_VERSION, OPENTS_COMMIT, OPENTS_ARCH);
		} else {
			std::snprintf(VersionDisplay, sizeof(VersionDisplay), "siliconsun %s (%s, %s)",
				SILICONSUN_VERSION, OPENTS_COMMIT, OPENTS_ARCH);
		}
#endif
		VersionDisplayReady = true;
	}

	return(VersionDisplay);
}
