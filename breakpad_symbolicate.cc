/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "google_breakpad/processor/basic_source_line_resolver.h"
#include "google_breakpad/processor/stack_frame.h"
#include "processor/simple_symbol_supplier.h"

#include <algorithm>
#include <iostream>
#include <cstdlib>

#include "simple_code_module.h"

using namespace google_breakpad;
using namespace std;

static void
usage(char **argv)
{
	cerr
		<< "Usage: "
		<< argv[0]
		<< " <symbols-directory-path> <module> <address1> "
		<< "<address2> <address3>...\n"
		<< "Resolve address symbols based on "
		<< "breakpad symbol files.\n\n";
}

int
main(int argc, char **argv)
{
	if (argc < 4) {
		usage(argv);
		return EXIT_FAILURE;
	}

	SimpleCodeModule code_module(argv[1], argv[2]);
	SimpleSymbolSupplier symbol_supplier(argv[1]);
	BasicSourceLineResolver resolver;
	string symbol_file;

	if (symbol_supplier.GetSymbolFile(&code_module, nullptr,
				&symbol_file) != SymbolSupplier::FOUND) {
		cerr << "Could not get symbol file\n";
		return EXIT_FAILURE;
	}

	if (!resolver.LoadModule(&code_module, symbol_file)) {
		cerr << "Error loading module " << symbol_file << endl;
		return EXIT_FAILURE;
	}

	StackFrame frame;
	frame.module = &code_module;

	for (int i = 3; i < argc; ++i) {
		frame.instruction = strtoul(argv[i], NULL, 0);
		resolver.FillSourceLineInfo(&frame);

		if (frame.function_name.empty()) {
			cout << "??\n??:0\n";
		} else {
			cout
				<< frame.function_name
				<< "\n"
				<< frame.source_file_name
				<< ":"
				<< frame.source_line
				<< "\n";
		}

		frame.function_name.clear();
	}

	return 0;
}
