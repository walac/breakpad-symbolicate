/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "google_breakpad/processor/code_module.h"

// Given a path and a module name, fills the CodeModule fields
class SimpleCodeModule : public google_breakpad::CodeModule {
public:
	SimpleCodeModule(
		const std::string &root_path,
		const std::string &code_module);

	uint64_t base_address() const
	{ return 0; }

	uint64_t size() const
	{ return 0; }

	std::string code_file() const
	{ return code_file_; }

	std::string code_identifier() const
	{ return code_identifier_; }

	std::string debug_file() const
	{ return debug_file_; }

	std::string debug_identifier() const
	{ return debug_identifier_; }

	std::string version() const
	{ return ""; }

	const CodeModule *Copy() const;

private:
	std::string debug_identifier_;
	std::string debug_file_;
	std::string code_file_;
	std::string code_identifier_;
};



