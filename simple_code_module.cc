/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "simple_code_module.h"
#include "processor/pathname_stripper.h"
#include <glob.h>
#include <memory>
#include <iostream>
#include <cstring>

using namespace std;
using namespace google_breakpad;

static const string
get_path(const string &root_path, const string &module)
{
	glob_t g;

	memset(&g, 0, sizeof 0);
	const string pattern(root_path + "/" + module + "/[0-9A-F][0-9A-F]*");

	const int glob_ret =
		glob(
			pattern.c_str(),
			GLOB_NOSORT|GLOB_ONLYDIR,
			NULL,
			&g);

	if (glob_ret != 0) {
		switch (glob_ret) {
			case GLOB_NOSPACE:
				cerr << __func__ << ": no memory\n";
				break;
			case GLOB_ABORTED:
				cerr << __func__ << ": read error\n";
				break;
			case GLOB_NOMATCH:
				cerr << __func__ << ": no matches found\n";
				break;
		}

		return "";
	}

	unique_ptr<glob_t, void(*)(glob_t*)> glob_guard(&g, globfree);

	return PathnameStripper::File(g.gl_pathv[0]);
}

SimpleCodeModule::SimpleCodeModule(
	const string &root_path,
	const string &module)
	: debug_identifier_(get_path(root_path, module))
	, debug_file_(module)
	, code_file_(module)
{
}

const CodeModule *
SimpleCodeModule::Copy() const
{
	return new SimpleCodeModule(*this);
}

